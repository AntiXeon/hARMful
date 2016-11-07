#include <DemoTranslate.h>
#include <libintl.h>


namespace DemoTranslate {
    char* Translate(const char* str) {
        return gettext(str) ;
    }
} ;
