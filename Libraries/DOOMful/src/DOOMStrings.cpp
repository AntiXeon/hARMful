/**
 * DOOMStrings.cpp
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *
 * @Author:      Denis CARLUS
 * @Created on:  11-Nov-2016
 * @Last change: 14-Nov-2016
 */

#include <DOOMStrings.hpp>

/**
 * Tag to be detected when using xgettext on this file.
 * @param  str The string to be detected by xgettext.
 * @return     The same string as input.
 */
#define i18n(str) str

namespace Doom {
    namespace Texts {
        /* Keep the space at the end of the string (filepath printed after). */
        const std::string File_NotOpened =        i18n("Unable to open file at ") ;
    } ;
} ;
