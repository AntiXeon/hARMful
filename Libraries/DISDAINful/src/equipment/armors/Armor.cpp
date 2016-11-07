#include "Armor.h"

using namespace std ;

Armor::Armor(std::string name,
	         std::string desc,
	         unsigned char hardness,
	         unsigned char percent_hardness,
	         MagicElement* el) : Item(name, desc, Item::TYPE_ARMOR),
	                             m_hardness(hardness),
	                             m_percent_hardness(percent_hardness) {
    m_element = el ;

    m_hp = 0 ;
    m_mp = 0 ;
    m_str = 0 ;
    m_def = 0 ;
    m_mag = 0 ;
    m_psy = 0 ;
    m_vel = 0 ;
    m_lck = 0 ;
    m_prc = 0 ;
}

void Armor::consume() {
	if (m_hardness > 0) {
	    short hardness = m_hardness / 10 ;
	    if (hardness == 0) hardness = 1 ;
		int random_loss = (rand() % hardness) + 1 ;
		if (rand() % 100 < m_percent_hardness)
			m_percent_hardness = m_percent_hardness - random_loss ;

		// Les points de durete ne peuvent etre negatifs
		if (m_hardness < 0)
			m_hardness = 0 ;
	}
}

void Armor::setBonus(short hp,
		             short mp,
		             char str,
		             char def,
		             char mag,
		             char psy,
		             char vel,
		             char lck,
		             char prc) {
    m_hp = hp ;
    m_mp = mp ;
    m_str = str ;
    m_def = def ;
    m_mag = mag ;
    m_psy = psy ;
    m_vel = vel ;
    m_lck = lck ;
    m_prc = prc ;
}
