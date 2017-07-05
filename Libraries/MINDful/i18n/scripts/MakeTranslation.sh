#!/bin/sh

# @Author: Denis CARLUS
# @Date:   12-Nov-2016
# @Filename: MakeTranslation.sh
# @Last modified time: 12-Nov-2016
# @License: GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007

PO_DIR="../po" ;

if [[$# -ne 2]]; then
    echo "Use the command line:\n"
    echo "./$0 <domain> <locale>"
else
    mkdir -p ${PO_DIR}/$2
    msginit --input=../$1.pot --locale=$2 --output=$PO_DIR/$2/$1.po
fi
