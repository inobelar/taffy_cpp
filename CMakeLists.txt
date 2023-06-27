cmake_minimum_required(VERSION 3.14)

project(
    taffy_cpp
    DESCRIPTION "taffy_cpp library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

add_library(taffy_cpp INTERFACE)

target_include_directories(taffy_cpp INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_include_directories(taffy_cpp INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/optional-lite-3.5.0/include/
)

target_include_directories(taffy_cpp INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/optional-lite-3.5.0/include/
)

target_include_directories(taffy_cpp INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/expected-lite-0.6.3/include/
)

target_include_directories(taffy_cpp INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/span-lite-0.10.3/include/
)

target_include_directories(taffy_cpp INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/slot_map/include/
)
