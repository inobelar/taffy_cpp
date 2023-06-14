# Conversion rules

## C++

### Resolving circular dependencies

During porting code from Rust into C++, was found few circulard dependencies:
- `TrackCounts` <--> `OriginZeroLine`
- `Taffy` <--> functions from `taffy_tree`

To resolve them used pattern, described in the next references: 
- https://stackoverflow.com/a/51185143/
- https://stackoverflow.com/a/68021125/

```cpp
// A_def.h
#ifndef A_DEF_H
#define A_DEF_H

class B;
class A
{
    int _val;
    B *_b;

public:
    A(int val);
    void SetB(B *b);
    void Print();
};

#endif // A_DEF_H
```

```cpp
// B_def.h
#ifndef B_DEF_H
#define B_DEF_H

class A;
class B
{
    double _val;
    A* _a;

public:
    B(double val);
    void SetA(A *a);
    void Print();
};

#endif // B_DEF_H
```

```cpp
// A.h
#ifndef A_H
#define A_H

#include "A_def.h"
#include "B_def.h"

inline A::A(int val) : _val(val)
{}

inline void A::SetB(B *b) {
    _b = b;
    _b->Print();
}

inline void A::Print() {
    cout << "Type:A val=" << _val << endl;
}

#endif // A_H
```

```cpp
// B.h
#ifndef B_H
#define B_H

#include "A_def.h"
#include "B_def.h"

inline B::B(double val) : _val(val)
{}

inline void B::SetA(A *a) {
    _a = a;
    _a->Print();
}

inline void B::Print() {
    cout << "Type:B val=" << _val << endl;
}

#endif // B_H
```

### Scoped enumerations

All [scoped enumerations](https://en.cppreference.com/w/cpp/language/enum#Scoped_enumerations) 
**must** explicitly contain **smallest** underlying type (since default type is 
`int`) - to achieve:

1. Rust behaviour.
2. Smaller memory usage of huge structures that contain many fields with such enums (like `Style`).

```cpp
enum class AlignItems : uint8_t // <-- uint8_t required here
{
    Start = 0,
    End,
    FlexStart,
    FlexEnd,
    Center,
    Baseline,
    Stretch
};
```

Search all enumerations with missing underlying type:

```shell
$ grep -Ern "enum class \S+\s*{"
```

### std::reference_wrapper

**All** places of **creation** objects of 
[`std::reference_wrapper<T>`](https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper)
type must use [`std::ref()` or `std::cref()`](https://en.cppreference.com/w/cpp/utility/functional/ref)
for it - to avoid passing reference to **local** variable, instead of what we need.

For consistency, them really must be used in **all** places, even when it not 
really needed - to not check that places it in case of bugs. That functions 
produces zero overhead, so their use only increases security.

There were a few bugs during the implementation - some tests fails for strange
reason (looking ahead - it was due to the lack of `std::ref()`). Finding the 
problems by using  `printf()`/`println!()` to side-by-side compare internal 
state and result of algorithms excution in Rust and C++ took around **two days** :D 

Examples:

```cpp
const Vec<ExpectedChildInfo>& children = ...;

auto mapped_children = new_vec_with_capacity< std::tuple<size_t, NodeId, std::reference_wrapper<Style const>> >(children.size());
for(const auto& item : children) {
    const size_t& index = std::get<0>(item);
    const Style&  style = std::get<1>(item);

    // NOTE: `std::cref()` is important here. Otherwise passed style here
    // will wrong: (same/repeated), since it will be reference to local
    // variable, not reference to `item` style.
    mapped_children.push_back( std::make_tuple(index, NodeId::from(index), std::cref(style)) ); 
}
```

```cpp
std::tuple<size_t, NodeId, InBothAbsAxis<Line<OriginZeroGridPlacement>>, std::reference_wrapper<Style const>>
operator () (const std::tuple<size_t, NodeId, std::reference_wrapper<Style const>>& t) const
{
    const auto& index = std::get<0>(t);
    const auto& node  = std::get<1>(t);
    const auto& style = std::get<2>(t).get();

    const auto origin_zero_placement = InBothAbsAxis<Line<OriginZeroGridPlacement>> {
        style.grid_column.map<OriginZeroGridPlacement>([this](const GridPlacement& placement) { return placement.into_origin_zero_placement(explicit_col_count); }),
        style.grid_row.map<OriginZeroGridPlacement>([this](const GridPlacement& placement) { return placement.into_origin_zero_placement(explicit_row_count); })
    };

    // NOTE: `std::cref()` is important here! To pass reference to 't.style', 
    // not reference to temporal 'style'
    return std::make_tuple(index, node, origin_zero_placement, std::cref(style));
}
```

```cpp
inline TaffyResult<std::reference_wrapper<Style const>> style(NodeId node) const
{
    // `std::cref()` is not needed here (no local variables created), but we
    // use it for consistency.
    return TaffyResult<std::reference_wrapper<Style const>>::Ok( std::cref(this->nodes[node_id_into_key(node)].style) );
}
```

Search for all places of usage `std::reference_wrapper`:

```shell
$ grep -rn "std::reference_wrapper"
```

## Rust --> C++

### Reserved keywords usage

In Rust sources, in some cases used C++ keywords as names for variables or functions.
In such cases, we simply use capitalized names instead. For example:

- `new`      -> `New`
- `default`  -> `Default`
- `auto`     -> `Auto`
- `explicit` -> `Explicit`
- `or`       -> `Or`
- `template` -> `Template`

### Tests in sources

All tests (marked by `#[test]`) inside of sources, must be implemented as
separated tests in  `./tests/` directory.

Search for `#[test]`:

```shell
$ grep -rn "#\[test\]"
```

### Traits :: Debug, Default, Display

TODO

`$ grep -Ern "Default[^a-zA-Z]"`

### Constructor with `new`

All consistency, all Rust functions `fn new(Args...) -> Self` must be converted
in C++ as `static` `New` function AND constructor.

Example:

```rust
// Rust
pub(crate) struct NodeData {
    pub(crate) style: Style,
    pub(crate) layout: Layout,
    pub(crate) needs_measure: bool,
    pub(crate) cache: Cache,
}

impl NodeData {
    #[must_use]
    pub const fn new(style: Style) -> Self {
        Self { style, cache: Cache::new(), layout: Layout::new(), needs_measure: false }
    }
}
```

```cpp
struct NodeData {
    Style style;
    Layout layout;
    bool needs_measure;
    Cache cache;

    // -------------------------------------------------------------------------

    NodeData(
        const Style& style_,
        const Layout& layout_,
        bool needs_measure_,
        const Cache& cache_
    )
        : style(style_)
        , layout(layout_)
        , needs_measure(needs_measure_)
        , cache(cache_)
    {}

    // -------------------------------------------------------------------------

    // Named constructor New (actually - static function) - to be similar to Rust
    static inline NodeData New(const Style& style) {
        return NodeData{ style, Layout::New(), false, Cache::New() };
    }

    // Common constructor - in C++ style
    NodeData(const Style& style)
        : NodeData{ New(style) }
    {}
};
```

Search for `fn new(`:

```shell
$ grep -Ern "fn\s+new\s*\("
```

### `self.` convert into `this->`

For consistency, all occurancies of `self.???` in Rust convert into `this->???` in C++.

Search for `self.`:

```shell
$ grep -rn "self\."
```

### Iteration utilites

Simple cases occurancies of `.any(...)`, `.all(...)`, `.position(...)`, ..., for readability must be replaced with one-liners:

- `.any(...)` :

    - Search: 

        ```shell
        $ grep -Ern "\.\s*any\s*\("
        ```

    - Example:

        ```rust
        // Rust
        pub fn is_empty(&self) -> bool {
            !self.entries.iter().any(|entry| entry.is_some())
        }
        ```

        ```cpp
        // C++
        bool is_empty() const {
            return !any(this->entries, [](const Option<CacheEntry>& entry) { return entry.is_some(); });
        }
        ```

- `.all(...)`:

    - Search:

        ```shell
        $ grep -Ern "\.\s*all\s*\("
        ```

    - Example:

        ```rust
        // Rust
        let tracks_all_fixed = spanned_tracks.iter()
            .all(|track| track.max_track_sizing_function.definite_value(axis_parent_size).is_some());
        ```

        ```cpp
        // C++
        const auto tracks_all_fixed =
            all(spanned_tracks, [&](const GridTrack& track) {
                return track.max_track_sizing_function.definite_value(axis_parent_size).is_some();
            });
        ```

- `.position(...)`:

    - Search:

        ```shell
        $ grep -Ern "\.\s*position\s*\("
        ```

    - Example:

        ```rust
        let next_row_first_item =
            remaining_items.iter().position(|item| item.placement(other_axis).start != current_row);
        ```

        ```cpp
        const auto next_row_first_item =
            position(remaining_items, [&](const GridItem& item) { return item.placement(other_axis).start != current_row; });
        ```

- `.count()` (typically it's `.filter(...).count()`):

    - Search:

        ```shell
        $ grep -Ern "\.\s*count\s*\("
        ```

    - Example:

        ```rust
        let row_baseline_item_count = row_items.iter().filter(|item| item.align_self == AlignSelf::Baseline).count();
        ```

        ```cpp
        const auto row_baseline_item_count =
            filter_and_count(row_items, [](const GridItem& item) { return item.align_self == AlignSelf::Baseline; });
        ```

        ```rust
        let number_of_growable_tracks = tracks.iter()
            .filter(|track| track_is_affected(track))
            .filter(|track| {
                track.infinitely_growable || track.fit_content_limited_growth_limit(axis_inner_node_size) == f32::INFINITY
            })
        ```

        ```cpp
        const auto number_of_growable_tracks =
            filter_and_filter_and_count(
                tracks,
                [&](const GridTrack& track) { return track_is_affected(track); },
                [&](const GridTrack& track) { return track.infinitely_growable || track.fit_content_limited_growth_limit(axis_inner_node_size) == std::numeric_limits<float>::infinity(); }
            );
        ```

- `.sum()`

    - `.map(...).sum()` and `.map(...).sum::<???>()`:

        - Search:

            ```shell
            $ grep -Ern "\.\s*sum\s*\("
            ```

            ```shell
            $ grep -Ern "\.\s*sum\s*::\s*<\s*\S+\s*>\s*\("
            ```

        - Example:

            ```rust
            let track_sizes: f32 = tracks.iter().map(|track| track.base_size).sum();
            ```

            ```cpp
            const float track_sizes = map_and_sum<float>(tracks, [](const GridTrack& track) { return track.base_size; });
            ```

## panic

Rust `panic!` must be translated into similar macro (not simple `assert()`).

- Search:

    ```shell
    $ grep -rn "panic"
    ```  

## Misc

### Iterators

Notice, that [Rust iterators not the same as C++ iterators](https://stackoverflow.com/a/49003330/):

- C++ iterators will be named cursors,
- Rust iterators will be named streams.

Since this library is written in C++11 (for portability) and perfomance also at
the head of the table (any overhead for the sake of readability is not
acceptable) - where it's possible, we use alternate simple naive C++
implementation (typically it's `for`/`while` loops, even it kinda verbose or
boilerplate), without unwanted magic from STL (for example, functions from
`<algrorithm>`), or external libraries.

Alternatives that do not suit us:

- [ericniebler/range-v3](https://github.com/ericniebler/range-v3) (C++14) or [`ranges`](https://en.cppreference.com/w/cpp/ranges) from C++20
- [NasalDaemon/iter](https://github.com/NasalDaemon/iter) (C++20)

Exceptions:

- From `<algorithm>` used the next functions:
    - [`std::remove_if()`](https://en.cppreference.com/w/cpp/algorithm/remove)
    - [`std::stable_sort()`](https://en.cppreference.com/w/cpp/algorithm/stable_sort)
