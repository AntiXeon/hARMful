# @Author: Denis CARLUS
# @Date:   10-Nov-2016
# @Filename: convert.sh
# @Last modified by:   Denis CARLUS
# @Last modified time: 18-Nov-2016
# @License: GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007

# This file is part of hARMful.
#
# hARMful is free software: you can redistribute
# it and/or modify it under the terms of the GNU
# General  Public License  as published  by  the
# Free Software Foundation,  either version 3 of
# the  License,  or (at your option)  any  later
# version.
#
# hARMful is  distributed in  the hope  that  it
# will  be  useful, but  WITHOUT  ANY  WARRANTY;
# without   even   the   implied   warranty   of
# MERCHANTABILITY  or  FITNESS FOR  A PARTICULAR
# PURPOSE.  See the  GNU General  Public License
# for more details.
#
# You  should have  received a  copy of  the GNU
# General  Public  License  along  with hARMful.
# If not, see <http://www.gnu.org/licenses/>.


# FILE:     Convert OpenGL API to inline C++ functions.
# AUTHOR:   Denis CARLUS
# VERSION:  1.0     2016-10-31

#!/bin/sh

HOME=$(realpath .)
NAMESPACE="Hope"
GL_VERSION="OGL3"

SOURCES=$(realpath ./src)

OUTPUT="./output"
OUTPUT=$(realpath $OUTPUT)
OUTPUT_HEADER=$OUTPUT/$GL_VERSION.hpp

OUTPUT_INLINED="$OUTPUT/$GL_VERSION"
mkdir -p $OUTPUT_INLINED
OUTPUT_INLINED=$(realpath $OUTPUT_INLINED)

# Compile the converter app
cd $SOURCES
make
cd $HOME

# Convert .gl files
cd ./API
for file in *.gl
do
    $HOME/bin/inliner "$file" $OUTPUT_INLINED/${file:0:(-3)}".inl" "Types" > null
done

# Aggregate .inl files in a single .hpp
cd $OUTPUT_INLINED

touch $OUTPUT_HEADER
echo "#include \"GL/glew.h\"" >> $OUTPUT_HEADER
echo "#include \"GL/gl.h\"" >> $OUTPUT_HEADER
echo "" >> $OUTPUT_HEADER
echo "namespace $NAMESPACE {" >> $OUTPUT_HEADER
echo -e "\tnamespace $GL_VERSION {" >> $OUTPUT_HEADER
echo -e "\t\tnamespace Types {" >> $OUTPUT_HEADER
cat $SOURCES/types.convert >> $OUTPUT_HEADER
echo -e "\t\t} ;" >> $OUTPUT_HEADER
echo "" >> $OUTPUT_HEADER
for file in $OUTPUT_INLINED/*.inl
do
    FILENAME=$(basename $file)
    echo -e '\t\t#include \"$GL_VERSION/"$FILENAME"\"' >> $OUTPUT_HEADER
done
echo -e "\t} ;" >> $OUTPUT_HEADER
echo "} ;" >> $OUTPUT_HEADER
echo "" >> $OUTPUT_HEADER
echo "// To anticipate the use of Vulkan in future versions of the library." >> $OUTPUT_HEADER
echo "using namespace $NAMESPACE::$GL_VERSION::Types ;" >> $OUTPUT_HEADER

# Clear the directory
cd $SOURCES
make clean
cd $HOME

echo "DONE: the files are generated in $OUTPUT directory."
