#ifndef __ALLWEAPONS_H__
#define __ALLWEAPONS_H__

    #ifdef DEBUG_MODE
        #include "utils/LogGen.h"
    #endif

#include "pattern/NoCopy.h"
#include "AllMagic.h"
#include "weapons.h"

#include <assert.h>
#include <unordered_map>
#include <string>

class AllWeapons : private NoCopy {
    private:
        /* ** DATA ** */
        /** @brief List of all the default weapons created in the game. */
        static std::unordered_map<std::string, DefaultWeaponStatus*> DefaultWeapons ;

        /** @brief List of all the Weapons created in the game. */
        static std::unordered_map<std::string, Weapon*> Weapons ;


		/** @brief Unique instance of the singleton. */
		static AllWeapons* Singleton ;


        /* ** FUNCTIONS ** */
		/** @brief Private constructor to avoid new instances. */
		AllWeapons() throw() ;
		
		/** @brief Destructor to delete dynamic instances. */
		~AllWeapons() throw() ;

    public:
		/**
		 * @brief Get the singleton instance.
		 * @return The unique instance.
		 */
		static AllWeapons* getInstance() {
	        if (AllWeapons::Singleton == 0)
                AllWeapons::Singleton = new AllWeapons() ;
            return AllWeapons::Singleton ;
		}


                                                         /** DEFAULT WEAPONS **/
        /**
         * @brief Add a new DefaultWeaponStatus.
         * @param name  The DefaultWeaponStatus to add to the list.
         */
        static void addDefaultWeapon(DefaultWeaponStatus* weapon) {
            assert(weapon != 0) ;

            std::string name = weapon -> getItem() -> getName() ;

            // The weapon description must have been added
            assert(AllWeapons::Weapons.count(name) > 0) ;
            assert(AllWeapons::DefaultWeapons.count(name) == 0) ;

            AllWeapons::DefaultWeapons[name] = weapon ;
        }

        /**
         * @brief Get a DefaultWeaponStatus.
         * @param name  The name of the DefaultWeaponStatus to get.
         * @return The searched DefaultWeaponStatus.
         * @warning Assertion when the name does not exists in the list!
         */
        static DefaultWeaponStatus* getWeaponStatus(const std::string& name) {
            assert(AllWeapons::DefaultWeapons.count(name) > 0) ;
            return AllWeapons::DefaultWeapons[name] ;
        }


                                                                 /** WEAPONS **/
        /**
         * @brief Add a new Weapon.
         * @param name  The Weapon to add to the list.
         */
        static void addWeapon(Weapon* weapon) {
            assert(weapon != 0) ;
            std::string name = weapon -> getName() ;
            assert(AllWeapons::Weapons.count(name) == 0) ;

            AllWeapons::Weapons[name] = weapon ;
        }

        /**
         * @brief Get a DefaultWeaponStatus.
         * @param name  The name of the DefaultWeaponStatus to get.
         * @return The searched DefaultWeaponStatus.
         * @warning Assertion when the name does not exists in the list!
         */
        static Weapon* getWeapon(const std::string& name) {
            assert(AllWeapons::Weapons.count(name) > 0) ;
            return AllWeapons::Weapons[name] ;
        }
} ;

#endif
