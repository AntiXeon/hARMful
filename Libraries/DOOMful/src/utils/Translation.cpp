/**
 * Translation.cpp
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *
 * @Author:      Denis CARLUS
 * @Created on:  11-Nov-2016
 * @Last change: 13-Nov-2016
 */

#include <utils/Translation.hpp>
#include <libintl.h>
#include <clocale>

namespace Doom {
    namespace Translation {
        void Init(const std::string domain, const std::string& path) {
            setlocale(LC_ALL, "") ;
            bindtextdomain(domain.c_str(), path.c_str()) ;
            textdomain(domain.c_str()) ;
        }

        std::string Get(const std::string& str) {
            return std::string(gettext(str.c_str())) ;
        }
    } ;
} ;
