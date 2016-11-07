#include "../AllMagic.h"
#include "BlackMagic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std ;

BlackMagic::BlackMagic(const string& name,
					   const string& desc,
					   unsigned short damages,
					   unsigned short variance,
					   unsigned short mp_used,
					   MagicElement* el) : Magic(name,
					                             desc,
				   							 	 damages,
				   							 	 variance,
				   							 	 mp_used,
				   							 	 el) {}

BlackMagic::~BlackMagic() {}

short BlackMagic::getDamages(MagicElement* target) {
    if (m_variance == 0)
        return m_damages ;

	int value ;
	if ((rand() % 2) == 0)
		value = (m_damages + (rand() % m_variance)) ;
	else
		value = (m_damages - (rand() % m_variance)) ;

    if (value > 9999) value = 9999 ;
    if (value < 0) value = 0 ;

    // Element strength modify the damages caused by the magic
    string elementName = m_element -> getName() ;
    string targetName = target -> getName() ;

    switch(AllMagic::getElementEfficacity(elementName, targetName)) {
        case AllMagic::ELEFF_VEFF:
            value = value * 2 ;
            if (value > 9999) value = 9999 ;
            break ;

        case AllMagic::ELEFF_EFF:
            value = (value * 15) / 10 ;
            if (value > 9999) value = 9999 ;
            break ;

        case AllMagic::ELEFF_BEFF:
            value = (value * 75) / 100 ;
            break ;

        case AllMagic::ELEFF_VBEFF:
            value = (value * 5) / 10 ;
            break ;

        case AllMagic::ELEFF_REGEN:
            value = -value ;
            break ;
    }

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " damage "
                         << ((short) value)
                         << " HP" ;
        LogGen::print() ;
    #endif

	return (short) value ;
}
