#include "Inventory.h"

using namespace std ;

                                                            /** CONSTRUCTORS **/
Inventory::Inventory() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION" ;
        LogGen::print() ;
    #endif

    m_ammostock = new AmmoStock() ;
    m_maxWeapons = 3 ;
    m_maxItems = 99 ;
}

Inventory::~Inventory() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " DESTRUCTION" ;
        LogGen::print() ;
    #endif

    delete m_ammostock ;
}

                                                                     /** ADD **/
bool Inventory::add(WeaponStatus* weapon) {
    assert(weapon != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " add weapon "
                         << (weapon -> getItem() -> getName()) ;
        LogGen::print() ;
    #endif

    Weapon* def = (Weapon*) weapon -> getItem() ;

    if (m_weapons.count(def) == 0) {                 // Does not have the weapon
        if (m_weapons.size() < m_maxWeapons)         // Has enough space in inv.
            m_weapons[def] = weapon ;                // Store the weapon in inv.
        else
            return false ;                           // Not enought free space !
    }
    
    m_weapons[def] = weapon ;                        // Replace the weapon saved

   return true ;
}

void Inventory::add(ArmorStatus* armor) {
    assert(armor != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " add armor "
                         << (armor -> getItem() -> getName()) ;
        LogGen::print() ;
    #endif

    Armor* def = (Armor*) armor -> getItem() ;
    m_armors[def] = armor ;                         // Replace the armor saved
}

void Inventory::add(Item* item, unsigned char quantity) {
    assert(item != 0) ;
    assert(quantity < 100) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " add item x"
                         << (int) quantity
                         << " "
                         << (item -> getName()) ;
        LogGen::print() ;
    #endif

    if (m_bag.count(item) > 0) {        // Increase quantities if already stored
        unsigned char newQuantities = m_bag[item] + quantity ;  // max = 198 (255 max for an uchar)
        if (newQuantities < m_maxItems)
            m_bag[item] = newQuantities ;
        else
            m_bag[item] = m_maxItems ;
    }
    else                              // Create the entry if not yet saved
        m_bag[item] = quantity ;
}

                                                                    /** DROP **/
void Inventory::drop(Item* item, unsigned char quantity) {
    assert(item != 0) ;
    assert(quantity < 100) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " drop item x"
                         << (int) quantity
                         << " "
                         << (item -> getName()) ;
        LogGen::print() ;
    #endif

    if (m_bag.count(item) > 0) {            // Consider case of owned item only!
        char newQuantities = m_bag[item] - quantity ;   // min = -99 (-128 min for char)
        if (newQuantities > 0)
            m_bag[item] = newQuantities ;
        else
            m_bag.erase(item) ; // Useless to store item not represented anymore
                                // (above all for key objects used only once!)
    }
}

                                                                     /** USE **/
unsigned char Inventory::use(Item* item, unsigned char quantity) {
    assert(item != 0) ;

    unsigned char ret ;
    if (m_bag.count(item) > 0) {
        if (m_bag[item] > quantity) {   // Enough quantities in the inventory
            m_bag[item] -= quantity ;
            ret = quantity ;
        }
        else {                          // Not enough, take every thing...
            ret = m_bag[item] ;
            m_bag[item] = 0 ;
        }
    }
    else                                // The item is not stored, nothing used
        ret = 0 ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " use item x"
                         << (int) ret
                         << " "
                         << (item -> getName()) ;
        LogGen::print() ;
    #endif

    return ret ;
}
