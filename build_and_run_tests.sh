#!/usr/bin/env bash

rm -rf ./build_tests/
mkdir -p ./build_tests/
cd ./build_tests/

# Notice, that we build tests in 'Debug' mode - specially to be able to use
# `gdb` if some tests fails with 'segmentation fault' or other corruption.
# Also, during tests execution, run-time perfomance not matter (tests are not
# benchmarks) - tests checks only algorithm correctness.

clear && \
cmake ./../tests/ -DCMAKE_BUILD_TYPE=Debug && \
make -j4 && \
./taffy_tests

cd ..
