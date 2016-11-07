#include "hARMful.h"

using namespace std ;

hARMful::hARMful() throw() {
    #ifdef DEBUG_MODE
        LogGen::print("hARMful creation") ;
    #endif

    // Create the other singletons
    AllMagic::getInstance() ;
    AllPotions::getInstance() ;
    AllWeapons::getInstance() ;
}

hARMful::~hARMful() throw() {
    #ifdef DEBUG_MODE
        LogGen::print("hARMful destruction") ;
    #endif
}
