#include <doctest.h>

#include "tests_taffy_to_string.hpp"

#include <taffy/tree/measure_func/MeasureFunc.hpp>

using namespace taffy;

TEST_CASE("measure_func_is_send_and_sync" * doctest::test_suite("measure_func"))
{
    /* TODO: somehow implement that test:

        fn is_send_and_sync<T: Send + Sync>() {}
        is_send_and_sync::<MeasureFunc>();
    
    */
}
