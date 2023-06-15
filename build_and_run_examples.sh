#!/usr/bin/env bash

rm -rf ./build_examples/
mkdir -p ./build_examples/
cd ./build_examples/

clear && \
cmake ./../examples/ -DCMAKE_BUILD_TYPE=Release && \
make -j4 && \
\
printf "\nExample: basic\n" && \
./basic && \
\
printf "\nExample: flexbox_gap\n" && \
./flexbox_gap && \
\
printf "\nExample: grid_holy_grail\n" && \
./grid_holy_grail && \
\
printf "\nExample: nested\n" && \
./nested

cd ..
