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

SOURCES=$(realpath ./src)

OUTPUT="./output"

OUTPUT_INLINED=$OUTPUT"/OGL3"
mkdir -p $OUTPUT_INLINED
OUTPUT_INLINED=$(realpath $OUTPUT_INLINED)

cd $SOURCES
make
cd $HOME

cd ./API
for file in *.gl
do
    $HOME/bin/inliner "$file" $OUTPUT_INLINED/${file:0:(-3)}".inl" > null
    echo "#include \"OGL3/$file\"" >> .$OUTPUT/OGL3.h
done

cd $SOURCES
make clean
cd $HOME

echo "DONE: the files are generated in $OUTPUT directory."
