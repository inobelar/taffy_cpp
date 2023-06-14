#pragma once

// Reference: https://doc.rust-lang.org/cargo/reference/profiles.html#panic

// -----------------------------------------------------------------------------

// If panic strategy not defined - default is 'unwind'
#if !defined(TAFFY_CONFIG_PANIC_UNWIND) && !defined(TAFFY_CONFIG_PANIC_ABORT)
    #define TAFFY_CONFIG_PANIC_UNWIND
#endif // !TAFFY_CONFIG_PANIC_UNWIND && !TAFFY_CONFIG_PANIC_ABORD

// If panic strategies BOTH defined - notify about error
#if defined(TAFFY_CONFIG_PANIC_UNWIND) && defined(TAFFY_CONFIG_PANIC_ABORT)
    #error "Taffy :: Both 'TAFFY_CONFIG_PANIC_UNWIND' and 'TAFFY_CONFIG_PANIC_ABORT' defined - choose one"
#endif // !TAFFY_CONFIG_PANIC_UNWIND && !TAFFY_CONFIG_PANIC_ABORD

// -----------------------------------------------------------------------------

#if defined(TAFFY_CONFIG_PANIC_UNWIND)
    #include <cassert> // for: assert()
#endif // TAFFY_CONFIG_PANIC_UNWIND

#if defined(TAFFY_CONFIG_PANIC_ABORT)
    #include <cstdio>  // for: std::fprintf(), std::fflush()
    #include <cstdlib> // for: std::abort()
#endif // TAFFY_CONFIG_PANIC_ABORT

namespace taffy {

#if defined(TAFFY_CONFIG_PANIC_UNWIND)

    #define taffy_panic(message) \
        do { assert(false && message); } while(false)

#elif defined(TAFFY_CONFIG_PANIC_ABORT)

    #define taffy_panic(message) \
        do { std::fprintf(stderr, "taffy :: panic at %s:%i : %s\n", __FILE__, __LINE__, message); std::fflush(stderr); std::abort(); } while(false)

#else

    #error "Taffy :: panic behavior unknown"

#endif

} // namespace taffy
