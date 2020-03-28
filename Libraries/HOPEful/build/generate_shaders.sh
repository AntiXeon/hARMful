#!/bin/sh

harmfulDir=$(realpath ../../..)

# Generate the GLSL embedded source files (C++).
cd ../../../Tools/GLSL2Cpp/build && cmake . && make && cd ../bin && ./glsl2cpp.exe $harmfulDir
