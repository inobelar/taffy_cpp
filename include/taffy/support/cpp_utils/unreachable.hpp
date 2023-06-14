#pragma once

#include <cassert> // for: assert()

namespace taffy {

/**
    Special macro, used when we need to mark 'unreachable' code.

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

        taffy_unreachable;
    }
    @endcode

    Reference: https://stackoverflow.com/a/34112549/
*/

#define taffy_unreachable \
    do { assert(false && "Unreachable place"); } while(false)

} // namespace taffy
