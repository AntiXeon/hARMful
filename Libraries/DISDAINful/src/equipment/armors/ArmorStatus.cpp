#include "ArmorStatus.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>

using namespace std ;

ArmorStatus::ArmorStatus(Armor* armor, ItemStatus::QUALITY hardness) : ItemStatus() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION" ;
        LogGen::print() ;
    #endif

    assert(armor != 0) ;
    m_armor = armor ;

    if (hardness == ItemStatus::MAXIMAL)
        m_hardness = m_armor -> getHardness() ;
    else
        m_hardness = rand() % (m_armor -> getHardness() + 1) ;
}

ArmorStatus::~ArmorStatus() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " DESTRUCTION" ;
        LogGen::print() ;
    #endif
}

bool ArmorStatus::consume() {
	if (m_hardness > 0) {
		if (rand() % 100 < (m_armor -> getPercentHardness())) {
		    if (m_hardness > 1)
    			m_hardness = m_hardness - 1 ;
			else
			    m_hardness = 0 ;
		}
		
		return true ;
	}
	return false ;
}
