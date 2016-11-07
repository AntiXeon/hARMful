#include "Helmet.h"

using namespace std ;

Helmet::Helmet(std::string name,
	           std::string desc,
	           unsigned char hardness,
	           unsigned char percent_hardness,
	           MagicElement* el) : Armor(name,
	                                     desc,
	                                     hardness,
	                                     percent_hardness,
	                                     el) {
   m_type = Armor::TYPE_HELMET ;
}
