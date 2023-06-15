cmake_minimum_required(VERSION 3.14)

project(
    taffy_tests
    DESCRIPTION "taffy_cpp tests"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

set(SOURCES

    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

    # Manually-written inplace tests from sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src_style_mod.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_style_flex.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_tree_measure_func.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_tree_taffy_tree_tree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_compute_grid_placement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_compute_grid_explicit_grid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_compute_grid_implicit_grid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_compute_flexbox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_compute_mod.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_style_helpers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_util_math.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_util_resolve.cpp

    # Manually-written tests
    ${CMAKE_CURRENT_SOURCE_DIR}/rounding.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/caching.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/min_max_overrides.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/root_constraints.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/relayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/measure.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/border_and_paddings.cpp

    # Generated tests
    ${CMAKE_CURRENT_SOURCE_DIR}/fixtures.cpp
)
    
add_executable(taffy_tests ${SOURCES})

# ------------------------------------------------------------------------------

# Make this 'tests' project also sources 'verifier'/'analyzer'
#
# Reference about compiler detection: https://stackoverflow.com/a/10055571/
#
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Using regular Clang or AppleClang
    # That's why here is 'MATCHES' not 'STREQUAL'

    if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        # Using clang with clang-cl front end

        # TODO: add flags

    elseif (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
        # Using clang with regular front end

        # TODO: add flags

    endif()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Using GCC

    target_compile_options(taffy_tests PRIVATE
        -Wall -Wextra -pedantic-errors
    )

    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 10.1)

        # Flag '-fanalyzer' was added since gcc 10.1
        target_compile_options(taffy_tests PRIVATE
            -fanalyzer
        )

    endif()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    # Using Intel C++

    # TODO: add flags

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Using Visual Studio C++

    # TODO: add flags

endif()

# ------------------------------------------------------------------------------
# Doctest

target_include_directories(taffy_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/doctest_v2_4_11/
)

# ------------------------------------------------------------------------------
# taffy_cpp

add_subdirectory(../ taffy_lib_dir)

target_link_libraries(taffy_tests PRIVATE taffy)

target_compile_definitions(taffy_tests PRIVATE TAFFY_FEATURE_BLOCK_LAYOUT)
target_compile_definitions(taffy_tests PRIVATE TAFFY_FEATURE_FLEXBOX)
target_compile_definitions(taffy_tests PRIVATE TAFFY_FEATURE_GRID)
#target_compile_definitions(taffy_tests PRIVATE TAFFY_FEATURE_DEBUG)
target_compile_definitions(taffy_tests PRIVATE TAFFY_CONFIG_TEST)

# ------------------------------------------------------------------------------
# Generated tests

target_include_directories(taffy_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/
)
