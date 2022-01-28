#!/bin/bash

# directory where current shell script resides
PROJECTDIR=$(dirname "$BASH_SOURCE")

cd "$PROJECTDIR"

mkdir -p build && cd build

rm -rf ./*
cmake ../ -DCMAKE_BUILD_TYPE=Release "$@"
cmake --build . -- -j6
