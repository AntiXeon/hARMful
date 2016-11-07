#ifndef __PHYSIQUE_H__
#define __PHYSIQUE_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include "../limb/Limb.h"
#include "../Body.h"
#include "../equipment/Equipment.h"

/**
 * @brief Physique is the external aspect of a character. This class (interface)
 *        has as aim to abstract all the elements relative to the physique in
 *        order to improve the evolutivity of the software. Classes such as
 *        artificial intelligence ones can be used for every kind of character
 *        independantly of their physique.
 * @version 1.0 04/04/2013
 */
class Physique {
    protected:
        /** @brief Body of the character. */
        Body* m_body ;

        /** @brief Equipment of the character. */
        Equipment* m_equipment ;

    public:
        Physique() {}

        virtual ~Physique() {}

                                                         /** BODY MANAGEMENT **/
        /** @brief Set all blown off limbs to treated limbs. */
        virtual void setBlownOffToTreatedLimbs() = 0 ;

        /** @brief Heal fractured limbs. */
        virtual void healFracturedLimbs(unsigned char points) = 0 ;

        /** @brief Heal limbs and blown off limbs are back. */
        virtual void fullBodyRestore() = 0 ;

        /**
         * @brief To know if the body is seriously damaged.
         * @return TRUE if some limbs are blown off or the trunk is fractured.
         */
        virtual bool seriouslyDamagedBody() = 0 ;

        /**
         * @brief To know if the body does not allow the character to continue
         * to live.
         * @return TRUE if the body situation is lethal, FALSE else.
         */
        virtual bool lethalCondition() {
            return m_body -> getMainHead() -> isBlownOff() ;
        }

        /**
         * @brief Damage the body of the character.
         * @param points    Points losed by a limb.
         * @param effect    Type of damage on the limb.
         */
        virtual void damageBody(unsigned char points, Weapon::DAMAGE_EFFECT effect) = 0 ;


                                                    /** EQUIPMENT MANAGEMENT **/
        /**
         * @brief Get the equipment of the character (armors and weapons worn).
         * @return The equipment of the character.
         */
        Equipment* getEquipment() {
            return m_equipment ;
        }

        /**
         * @brief Get the weapon the character has in hands or another limb
         *         used to take items...
         */
        virtual ItemStatus* getHeldItem() = 0 ;

        /**
         * @brief Set the weapon the character has in hands or another limb
         *        used to take items...
         * @return item     The item hold by the character.
         */
        virtual void setHeldItem(ItemStatus* item) = 0 ;

        /** @brief Do not use the held item anymore. */
        virtual void clearHeldItem(ItemStatus* item) = 0 ;

        /** @brief Get the element of the character. */
        virtual MagicElement* getElement() = 0 ;
} ;

#endif
