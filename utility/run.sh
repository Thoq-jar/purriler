#!/bin/bash

clear

if [ -d "build" ]; then
    cd build
else
    mkdir -p build
    cd build
fi

cmake ..
make -j 16

./purriler \
    ../example/src/main.cpp \
    ../example/src/geometry/point.cpp \
    ../example/src/geometry/circle.cpp \
    ../example/src/utils/pattern.cpp \
    ../example/src/utils/random.cpp \
    ../example/src/analysis/number_analyzer.cpp \
    --out-dir=../example/build \
    -o program