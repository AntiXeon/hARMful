#!/bin/sh

# @Author: Denis CARLUS
# @Date:   12-Nov-2016
# @Filename: CompileTranslation.sh
# @Last modified time: 12-Nov-2016
# @License: GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007

PO_DIR="../po" ;
LOCALE_DIR="../locale" ;
MESSAGES_DIR="LC_MESSAGES"

# if [[$# -ne 2]]; then
#     echo "Use the command line:\n"
#     echo "./$0 <domain> <locale>"
# else
    mkdir -p ${LOCALE_DIR}/$2/${MESSAGES_DIR}
    msgfmt --output-file=${LOCALE_DIR}/$2/${MESSAGES_DIR}/$1.mo ${PO_DIR}/$2/$1.po
# fi
