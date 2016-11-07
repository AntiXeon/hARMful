#include "AllPotions.h"

using namespace std ;

AllPotions* AllPotions::Singleton = 0 ;

unordered_map<std::string, Potion*> AllPotions::LifePotions ;
unordered_map<std::string, Potion*> AllPotions::ManaPotions ;
unordered_map<std::string, Potion*> AllPotions::CarePotions ;
unordered_map<std::string, Potion*> AllPotions::BonusPotions ;
unordered_map<std::string, Potion*> AllPotions::KOPotions ;


AllPotions::AllPotions() throw() {
    #ifdef DEBUG_MODE
        LogGen::print("Potions singleton creation") ;
    #endif

    assert(AllMagic::isLoaded()) ;
}

AllPotions::~AllPotions() throw() {
    #ifdef DEBUG_MODE
        LogGen::print("Potions singleton destruction") ;
    #endif
}
