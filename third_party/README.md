# Third-party dependencies

- [martinmoene/optional-lite](https://github.com/martinmoene/optional-lite)
    - Version: [3.5.0](https://github.com/martinmoene/optional-lite/releases/tag/v3.5.0)

- [martinmoene/expected-lite](https://github.com/martinmoene/expected-lite)
    - Version: [0.6.3](https://github.com/martinmoene/expected-lite/releases/tag/v0.6.3)

- [martinmoene/span-lite](https://github.com/martinmoene/span-lite)
    - Version: [0.10.3](https://github.com/martinmoene/span-lite/releases/tag/v0.10.3)

-----

- [slot_map](https://github.com/Masstronaut/slot_array/blob/master/P0661r2.md)
    - NOTE: we using slightly patched 'reference implementation implemented by
      Arthur O'Dwyer for the SG14' (from [here](https://github.com/WG21-SG14/SG14/blob/master/SG14/slot_map.h))

      Patches contains the next changes, needed to adapt it for C++11:
      - Explicit types, instead of `auto`:

        ```cpp
        using index_type      = typename Key::first_type;
        using generation_type = typename Key::second_type;

        static constexpr index_type get_index(const Key& k) { return std::get<0>(k); }
        static constexpr generation_type get_generation(const Key& k) { return std::get<1>(k); }
        ```

      - `constexpr` almost everywhere changed into `inline`, since in such
        places it allowed only since C++20, but in C++11 `std::vector` is not
        `constexpr`.

      - Added `protected` accessor for internal `slots_`:

        ```cpp
        inline Container<key_type>& s() & noexcept { return slots_; }
        inline const Container<key_type>& s() const& noexcept { return slots_; }
        inline Container<key_type>&& s() && noexcept { return std::move(slots_); }
        inline const Container<key_type>&& s() const&& noexcept { return std::move(slots_); }
        ```

        Specially to be able to iterate over `slot_map` not only by `values`, but
        over `key` and `value` simultaneously (needed for tests):

        ```cpp
        template <typename T>
        class SlotMap
            : public stdext::slot_map<T, DefaultKey>
        {
        public:
            // ...

            template <typename F>
            void for_each(F&& callback) const
            {
                const auto& keys   = base_t::s(); // accessor to `slot_map::slots_`
                const auto& values = base_t::c(); // accessor to `slot_map::values_`

                assert(values.size() <= keys.size());
                const size_t values_size = values.size();

                for(size_t i = 0; i < values_size; ++i)
                {
                    const auto& key   = keys[i];
                    const auto& value = values[i];
                    callback(key, value);
                }
            }
        };
        ```

        It can be used in the next way:

        ```cpp
        taffy.nodes.for_each([&](const DefaultKey& key, const NodeData& value)
        {
            // ...
        };
        ```

      - Minor formatting
