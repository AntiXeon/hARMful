#include "DefaultWeaponStatus.h"
#include <assert.h>

using namespace std ;

DefaultWeaponStatus::DefaultWeaponStatus(Weapon* weapon) : WeaponStatus(weapon, ItemStatus::MAXIMAL) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION" ;
        LogGen::print() ;
    #endif

    assert((weapon -> getWeaponType()) == Weapon::TYPE_DEFAULT) ;
    m_hardness = 1 ;
}

DefaultWeaponStatus::~DefaultWeaponStatus() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " DESTRUCTION" ;
        LogGen::print() ;
    #endif
}
