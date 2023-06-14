<div align="center">

# taffy_cpp - Taffy C++ port

:heavy_exclamation_mark: This project currently in 'Work In Progress' state :heavy_exclamation_mark:

</div>

This library is a port of excellent Rust-written [Taffy][taffy_url] UI layout
library for C++.

The main goals of this library are:
- Provide all the features (or almost all) of the [Taffy][taffy_url] library 
  (with similar API) but for C++ projects.
- Behave exactly like [Taffy][taffy_url] and pass all tests.
- Be the same fast and achieve same cross-platform support (or even wider).

<!--
  Reference to great quote in Carbon language README:
    https://github.com/carbon-language/carbon-lang/blob/trunk/README.md

  > Existing modern languages already provide an excellent developer experience:
  > Go, Swift, Kotlin, Rust, and many more. Developers that can use one of these
  > existing languages should.
-->
If you _**can**_ use [Taffy][taffy_url] (if your project written in Rust, or can
be easily linked with it) - you **should** use it! If you _**can't**_ (for
example: if your project in C++, and you want to use [Taffy][taffy_url]
'directly' - without linking or wrapping) - `taffy_cpp` **for you**! :)

----

In short - `taffy_cpp` is a 'mirror', 'reflection' or 'back-port' of 
[Taffy][taffy_url] library, to provide ability of usage of it's brilliant 
algorithms in other (non-Rust) environments or toolchains. 

If you want to add any feature or bug-fix - first of all propose changes into 
[Taffy][taffy_url] project. If they are accepted, next (if it's possible) - they 
will be ported into `taffy_cpp`.
This project aims to be a 'reflection' of [Taffy][taffy_url] (and be compatible 
and similar to it as close as possible), not a separated incompatible standalone
entity. In `taffy_cpp` considered only changes that improve code similarity 
(with [Taffy][taffy_url]) or improve performance and safety.

----

If you find `taffy_cpp` useful for you, you can show it in a simple way - just
put a 'star' :star: for this project on GitHub. Instead of saying thanks, this
way you will show that this project is **in demand**, and you can also see how 
many of the same users need it. 

Don't forget to add the [Taffy][taffy_url] 'star' :star: too! The great work in
that repository is the reason why `taffy_cpp` even exists.

----

Notice, that [Taffy][taffy_url] in the future may have FFI interface (exposing
its API via C interface - for bindings with other languages), and
[gccrs](https://github.com/Rust-GCC/gccrs) promisingly evolve, but `taffy_cpp`
still may be needed for those, who prefer simple C++ alternative.

Also, you can consider `taffy_cpp` as an alternative to the well-known 
[Yoga](https://github.com/facebook/yoga) (which is also written in C++, but
supported by a big company and used in many projects in various languages).

## Version

Current state of this library sources reflects the state of [Taffy][taffy_url] 
sources tree for:

- Commit: [46546b26777ca14669ba079a307f9c0b5d9a8854](https://github.com/DioxusLabs/taffy/tree/46546b26777ca14669ba079a307f9c0b5d9a8854)
    - In tree: [46546b2](https://github.com/DioxusLabs/taffy/commits/main#:~:text=46546b2)
        <!-- Reference to '#:~:text=<text>' usage: https://stackoverflow.com/a/62162093/ -->

## Configuring

| Define                       | Description                                   |
| :--------------------------- | :-------------------------------------------- |
| `TAFFY_FEATURE_BLOCK_LAYOUT` | Enable `Block`   layout algorithm support
| `TAFFY_FEATURE_FLEXBOX`      | Enable `Flexbox` layout algorithm support (and related `Style` properties)
| `TAFFY_FEATURE_GRID`         | Enable `Grid`    layout algorithm support (and related `Style` properties)
|                              |
| `TAFFY_FEATURE_DEBUG`        | Enable layout algorithm execution-steps debug printing via `DebugLogger`
| `TAFFY_FEATURE_PROFILE`      | Enable some additional debug printing during layout algorithm execution
| `TAFFY_CONFIG_TEST`          | Enable extra printing in 'tests'
|                              |
| `TAFFY_CONFIG_PANIC_UNWIND`  | (default) In case of `panic` called `assert(false)` with stack unwinding
| `TAFFY_CONFIG_PANIC_ABORT`   | In case of panic called `std::abort()` (causes `SIGABRT` signal throwing)

## Dependencies

For third-party dependencies shipped with this library (and their versions),
read [third_party/README.md](./third_party/README.md).

## FAQ

- **Question**: Why it written in `C++11` over modern `C++17`/`C++20`/etc ?
- **Answer**: First of all, in `C++11`, the minimum necessary things were 
  introduced to make the C++ code look (and behave) like original Taffy Rust 
  implementation: lambdas, (good) templates, scoped enumerations, constexpr 
  functions, type traits, SFINAE, auto type deduction, etc.
  That's why `C++98` was not used :D

  Low requirements for C++ support in compilers means wider code 
  'applicability'. In our imperfect world, there is an incredible number of 
  devices (with various architectures) under which you can compile C++ code, 
  but vendor's compiler may supports only good old `C++11` or `C`. I mean 
  microelectronics or various outdated systems that cannot be easily updated.

  Once you find yourself in a situation where you need to do something useful 
  in such harsh conditions, you will thank God that we still have useful 
  libraries, written with old standard but can be used almost anywhere :)
  
  However, the code also has to be written under severe restrictions, without 
  the features introduced in the new standards (like better constexpr rules
  introduced since `C++17`, or `concepts` from `C++20`), and with usage of
  third-party libraries that back-port needed functionality from next standards.

  Also, this does not mean that we are stuck on the 'old' `C++11` standard -
  this library (due to C++ backwards compatibility, which also a great 
  advantage) we can easily use in next or any future language versions. Any
  needed features of that versions may be enabled under conditional compile-time 
  C++ version check (via `#if` pragma). This only means, that (for greater good)
  our code must be written in a such way, that allows us to be used anywhere, 
  not in 'modern' environment (or which we consider to be).

  **TL;DR**: `C++11` was chosen due to wider support over newer standard
  versions. You can check `C++11` support in various compilers (and versions 
  from which such support began)
  [here](https://en.cppreference.com/w/cpp/compiler_support/11).

- **Question**: Why this library written in 'header-only' manner?
- **Answer**: Let's take a look at some advantages and disadvantages (that I was
  able to quickly come up with) of header-only library distribution:

    - Advantages:
        - Header-only library easier to integrate, since user need to specify 
          only include path in build system, instead of building library first 
          as static or shared library, then use public headers & link over it.

        - Header-only library easier to configure, since user only need to add 
          defines into build system, instead of building a library with special 
          flags that will be included as defines in a special configuration file
          that will need to be included in every public header.

        - Header-only library is suitable for code that contains a lot of 
          templates and constexpr functions (that this project abounds in).

        - Header-only library is easier to 'amalgamate' into a single header file,
          that also makes it much easier to distribute & integrate.

        - Header-only library provides for compiler all its sources, and during
          built it may easily throw out unused code, that cannot be removed from
          already built shared library.

    - Disadvantages:
        - We cannot easily specify special compilation flags when using 
          header-only library, for example: build it with extra 
          optimization due to high performance needs. In case of shared or static
          library, we can easily build it with `-O3` or `-ffast-math` without
          changing build rules for rest of the user project code.
          - As workaround for it, header-only library may be build separately,
            with exposing API only via C interface. Also, it's suitable for FFI.

        - Header-only library slightly increases compilation time

        - In non-header-only library easier to resolve circular types 
          dependencies, by moving dependent code into source files.

  **TL;DR**: I see a struggle here between two important properties:
  - Simple integration, configuration, distribution;
  - Simple compilation fine-tuning.
  Fine-tuning may be achieved by extra wrapping or in some other way, so I 
  prefer header-only manner to achieve easier usage.

- **Question**: Why it named so `taffy_cpp` - not `Taffy-cpp` or even 
  `Taffy.cpp` (like [whisper.cpp](https://github.com/ggerganov/whisper.cpp))?
- **Answer**: For a some strange paranoid reason, I prefer 'safe' naming, that 
  can be used in various contexts: in various file-systems with various naming 
  rules, and also in source code in any language. 
  That's why for naming here is avoided 'space', 'minus' or 'dot' symbols, or
  any non-ascii :D Also it makes us easy to search for such name.

[taffy_url]: https://github.com/DioxusLabs/taffy
