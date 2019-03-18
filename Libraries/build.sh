#!/bin/sh

CURRENT_DIR=$(pwd)

# Generate the GLSL embedded source files (C++).
cd ../Tools/GLSL2Cpp && cmake . && make
./glsl2cpp

# Build the project.
cd $CURRENT_DIR
cmake . && make -j
