#include "Weapon.h"

using namespace std ;

Weapon::Weapon(const string& name,
			   const string& desc,
			   unsigned short damageShoot,
			   unsigned short damageStock,
			   unsigned char variance,
			   unsigned char hardness,
			   unsigned char percentHardness,
			   Weapon::WEAPON_TYPES type,
			   Weapon::DAMAGE_EFFECT effect,
			   MagicElement* el,
			   bool twoHands) : Item(name,
               			 		 	 desc,
               			  		 	 Item::TYPE_WEAPON) {
    assert(damageShoot < 10000) ;
    assert(damageStock < 10000) ;
    assert(percentHardness < 101) ;
    assert(el != 0) ;


	m_damageShoot = damageShoot ;
	m_damageStock = damageStock ;
	m_variance = variance ;
	m_hardness = hardness ;
	m_percentHardness = percentHardness ;
	m_twoHands = twoHands ;
	m_element = el ;
	m_weaponType = type ;
	m_damageShootEffect = effect ;

//    m_hp = 0 ;
//    m_mp = 0 ;
//    m_str = 0 ;
//    m_def = 0 ;
//    m_mag = 0 ;
//    m_psy = 0 ;
//    m_vel = 0 ;
//    m_lck = 0 ;
//    m_prc = 0 ;
}


//void Weapon::setBonus(short hp,
//		              short mp,
//		              char str,
//		              char def,
//		              char mag,
//		              char psy,
//		              char vel,
//		              char lck,
//		              char prc) {
//    m_hp = hp ;
//    m_mp = mp ;
//    m_str = str ;
//    m_def = def ;
//    m_mag = mag ;
//    m_psy = psy ;
//    m_vel = vel ;
//    m_lck = lck ;
//    m_prc = prc ;
//}

short Weapon::evaluateDamageShoot() {
	short damage = m_damageShoot ;
	short variance = (m_variance / 10) ;
	if (variance == 0) variance = 1 ;
	variance = rand() % variance ;

	if (rand() % 2 == 0)
		damage = damage + variance ;
	else
		damage = damage - variance ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " damage on shoot: "
                         << ((damage > 0) ? damage : 0)
                         << " HP" ;
        LogGen::print() ;
    #endif

    return (damage > 0) ? damage : 0 ;
}

short Weapon::evaluateDamageStock() {
    short damage = m_damageStock ;
	short variance = (m_variance / 10) ;
	if (variance == 0) variance = 1 ;
	variance = rand() % variance ;

	if (rand() % 2 == 0)
		damage = damage + variance ;
	else
		damage = damage - variance ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " damage on shove: "
                         << ((damage > 0) ? damage : 0)
                         << " HP" ;
        LogGen::print() ;
    #endif

    return (damage > 0) ? damage : 0 ;
}
