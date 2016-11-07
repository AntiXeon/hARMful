#ifndef __DEFAULTWEAPONSTATUS_H__
#define __DEFAULTWEAPONSTATUS_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "WeaponStatus.h"

/**
 * @brief A default weapon is a weapon used by a character as its default
 *        weapon (arms, claws, teeth...). It means the character will use it if
 *        it does not hold another item. It cannot be broken.
 */
class DefaultWeaponStatus : public WeaponStatus {
    public:
        /**
         * @brief Creation of a default weapon with status.
         * @param The generic weapon from which it is an instance.
         */
        DefaultWeaponStatus(Weapon* weapon) ;

        /**
         * @brief Destruction of a default weapon.
         */
        virtual ~DefaultWeaponStatus() ;

        /**
		 * @brief Perte de durete de l'arme.
		 * @return FALSE si l'arme est deja cassee, TRUE sinon.
		 */
        virtual inline bool consume() {
            return true ;
        }
} ;

#endif
