#include "WeaponStatus.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>

using namespace std ;

WeaponStatus::WeaponStatus(Weapon* weapon, ItemStatus::QUALITY hardness) : ItemStatus() {
    assert(weapon != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION" ;
        LogGen::print() ;
    #endif

    m_wpn = weapon ;
    m_state = WeaponStatus::STATE_OK ;

    if (hardness == ItemStatus::MAXIMAL)
        m_hardness = m_wpn -> getHardness() ;
    else
        m_hardness = rand() % (m_wpn -> getHardness() + 1) ;
}

WeaponStatus::~WeaponStatus() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " DESTRUCTION" ;
        LogGen::print() ;
    #endif
}


bool WeaponStatus::consume() {
	if (m_hardness > 0) {
		if (rand() % 100 < (m_wpn -> getPercentHardness())) {
		    if (m_hardness > 1) {
                #ifdef DEBUG_MODE
                    LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                     << "The " << m_wpn << " still is OK" ;
                    LogGen::print() ;
                #endif

        		m_state = WeaponStatus::STATE_OK ;
    			m_hardness = m_hardness - 1 ;
			}
			else {
                #ifdef DEBUG_MODE
                    LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                     << "The " << m_wpn << " is broken!" ;
                    LogGen::print() ;
                #endif

	    		m_state = WeaponStatus::STATE_BROKEN ;
			    m_hardness = 0 ;
		    }
		}
		return true ;
	}

	return false ;
}
