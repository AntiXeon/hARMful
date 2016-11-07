#include "FirearmStatus.h"

#include <stdlib.h>

using namespace std ;

FirearmStatus::FirearmStatus(Firearm* weapon, ItemStatus::QUALITY hardness) : WeaponStatus(weapon, hardness) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION" ;
        LogGen::print() ;
    #endif

    setTimers() ;

    if (hardness == ItemStatus::MAXIMAL)
        m_ammoRemaining = weapon -> getAmmoMax() ;
    else
        m_ammoRemaining = rand() % (weapon -> getAmmoMax()) ;
}

FirearmStatus::~FirearmStatus() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " DESTRUCTION" ;
        LogGen::print() ;
    #endif
}
