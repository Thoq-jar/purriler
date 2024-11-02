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