#include <algorithm>
#include "ActionMemory.h"

using namespace std ;

                                                            /** CONSTRUCTORS **/
ActionMemory::ActionMemory(ActionMemory::INITIALIZE init) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION" ;
        LogGen::print() ;
    #endif

    m_hits_before_update= 0 ;
    m_need_update = false ;

    switch(init) {
        default:
        case ActionMemory::INIT_CLEAR:
            initClear() ;
            break ;
        case ActionMemory::INIT_RANDOM_NONE:
            initForNone() ;
            break ;
        case ActionMemory::INIT_RANDOM_PHYSICAL:
            initForPhysical() ;
            break ;
        case ActionMemory::INIT_RANDOM_MAGIC:
            initForMagic() ;
            break ;
        case ActionMemory::INIT_RANDOM_HEALING:
            initForHealing() ;
            break ;
    }
}

ActionMemory::~ActionMemory() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " DESTRUCTION" ;
        LogGen::print() ;
    #endif
}


                                                                 /** SETTERS **/
void ActionMemory::testMostPerformedAction() {
    m_need_update = false ;

    // Determine the most used action by the amount of resets
    if ((m_physical_reset > m_magical_reset) && (m_physical_reset > m_healing_reset)) {
        m_most_used = ActionMemory::ACTION_PHYSICAL ;
    }
    else if ((m_magical_reset > m_physical_reset) && (m_magical_reset > m_healing_reset)) {
        m_most_used = ActionMemory::ACTION_MAGICAL ;
    }
    else if ((m_magical_reset > m_physical_reset) && (m_magical_reset > m_healing_reset)) {
        m_most_used = ActionMemory::ACTION_MAGICAL ;
    }
    else {
        // Scores are used to determine the most used action
        int score_physical = m_physical_hits - (m_magical_hits + m_healing_hits) ;
        int score_magical = m_magical_hits - (m_physical_hits + m_healing_hits) ;
        int score_healing = m_healing_hits - (m_magical_hits + m_physical_hits) ;

        int max_score = max(score_physical, max(score_magical, score_healing)) ;
        if (max_score > (USHRT_MAX / 1000)) {           // 1/1000e of short as minimum
            if (score_physical == max_score)
                m_most_used = ActionMemory::ACTION_PHYSICAL ;
            else if (score_magical == max_score)
                m_most_used = ActionMemory::ACTION_MAGICAL ;
            else if (score_healing == max_score)
                m_most_used = ActionMemory::ACTION_HEALING ;
            else
                m_most_used = ActionMemory::ACTION_NONE ;
        }
        else
            m_most_used = ActionMemory::ACTION_NONE ;
    }
}

void ActionMemory::increasePhysical() {
    if (m_physical_hits < ActionMemory::MAX_ACTIONS) {
        m_physical_hits++ ;
        m_hits_before_update++ ;
        if (m_hits_before_update == 0)       // Request an update every 256 hits
            m_need_update = true ;           // to increase performances
    }
    else {
        m_physical_reset++ ;
        m_physical_hits = 1 ;
        m_need_update = true ;
    }
}

void ActionMemory::increaseMagical() {
    if (m_magical_hits < ActionMemory::MAX_ACTIONS) {
        m_magical_hits++ ;
        m_hits_before_update++ ;
        if (m_hits_before_update == 0)       // Request an update every 256 hits
            m_need_update = true ;           // to increase performances
    }
    else {
        m_magical_reset++ ;
        m_magical_hits = 1 ;
        m_need_update = true ;
    }
}

void ActionMemory::increaseHealing() {
    if (m_healing_hits < ActionMemory::MAX_ACTIONS) {
        m_healing_hits++ ;
        m_hits_before_update++ ;
        if (m_hits_before_update == 0)       // Request an update every 256 hits
            m_need_update = true ;           // to increase performances
    }
    else {
        m_healing_reset++ ;
        m_healing_hits = 1 ;
        m_need_update = true ;
    }
}



                                                         /** INITIALIZATIONS **/
void ActionMemory::initClear() {
    m_physical_reset = 0 ;
    m_physical_hits = 0 ;
    m_magical_reset = 0 ;
    m_magical_hits = 0 ;
    m_healing_reset = 0 ;
    m_healing_hits = 0 ;
    m_most_used = ActionMemory::ACTION_NONE ;
}

void ActionMemory::initForNone() {
    m_physical_reset = rand() % 5 ;
    m_physical_hits = rand() % USHRT_MAX ;
    m_magical_reset = m_physical_reset ;
    m_magical_hits = m_physical_hits ;
    m_healing_reset = m_physical_reset ;
    m_healing_hits = m_physical_hits ;
    m_most_used = ActionMemory::ACTION_NONE ;
}

void ActionMemory::initForPhysical() {
    m_physical_reset = rand() % 5 ;
    m_physical_hits = (rand() % 30000) + 20000 ;
    m_magical_reset = 0 ;
    m_magical_hits = rand() % 5000 ;
    m_healing_reset = 0 ;
    m_healing_hits = rand() % 5000 ;
    m_most_used = ActionMemory::ACTION_PHYSICAL ;
}

void ActionMemory::initForMagic() {
    m_physical_reset = 0 ;
    m_physical_hits = rand() % 5000 ;
    m_magical_reset = rand() % 5 ;
    m_magical_hits = (rand() % 30000) + 20000 ;
    m_healing_reset = 0 ;
    m_healing_hits = rand() % 5000 ;
    m_most_used = ActionMemory::ACTION_MAGICAL ;
}

void ActionMemory::initForHealing() {
    m_physical_reset = 0 ;
    m_physical_hits = rand() % 5000 ;
    m_magical_reset = 0 ;
    m_magical_hits = rand() % 5000 ;
    m_healing_reset = rand() % 5 ;
    m_healing_hits = (rand() % 30000) + 20000 ;
    m_most_used = ActionMemory::ACTION_HEALING ;
}
