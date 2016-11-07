#include <iostream>
#include <DemoLib.h>


int main() {
    DemoLib::Init("../i18n") ;

    DemoClass dc1(0) ;
    DemoClass dc2(0) ;
    DemoClass dc3(2) ;
    DemoClass dc4(3) ;

    dc1.isEqual(&dc2) ;
    dc1.isEqual(&dc4) ;
    dc1.isEqual(NULL) ;
    dc1.isDifferent(NULL) ;
    dc1.copy(NULL) ;

    return 0 ;
}
