#include "Shield.h"

using namespace std ;

Shield::Shield(std::string name,
	           std::string desc,
	           unsigned char parade,
	           unsigned char hardness,
	           unsigned char percent_hardness,
	           MagicElement* el) : Armor(name,
	                                     desc,
	                                     hardness,
	                                     percent_hardness,
	                                     el),
                                   m_parade(parade) {
   m_type = Armor::TYPE_SHIELD ;
}
