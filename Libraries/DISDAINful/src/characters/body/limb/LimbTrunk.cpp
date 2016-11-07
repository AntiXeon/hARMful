#include "LimbTrunk.h"

using namespace std ;

LimbTrunk::LimbTrunk() : Limb() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION" ;
        LogGen::print() ;
    #endif
}

LimbTrunk::~LimbTrunk() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " DESTRUCTION" ;
        LogGen::print() ;
    #endif
}
