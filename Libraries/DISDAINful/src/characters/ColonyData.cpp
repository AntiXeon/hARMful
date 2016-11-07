#include "ColonyData.h"

using namespace std ;

vector<ColonyData*> ColonyData::ALL_COLONIES ;

ColonyData::ColonyData(const string& name, ColonyStrategy* strategy, ObserverInterface* o) : m_name(name) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << name << " colony CREATION " ;
        LogGen::print() ;
    #endif

    addObserver(o) ;

    m_strategy = strategy ;
    m_isToBeDestroyed = false ;
    m_enemiesAmount = 0 ;
    m_toFight = 0 ;
    ColonyData::ALL_COLONIES.push_back(this) ;
}

ColonyData::~ColonyData() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << m_name << " colony DESTRUCTION " ;
        LogGen::print() ;
    #endif

    // Delete the colony from the enemies lists
    unsigned short max = ColonyData::ALL_COLONIES.size() ;
    short pos = -1 ;
    for (unsigned short i = 0 ; i < max ; i++) {
        // Delete from enemies.
        ColonyData::ALL_COLONIES[i] -> removeEnemieColony(this) ;
        // Find its position in the list of the colonies.
        if (ColonyData::ALL_COLONIES[i] == this) pos = i ;
        // Delete this colony from the ones that were attacking it.
        if (ColonyData::ALL_COLONIES[i] -> m_toFight == this)
            ColonyData::ALL_COLONIES[i] -> m_toFight = 0 ;
    }

    assert (pos > -1) ;
    ColonyData::ALL_COLONIES.erase(ColonyData::ALL_COLONIES.begin() + pos) ;

    delete m_strategy ;
}
