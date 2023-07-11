#pragma once

#if !defined(__GNUC__) && !defined(_MSC_VER)
    #include <cassert> // for: assert()
#endif

namespace taffy {

/**
    Special function, used when we need to mark 'unreachable' code.

    It must be used in places, where compiler produces the next warning:

        warning: control reaches end of non-void function [-Wreturn-type]

    as 'clap' to suppress it :)

    This warning it typically produced in the next cases:
    - switch'es without 'default' case
    - if { .. } else if { ... } without closing 'else' at end

    > Note that adding it as the `default` case wouldn't be as good, since that
    > would silence all unhandled switch case warnings when e.g. adding new
    > enum values.
    >
    > This is also good for debugging because it lets you instantly know such
    > functions receives an invalid argument for some reason.

    Example of usage:

    @code{.cpp}
    const char* bar(FOO f) {
        switch (f) {
        case FOO::A : return "A";
        case FOO::B : return "B";
        case FOO::C : return "C";
        }

        taffy_unreachable();
    }
    @endcode

    Reference: https://stackoverflow.com/a/34112549/

    ----------------------------------------------------------------------------

    Implementation based on:

        https://en.cppreference.com/w/cpp/utility/unreachable

    Notice the difference between 'builtin functions' and 'assert(false)':

    - 'assert(false)':
        - In 'Release' build, assertions may be removed by compiler, so
          it still may trigger warnings. That's why its preferred to use
          'builtin functions'.

        - But in 'Debug', assertion causes stack unwinding in case of reaching
          'unreachable' code (unlike 'buitin functions' that may or may not do
          this in 'Debug').

    - 'builtin functions':
        - They silence compiler warnings in both 'Release' and 'Debug' builds,
          since not removed by compiler.

        - In 'Release' build they cause 'undefined behavior' in case of reaching
          'unreachable' code, and in 'Debug' may cause 'trap' - silently
          'terminate' program abnormally:
            - Reference: https://stackoverflow.com/a/35734843/

    In short, if we take a look into 'disadvantages' of this 2 methods:
        - 'builtin functions' - not produce stack unwinding
        - 'assert(false)'     - may be erased by compiler
    we prefere 'builtin functions' for our needs.
*/

[[noreturn]] inline void taffy_unreachable()
{
    // Uses compiler specific extensions if possible.
    // Even if no extension is used, undefined behavior is still raised by
    // an empty function body and the 'noreturn' attribute.

    #if defined(__GNUC__) // GCC, Clang, ICC

        // References:
        //   - gcc   : https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005funreachable
        //   - clang : https://clang.llvm.org/docs/LanguageExtensions.html#builtin-unreachable

        __builtin_unreachable();

    #elif defined(_MSC_VER) // MSVC

        // Reference:
        //   https://learn.microsoft.com/en-us/cpp/intrinsics/assume

        __assume(false);

    #else // Unknown compiler

        // NOTE: in 'Release' build, assertions may be removed by compiler, so
        // it still may trigger warnings.

        do { assert(false && "Unreachable place"); } while(false);

    #endif
}

} // namespace taffy
