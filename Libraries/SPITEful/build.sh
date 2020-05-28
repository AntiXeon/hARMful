#!/bin/sh

CURRENT_DIR=$(pwd)

cd ./lib/hARMful/Libraries/HOPEful/build && ./generate_shaders.sh

# Build the project.
cd $CURRENT_DIR
cmake . -DDEBUG=false && make -j
