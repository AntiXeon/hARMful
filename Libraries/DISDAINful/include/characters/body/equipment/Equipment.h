#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include <assert.h>
#include <time.h>
#include "../../../equipment/inventory/Inventory.h"
#include "../../../equipment/weapons/DefaultWeaponStatus.h"

/**
 * @brief Equipment of a character. It makes the link between the body and the
 *        inventory of the character to make the character able to wear weapons
 *        and armors.
 * @see Body
 * @see Character
 * @see Inventory
 * @version 1.0 01/04/2013
 */
class Equipment {
    protected:
        /** @brief The default weapon used by the character. */
        DefaultWeaponStatus* m_defaut ;

		/** @brief Helmet, protection for the main head. */
        ArmorStatus* m_mainHelmet ; // @TODO change to HelmetStatus when available

    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Creation of the character's equipment. */
        Equipment() ;

        /** @brief Destruction of the character's equipment. */
        virtual ~Equipment() ;

                                                                 /** GETTERS **/
        /**
         * @brief Get the helmet used for the main head.
         * @return Helmet used for the main head.
         */
        inline ArmorStatus* getMainHelmet() const {
            return m_mainHelmet ;
        }

        /**
         * @brief Get the default weapon used by the character.
         * @return The defaut weapon used by the character.
         */
        virtual inline DefaultWeaponStatus* getDefaultWeapon() {
            return m_defaut ;
        }

                                                                 /** SETTERS **/
        /**
         * @brief Set the helmet used by the character for its main head.
         * @param armor Pointer to the helmet.
         */
        inline void setMainHelmet(ArmorStatus* armor) {
            m_mainHelmet = armor ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " set main helmet : "
                                 << (m_mainHelmet -> getItem() -> getName()) ;
                LogGen::print() ;
            #endif
        }
} ;

#endif
