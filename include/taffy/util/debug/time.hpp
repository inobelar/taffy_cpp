#pragma once

namespace taffy {

/* TODO: maybe we need it ?

    #[cfg(feature = "profile")]
    #[allow(unused_macros)]
    macro_rules! time {
        ($label:expr, $($code:tt)*) => {
            let start = ::std::time::Instant::now();
            $($code)*
            let duration = ::std::time::Instant::now().duration_since(start);
            crate::util::debug::NODE_LOGGER.log(format_args!("Performed {} in {}ms", $label, duration.as_millis()));
        };
    }

    #[cfg(not(feature = "profile"))]
    #[allow(unused_macros)]
    macro_rules! time {
        ($label:expr, $($code:tt)*) => {
            $($code)*
        };
    }

    #[allow(unused_imports)]
    pub(crate) use time;

*/

} // namespace taffy