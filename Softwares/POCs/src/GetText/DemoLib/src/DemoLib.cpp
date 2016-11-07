#include <DemoLib.h>
#include <libintl.h>
#include <locale.h>


namespace DemoLib {

    void Init(const char* path) {
        setlocale(LC_ALL, "") ;
        bindtextdomain("DemoLib", path) ;
        textdomain("DemoLib") ;
    }

} ;
