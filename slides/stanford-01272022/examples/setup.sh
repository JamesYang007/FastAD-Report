#!/bin/bash

projectdir=$(dirname "BASH_SOURCE")
fastadpath="libs/FastAD"
eigen3path="libs/eigen-3.3.7"

mkdir -p libs

# install Eigen 3.3
if [ ! -d "$eigen3path" ]; then
    cd libs &> /dev/null
    curl -o eigen-3.3.7.tar.gz https://gitlab.com/libeigen/eigen/-/archive/3.3.7/eigen-3.3.7.tar.gz
    tar xzf eigen-3.3.7.tar.gz
    rm -f eigen-3.3.7.tar.gz
    cd eigen-3.3.7
    mkdir -p build && cd build
    cmake .. -DCMAKE_INSTALL_PREFIX="." # installs into build directory
    make install
    cd ../../../ &> /dev/null
fi

# install FastAD
if [ ! -d "$fastadpath" ]; then
    cd libs &> /dev/null
    git clone https://github.com/JamesYang007/FastAD.git
    cd FastAD
    mkdir -p build && cd build
    mkdir -p release && cd release
    cmake \
        -DCMAKE_INSTALL_PREFIX=.. \
        -DCMAKE_BUILD_TYPE=Release \
        -DFASTAD_ENABLE_TEST=OFF ../../
    make install
    cd ../../../../ &> /dev/null
fi
