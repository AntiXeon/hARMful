#ifndef __ALLMAGIC_H__
#define __ALLMAGIC_H__

    #ifdef DEBUG_MODE
        #include "utils/LogGen.h"
    #endif

#include "pattern/NoCopy.h"
#include "magic.h"

#include <assert.h>
#include <unordered_map>
#include <string>

/**
 * @brief Singleton to easily access all the magic created in the game.
 * @version 1.0 03/05/2013      New singleton management to store the game data
 *                              into the game code itself, not in the library.
 */
class AllMagic : private NoCopy {
    public:
        /**
	     * @brief Efficacity of the elements.
	     * VEFF  = Very Efficient ;
	     * EFF   = Efficient ;
	     * BEFF  = Badly Efficient ;
	     * VBEFF = Very Badly Efficient ;
	     * REG   = Regenerate.
	     */
        enum ELEMENT_EFFICACITY { ELEFF_VEFF = -3, ELEFF_EFF, ELEFF_BEFF, ELEFF_VBEFF, ELEFF_REGEN } ;

        /**
         * @brief Types of magic things...
         * MAG_BLK = Black magic ;
         * MAG_WHT = White magic ;
         * MAG_EFF = Magic effect ;
         * MAG_ELT = Magic element.
         */
		enum MAGIC_TYPE {MAG_BLK = 0, MAG_WHT, MAG_EFF, MAG_ELT} ;


    private:
        /* ** DATA ** */
        /** @brief To know if the singleton has been loaded. */
        static bool Loaded ;

        /** @brief List of all the BlackMagic created in the game. */
        static std::unordered_map<std::string, BlackMagic*> BlackMagicList ;

        /** @brief List of all the WhiteMagic created in the game. */
        static std::unordered_map<std::string, WhiteMagic*> WhiteMagicList ;

        /** @brief List of all the MagicEffect created in the game. */
        static std::unordered_map<std::string, MagicEffect*> MagicEffects ;

        /** @brief List of all the MagicElement created in the game. */
        static std::unordered_map<std::string, MagicElement*> MagicElements ;

		/** @brief 2D matrix of the EFFICACITY for each element. */
		static ELEMENT_EFFICACITY** ELEMENTS_FORCE ;


		/** @brief Unique instance of the singleton. */
		static AllMagic* Singleton ;

        /* ** FUNCTIONS ** */
        /** @brief Private constructor to avoid new instances. */
		AllMagic() throw() ;
		
		/** @brief Destructor to delete dynamic instances. */
		~AllMagic() throw() ;


        /**
         * @brief Check if an element has been added to the singleton before
         *        adding the magic.
         */
        static bool checkElement(Magic* magic) {
            std::string element = magic -> getElement() -> getName() ;
            return (AllMagic::MagicElements.count(element) > 0) ;
        }

        /**
         * @brief Check if the effects of a magic were added to the singleton
         *        before adding the magic.
         */
        static bool checkEffects(Magic* magic) {
            std::unordered_map<MagicEffect*, unsigned char> list ;
            std::string name ;

            list = (magic -> getStatusEffects()) ;
            for (auto& effect : list) {
                name = (effect.first) -> getName() ;
                if(AllMagic::MagicEffects.count(name) == 0) {
                    return false ;
                }
            }

            list = magic -> getClearEffects() ;
            for (auto& effect : list) {
                name = (effect.first) -> getName() ;
                if(AllMagic::MagicEffects.count(name) == 0) {
                    return false ;
                }
            }

            return true ;
        }

	public:
		/**
		 * @brief Get the singleton instance.
		 * @return The unique instance.
		 */
		static AllMagic* getInstance() {
	        if (AllMagic::Singleton == 0)
                AllMagic::Singleton = new AllMagic() ;
            return AllMagic::Singleton ;
		}

        /**
         * @brief To know if the Singleton has been loaded (because others
         * depend on it).
         * @return TRUE if loaded, FALSE else.
         */
        static bool isLoaded() {
            return AllMagic::Loaded ;
        }


        static unsigned int countMagic(MAGIC_TYPE type) ;


                                                             /** BLACK MAGIC **/
        /**
         * @brief Add a new BlackMagic.
         * @param name  The BlackMagic to add to the list.
         */
        static void addBlackMagic(BlackMagic* magic) {
            assert(magic != 0) ;
            assert(AllMagic::BlackMagicList.count(magic -> getName()) == 0) ;
            assert(AllMagic::checkElement(magic)) ;
            assert(AllMagic::checkEffects(magic)) ;

            AllMagic::BlackMagicList[magic -> getName()] = magic ;
        }

        /**
         * @brief Get a BlackMagic.
         * @param name  The name of the BlackMagic to get.
         * @return The searched BlackMagic.
         * @warning Assertion when the name does not exists in the list!
         */
        static BlackMagic* getBlackMagic(const std::string& name) {
            assert(AllMagic::BlackMagicList.count(name) > 0) ;
            return AllMagic::BlackMagicList[name] ;
        }

        /**
         * @brief Count the number of registered BlackMagic.
         * @return Amount of stored BlackMagic.
         */
        static unsigned int countBlackMagic() {
            return AllMagic::BlackMagicList.size() ;
        }


                                                             /** WHITE MAGIC **/
        /**
         * @brief Add a new WhiteMagic.
         * @param name  The WhiteMagic to add to the list.
         */
        static void addWhiteMagic(WhiteMagic* magic) {
            assert(magic != 0) ;
            assert(AllMagic::WhiteMagicList.count(magic -> getName()) == 0) ;
            assert(AllMagic::checkElement(magic)) ;
            assert(AllMagic::checkEffects(magic)) ;

            AllMagic::WhiteMagicList[magic -> getName()] = magic ;
        }

        /**
         * @brief Get a WhiteMagic.
         * @param name  The name of the WhiteMagic to get.
         * @return The searched WhiteMagic.
         * @warning Assertion when the name does not exists in the list!
         */
        static WhiteMagic* getWhiteMagic(const std::string& name) {
            assert(AllMagic::WhiteMagicList.count(name) > 0) ;
            return AllMagic::WhiteMagicList[name] ;
        }

        /**
         * @brief Count the number of registered WhiteMagic.
         * @return Amount of stored WhiteMagic.
         */
        static unsigned int countWhiteMagic() {
            return AllMagic::WhiteMagicList.size() ;
        }


                                                           /** MAGIC EFFECTS **/
        /**
         * @brief Add a new MagicEffect.
         * @param name  The MagicEffect to add to the list.
         */
        static void addMagicEffect(MagicEffect* effect) {
            assert(effect != 0) ;
            assert(AllMagic::MagicEffects.count(effect -> getName()) == 0) ;

            AllMagic::MagicEffects[effect -> getName()] = effect ;
        }

        /**
         * @brief Get a MagicEffect.
         * @param name  The name of the MagicEffect to get.
         * @return The searched MagicEffect.
         * @warning Assertion when the name does not exists in the list!
         */
        static MagicEffect* getMagicEffect(const std::string& name) {
            assert(AllMagic::MagicEffects.count(name) > 0) ;
            return AllMagic::MagicEffects[name] ;
        }

        /**
         * @brief Count the number of registered MagicEffect.
         * @return Amount of stored MagicEffect.
         */
        static unsigned int countMagicEffects() {
            return AllMagic::MagicEffects.size() ;
        }


                                                          /** MAGIC ELEMENTS **/
        /**
         * @brief Add a new MagicElement.
         * @param name  Name of the new MagicElement to add to the list.
         */
        static void addMagicElement(const std::string& name) {
            assert(AllMagic::MagicEffects.count(name) == 0) ;
            AllMagic::MagicElements[name] = new MagicElement(name) ;
        }

        /**
         * @brief Get a MagicElement.
         * @param name  The name of the MagicElement to get.
         * @return The searched MagicElement.
         * @warning Assertion when the name does not exists in the list!
         */
        static MagicElement* getMagicElement(const std::string& name) {
            assert(AllMagic::MagicElements.count(name) > 0) ;
            return AllMagic::MagicElements[name] ;
        }

        /**
         * @brief Count the number of registered MagicElement.
         * @return Amount of stored MagicElement.
         */
        static unsigned int countMagicElements() {
            return AllMagic::MagicElements.size() ;
        }

        /**
         * @brief Create a 2D matrix in which will be defined the efficacities
         * of each element over other ones.
         * @warning It is impossible to create new MagicElements after calling
         * this method.
         */
        static void createMatrixElementsEfficacity() ;

        /**
         * @brief Set the efficacity of an effect on another one.
         * @param applied   The applied effect.
         * @param target    The target effect.
         * @param eff       The efficacity of the applied effect on the target.
         * @warning Call createMatrixElementsEfficacity() before this method!
         */
        static void setElementEfficacity(const std::string& applied,
                                         const std::string& target,
                                         ELEMENT_EFFICACITY eff) {
            assert(AllMagic::MagicElements.count(applied) > 0) ;
            assert(AllMagic::MagicElements.count(target) > 0) ;

            MagicElement* el_applied = (MagicElement*) AllMagic::getMagicElement(applied) ;
            MagicElement* el_target = (MagicElement*) AllMagic::getMagicElement(target) ;

            unsigned char appliedID = el_applied -> getID() ;
            unsigned char targetID = el_target -> getID() ;
            AllMagic::ELEMENTS_FORCE[appliedID][targetID] = eff ;
        }

        /**
         * @brief Get the efficacity of an effect on another one.
         * @param applied   The applied effect.
         * @param target    The target effect.
         * @return The efficacity of the applied effect on the target.
         * @warning Call createMatrixElementsEfficacity() before this method!
         */
        static ELEMENT_EFFICACITY getElementEfficacity(const std::string& applied,
                                                       const std::string& target) {
            assert(AllMagic::MagicElements.count(applied) > 0) ;
            assert(AllMagic::MagicElements.count(target) > 0) ;

            MagicElement* el_applied = (MagicElement*) AllMagic::getMagicElement(applied) ;
            MagicElement* el_target = (MagicElement*) AllMagic::getMagicElement(target) ;

            unsigned char appliedID = el_applied -> getID() ;
            unsigned char targetID = el_target -> getID() ;
            return AllMagic::ELEMENTS_FORCE[appliedID][targetID] ;
        }
} ;

#endif
