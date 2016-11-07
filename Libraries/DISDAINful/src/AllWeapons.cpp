#include "AllWeapons.h"

using namespace std ;

AllWeapons* AllWeapons::Singleton = 0 ;

unordered_map<std::string, DefaultWeaponStatus*> AllWeapons::DefaultWeapons ;
unordered_map<std::string, Weapon*> AllWeapons::Weapons ;

AllWeapons::AllWeapons() throw() {
    #ifdef DEBUG_MODE
        LogGen::print("Weapons singleton creation") ;
    #endif

    assert(AllMagic::isLoaded()) ;
}

AllWeapons::~AllWeapons() throw() {
    #ifdef DEBUG_MODE
        LogGen::print("Weapons singleton destruction") ;
    #endif
}
