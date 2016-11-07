#include "Body.h"

Body::Body() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION" ;
        LogGen::print() ;
    #endif

    m_mainHead = new LimbHead() ;
    m_trunk = new LimbTrunk() ;
}

Body::~Body() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " DESTRUCTION" ;
        LogGen::print() ;
    #endif

    delete m_trunk ;
    delete m_mainHead ;
}
