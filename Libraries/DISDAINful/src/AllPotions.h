#ifndef __ALLPOTIONS_H__
#define __ALLPOTIONS_H__

    #ifdef DEBUG_MODE
        #include "utils/LogGen.h"
    #endif

#include "pattern/NoCopy.h"
#include "AllMagic.h"
#include "items.h"

#include <assert.h>
#include <unordered_map>
#include <string>

/**
 * @brief Singleton to easily access all the potions created in the game.
 * @version 1.0 03/05/2013      New singleton management to store the game data
 *                              into the game code itself, not in the library.
 */
class AllPotions : private NoCopy {
    private:
        /* ** DATA ** */
        /** @brief List of all the LifePotion created in the game. */
        static std::unordered_map<std::string, Potion*> LifePotions ;

        /** @brief List of all the Potions created in the game for mana healing. */
        static std::unordered_map<std::string, Potion*> ManaPotions ;

        /** @brief List of all the Potions created in the game for effects healing. */
        static std::unordered_map<std::string, Potion*> CarePotions ;

        /** @brief List of all the Potions created in the game for bonus providing. */
        static std::unordered_map<std::string, Potion*> BonusPotions ;

        /** @brief List of all the Potions created in the game for KO healing. */
        static std::unordered_map<std::string, Potion*> KOPotions ;


		/** @brief Unique instance of the singleton. */
		static AllPotions* Singleton ;


        /* ** FUNCTIONS ** */
		/** @brief Private constructor to avoid new instances. */
		AllPotions() throw() ;
		
		/** @brief Destructor to delete dynamic instances. */
		~AllPotions() throw() ;

    public:
		/**
		 * @brief Get the singleton instance.
		 * @return The unique instance.
		 */
		static AllPotions* getInstance() {
	        if (AllPotions::Singleton == 0)
                AllPotions::Singleton = new AllPotions() ;
            return AllPotions::Singleton ;
		}


                                                                 /** POTIONS **/
        /**
         * @brief Add a new Potion.
         * @param name  The Potion to add to the list.
         * @param type  Type of the Potion.
         */
        static void addPotion(Potion* potion) {
            assert(potion != 0) ;
            std::string name = potion -> getName() ;

            Potion::TYPE type = potion -> getType() ;
            switch(type) {
                case Potion::TYPE_LIFE :
                    assert(AllPotions::LifePotions.count(name) == 0) ;
                    AllPotions::LifePotions[name] = potion ;
                    break ;
                case Potion::TYPE_MANA :
                    assert(AllPotions::ManaPotions.count(name) == 0) ;
                    AllPotions::ManaPotions[name] = potion ;
                    break ;
                case Potion::TYPE_CARE :
                    assert(AllPotions::CarePotions.count(name) == 0) ;
                    AllPotions::CarePotions[name] = potion ;
                    break ;
                case Potion::TYPE_BONUS :
                    assert(AllPotions::BonusPotions.count(name) == 0) ;
                    AllPotions::BonusPotions[name] = potion ;
                    break ;
                case Potion::TYPE_KO :
                    assert(AllPotions::KOPotions.count(name) == 0) ;
                    AllPotions::KOPotions[name] = potion ;
                    break ;
            }
        }

        /**
         * @brief Get a Potion.
         * @param name  The name of the Potion to get.
         * @param type  Type of the searched Potion.
         * @return The searched Potion.
         * @warning Assertion when the name does not exists in the list!
         */
        static Potion* getPotion(const std::string& name, Potion::TYPE type) {
            switch(type) {
                case Potion::TYPE_LIFE :
                    assert(AllPotions::LifePotions.count(name) > 0) ;
                    return AllPotions::LifePotions[name] ;
                    break ;
                case Potion::TYPE_MANA :
                    assert(AllPotions::ManaPotions.count(name) > 0) ;
                    return AllPotions::ManaPotions[name] ;
                    break ;
                case Potion::TYPE_CARE :
                    assert(AllPotions::CarePotions.count(name) > 0) ;
                    return AllPotions::CarePotions[name] ;
                    break ;
                case Potion::TYPE_BONUS :
                    assert(AllPotions::BonusPotions.count(name) > 0) ;
                    return AllPotions::BonusPotions[name] ;
                    break ;
                case Potion::TYPE_KO :
                    assert(AllPotions::KOPotions.count(name) > 0) ;
                    return AllPotions::KOPotions[name] ;
                    break ;
            }

            assert(false) ;
        }

        /**
         * @brief Get the list of registered Potions.
         * @return The list of all the potions.
         */
        static const std::unordered_map<std::string, Potion*>& getPotions(Potion::TYPE type) {
            switch(type) {
                case Potion::TYPE_LIFE :
                    return AllPotions::LifePotions ;
                    break ;
                case Potion::TYPE_MANA :
                    return AllPotions::ManaPotions ;
                    break ;
                case Potion::TYPE_CARE :
                    return AllPotions::CarePotions ;
                    break ;
                case Potion::TYPE_BONUS :
                    return AllPotions::BonusPotions ;
                    break ;
                case Potion::TYPE_KO :
                    return AllPotions::KOPotions ;
                    break ;
                default:
                    assert(false) ;
                    break ;
            }

            assert(false) ;
        }
} ;

#endif
