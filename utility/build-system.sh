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

cd ..
./build/purriler --build-system=example/build.purr