#!/bin/sh

CURRENT_DIR=$(pwd)

cd ./HOPEful/build && ./generate_shaders.sh

# Build the project.
cd $CURRENT_DIR
cmake . $1 && make -j
