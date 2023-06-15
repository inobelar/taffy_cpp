cmake_minimum_required(VERSION 3.14)

project(
    taffy
    DESCRIPTION "taffy_cpp examples"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

# ------------------------------------------------------------------------------
# taffy_cpp

add_subdirectory(../ taffy_lib_dir)

# ------------------------------------------------------------------------------

add_executable(basic
    ${CMAKE_CURRENT_SOURCE_DIR}/basic.cpp
)

target_link_libraries(basic PRIVATE taffy)

target_compile_definitions(basic PRIVATE TAFFY_FEATURE_FLEXBOX)

# ------------------------------------------------------------------------------

add_executable(flexbox_gap
    ${CMAKE_CURRENT_SOURCE_DIR}/flexbox_gap.cpp
)

target_link_libraries(flexbox_gap PRIVATE taffy)

target_compile_definitions(flexbox_gap PRIVATE TAFFY_FEATURE_FLEXBOX)

# ------------------------------------------------------------------------------

add_executable(grid_holy_grail
    ${CMAKE_CURRENT_SOURCE_DIR}/grid_holy_grail.cpp
)

target_link_libraries(grid_holy_grail PRIVATE taffy)

target_compile_definitions(grid_holy_grail PRIVATE TAFFY_FEATURE_GRID)

# ------------------------------------------------------------------------------

add_executable(nested
    ${CMAKE_CURRENT_SOURCE_DIR}/nested.cpp
)

target_link_libraries(nested PRIVATE taffy)

target_compile_definitions(nested PRIVATE TAFFY_FEATURE_FLEXBOX)

# ------------------------------------------------------------------------------
