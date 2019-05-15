#!/bin/sh

CURRENT_DIR=$(pwd)

# Generate the GLSL embedded source files (C++).
cd ../Tools/GLSL2Cpp/build && cmake . && make && cd ../bin && ./glsl2cpp.exe

# Build the project.
cd $CURRENT_DIR
cmake . && make -j
