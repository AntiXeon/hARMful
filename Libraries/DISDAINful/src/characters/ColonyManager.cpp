#include "ColonyManager.h"

using namespace std ;

unsigned short ColonyManager::CountColonies = 0 ;

std::vector<ColonyManager*> ColonyManager::DestroyList ;

ColonyManager::ColonyManager(const string& name, ColonyStrategy* strategy) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << name << " manager CREATION" ;
        LogGen::print() ;
    #endif

    m_data = new ColonyData(name, strategy, this) ;

    // "Register" the colony
    ColonyManager::CountColonies++ ;
}

ColonyManager::~ColonyManager() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << (m_data -> getName()) << " manager DESTRUCTION" ;
        LogGen::print() ;
    #endif

    unsigned short max = m_characters.size() ;
    for (unsigned short i = 0 ; i < max ; i++) {
        delete m_characters[i] ;
    }

    delete m_data ;

    // "Unregister" the colony
    ColonyManager::CountColonies-- ;
}
