#ifndef __FIREARM_H__
#define __FIREARM_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include "../Weapon.h"

#include <string>
#include <stdlib.h>

/**
 * @brief A firearm uses ammo to make most of damage. It can be used to repulse
 *        assailants and make few damage.
 * @version 1.0
 * @version 2.0 20/04/2013
 */
class Firearm : public Weapon {
    protected:
        /** @brief Maximal distance to hit a character. */
        unsigned short m_distanceShoot ;

        /** @brief Maximal amount of ammo the cylinder can have. */
        unsigned char m_ammoMax ;

        /** @brief Amount of ammo used at each shot. */
        unsigned char m_ammoUsed ;


    public:
                                                            /** CONSTRUCTORS **/
        /**
		 * @brief Creation of a firearm.
		 * @param name				Name of the weapon.
		 * @param desc				Description of the weapon.
		 * @param damageShoot		Damage points induced by the weapon when
		 *                          shooting.
		 * @param damageStock       Damage points induced by the weapon when
		 *                          shoving a character with the stock.
		 * @param variance			Damage variance.
		 * @param hardness 			Hardness of the weapon, decreased by
		 *                          reloadings and shove action.
		 * @param percentHardness	Possibility that the weapon get damage.
		 * @param twoHands			To know if the weapon is held with two hands.
		 * @param distanceShoot     Distance maximal to hit a character.
		 * @param ammoMax		    Maximal amount of ammo the cylinder can have.
		 * @param ammoUsed		    Amount of ammo used at each shot.
		 */
		Firearm(const std::string& name,
				const std::string& desc,
			    unsigned short damageShoot,
			    unsigned short damageStock,
			    unsigned char variance,
			    unsigned char hardness,
			    unsigned char percentHardness,
			    unsigned short distanceShoot,
			    unsigned char ammoMax,
			    unsigned char ammoUsed,
			    MagicElement* el,
			    bool twoHands = false) ;

        /** @brief Destruction of a firearm. */
        virtual ~Firearm() {}


                                                                 /** GETTERS **/
        /**
         * @brief Get the maximal distance to hit a character.
         */
        unsigned short getDistanceShoot() const {
            return m_distanceShoot ;
        }

        /**
         * @brief Get the maximal amount of ammo the cylinder can have.
         */
        unsigned char getAmmoMax() const {
            return m_ammoMax ;
        }

        /**
         * @brief Get the amount of ammo used by the weapon at each round.
         */
        unsigned char getAmmoUsed() const {
            return m_ammoUsed ;
        }
} ;

#endif
