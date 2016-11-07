#include "WhiteMagic.h"
#include <stdlib.h>

using namespace std ;

WhiteMagic::WhiteMagic(const string& name,
                       const string& desc,
					   unsigned short heal,
					   unsigned short variance,
					   unsigned short mp_used,
					   MagicElement* el,
					   WhiteMagic::TYPE type,
					   WhiteMagic::POWER_LIMBS power) : Magic(name,
				                                              desc,
					                   					 	  heal,
					                   					 	  variance,
					                   						  mp_used,
					                   						  el) {
    m_type = type ;
    m_power = power ;
}

WhiteMagic::~WhiteMagic() {}

unsigned short WhiteMagic::heal() {
    if (m_variance == 0)
        return m_damages ;

	short value ;
    if ((rand() % 2) == 0)
	    value = (m_damages + (rand() % m_variance)) ;
    else
	    value = (m_damages - (rand() % m_variance)) ;
	
	if (value < 0) return 0 ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " healing "
                         << ((short) value)
                         << " HP" ;
        LogGen::print() ;
    #endif

	return value ;
}
