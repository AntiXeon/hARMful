#ifndef __INVENTORY_H__
#define __INVENTORY_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include <unordered_map>
#include "AmmoStock.h"
#include "items.h"
#include "weapons.h"
#include "armors.h"

/**
 * @brief Inventory of a character where its items are stored.
 * @version 1.0
 * @version 1.1 20/04/2013  Improved weapons and armors management.
 *                          Only three weapons can be stored at the same time.
 *                          One weapon for each type is allowed.
 *                          Only 99 items of a same type can be stored.
 */
class Inventory {
    protected:
        /** @brief Maximal amount of weapon types. */
        unsigned char m_maxWeapons ;

        /** @brief Maximal amount of items for each type. */
        unsigned char m_maxItems ;

    private:
        /**
         * @brief Weapons owned by the character. Only one instance of each
         *        kind of weapon can be owned.
         */
        std::unordered_map<Weapon*, WeaponStatus*> m_weapons ;

        /**
         * @brief Armors owned by the character. Only one instance of each
         *        kind of armor can be owned.
         */
        std::unordered_map<Armor*, ArmorStatus*> m_armors ;

        /**
         * @brief Weapons owned by the character. It can be owned in different
         *        quantities.
         */
        std::unordered_map<Item*, unsigned char> m_bag ;
        
        /**
         * @brief Part of the inventory dedicated to the ammo management.
         */
        AmmoStock* m_ammostock ;
    
    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Creation of an inventory. */
        Inventory() ;

        /** @brief Destruction of an inventory. */
        virtual ~Inventory() ;

                                                                 /** GETTERS **/
        /** @brief Get the list of weapons. */
        const std::unordered_map<Weapon*, WeaponStatus*>& getWeapons() {
            return m_weapons ;
        }

        /** @brief Get the list of armors. */
        const std::unordered_map<Armor*, ArmorStatus*>& getArmors() {
            return m_armors ;
        }

                                                                     /** ADD **/
        /**
         * @brief Add a weapon.
         * @param weapon    The weapon to add. It can replace one of the same
         *                  type if already stored.
         * @return TRUE if the item can be added, FALSE else (inventory is
         *         full).
         */
        bool add(WeaponStatus* weapon) ;

        /**
         * @brief Add an armor.
         * @param armor     The armor to add. It can replace one of the same
         *                  type if already stored.
         */
        void add(ArmorStatus* armor) ;

        /**
         * @brief Add ammo.
         * @param ammo      Ammo for a firearm.
         * @param quantity  Quantity to add.
         */
        inline void addAmmo(Firearm* ammo, unsigned short quantity = 1) {
            m_ammostock -> add(ammo, quantity) ;
        }

        /**
         * @brief Add items.
         * @param item      Type of item.
         * @param quantity  Quantity to add.
         */
        void add(Item* item, unsigned char quantity = 1) ;

                                                                    /** DROP **/
        /**
         * @brief Drop a weapon from the inventory.
         * @param weapon    The weapon to drop.
         */
        inline void drop(WeaponStatus* weapon) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " drop weapon from WeaponStatus "
                                 << (weapon -> getItem() -> getName()) ;
                LogGen::print() ;
            #endif

            Weapon* item = ((Weapon*) weapon -> getItem()) ;
            drop(item) ;
        }

        /**
         * @brief Drop a weapon from the inventory.
         * @param weapon    The weapon to drop.
         */
        inline void drop(Weapon* weapon) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " drop weapon "
                                 << (weapon -> getName()) ;
                LogGen::print() ;
            #endif

            if (weapon -> getWeaponType() == Weapon::TYPE_FIREARM)
                dropAmmo((Firearm*) weapon) ;

            m_weapons.erase(weapon) ;
        }

        /**
         * @brief Drop an armor from the inventory.
         * @param armor     The armor to drop.
         */
        inline void drop(ArmorStatus* armor) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " drop armor from ArmorStatus "
                                 << (armor -> getItem() -> getName()) ;
                LogGen::print() ;
            #endif

            Armor* item = ((Armor*) armor -> getItem()) ;
            drop(item) ;
        }

        /**
         * @brief Drop an armor from the inventory.
         * @param armor     The armor to drop.
         */
        inline void drop(Armor* armor) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " drop armor "
                                 << (armor -> getName()) ;
                LogGen::print() ;
            #endif

            m_armors.erase(armor) ;
        }

    protected:
        /**
         * @brief Drop all the ammo of a firearm.
         * @param ammo  The type of firearm whose ammo have to be dropped.
         */
        inline void dropAmmo(Firearm* ammo) {
            m_ammostock -> drop(ammo) ;
        }

    public:
        /**
         * @brief Drop some quantities of items.
         * @param item      Type of item to drop.
         */
        inline void drop(Item* item) {
            #ifdef DEBUG_MODE
                assert(item != 0) ;

                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " drop all items "
                                 << (item -> getName()) ;
                LogGen::print() ;
            #endif

            m_bag.erase(item) ;
        }

        /**
         * @brief Drop some quantities of items.
         * @param item      Type of item to drop.
         * @param quantity  Quantity to drop.
         */
        void drop(Item* item, unsigned char quantity) ;

                                                                     /** USE **/
        /**
         * @brief Use some ammo.
         * @param ammo      Ammo for a firearm.
         * @param quantity  Quantity to use.
         * @return Quantity really used, as the requested quantities may be
         *         higher than what is stored.
         */
        inline unsigned short useAmmo(Firearm* ammo, unsigned short quantity = 1) {
            return m_ammostock -> use(ammo, quantity) ;
        }

        /**
         * @brief Use some items.
         * @param item      Item to use.
         * @param quantity  Quantity to use.
         * @return Quantity really used, as the requested quantities may be
         *         higher than what is stored.
         */
        unsigned char use(Item* item, unsigned char quantity = 1) ;


                                                                     /** OWN **/
        /**
         * @brief To know if a weapon of the given type is stored.
         * @param w     The type of weapon to test.
         * @return TRUE if a weapon is stored,
         *         FALSE else.
         */
        inline bool have(Weapon* w) const {
            return (m_weapons.count(w) > 0) ;
        }

        /**
         * @brief To know if an armor of the given type is stored.
         * @param a     The type of armor to test.
         * @return TRUE if an armor is stored,
         *         FALSE else.
         */
        inline bool have(Armor* a) const {
            return (m_armors.count(a) > 0) ;
        }

        /**
         * @brief To know if the ammo of the given type are stored.
         * @param ammo  The type of weapon to test.
         * @return TRUE if the ammo of a weapon are stored,
         *         FALSE else.
         */
        inline bool haveAmmo(Firearm* ammo) {
            return m_ammostock -> have(ammo) ;
        }

        /**
         * @brief To know if an item of the given type is stored.
         * @param item  The type of item to test.
         * @return TRUE if the item is stored,
         *         FALSE else.
         */
        inline bool have(Item* item) {
            return ((m_bag.count(item) > 0) && (m_bag[item] > 0)) ? true : false ;
        }


                                                                   /** COUNT **/
        /**
         * @brief Count owned weapons.
         * @return Amount of owned weapons.
         */
        inline unsigned char countWeapons() const {
            return m_weapons.size() ;
        }
        
        /**
         * @brief Count owned armors.
         * @return Amount of owned armors.
         */
        inline unsigned char countArmors() const {
            return m_armors.size() ;
        }

        /**
         * @brief Count owned ammo for a firearm.
         * @return Amount of owned ammo for the given firearm.
         */
        inline unsigned short countAmmo(Firearm* a) const {
            return m_ammostock -> countAmmo(a) ;
        }

        /**
         * @brief Count owned items.
         * @return Amount of owned items.
         */
        inline unsigned char countItems() const {
            return m_bag.size() ;
        }

        /**
         * @brief Count owned quantities of a given item.
         * @param i     The type of item considered.
         * @return Quantities of a given item.
         */
        inline unsigned char countItems(Item* i) const {
            return m_bag.count(i) ;
        }
} ;
#endif
