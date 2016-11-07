#ifndef __WEAPONSTATUS_H__
#define __WEAPONSTATUS_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "../ItemStatus.h"
#include "Weapon.h"

class WeaponStatus : public ItemStatus {
    public:
        /**
         * @brief Available states of weapons.
         *          - OK:           The weapon can be used ;
         *          - BROKEN:       The weapon is broken, unusable ;
         *          - JAMMED:       For firearm, impossible to shoot ;
         *          - RELOADING:    For firearm, the weapon is being reloaded.
         */
        enum STATE { STATE_OK = 0, STATE_BROKEN, STATE_JAMMED, STATE_RELOADING } ;

    protected:
        /** @brief Arme dont il faut decrire l'etat d'usure. */
        Weapon* m_wpn ;

        /** @brief State of the weapon. */
        WeaponStatus::STATE m_state ;

    public:
        /**
         * @brief Construction de l'etat d'une arme blanche.
         * @param weapon    Arme dont il faut decrire l'etat d'usure.
         * @param hardness  Usure de l'arme initiale.
         */
        WeaponStatus(Weapon* weapon, ItemStatus::QUALITY hardness) ;
        
        /** @brief Destruction de l'etat d'une arme. */
        virtual ~WeaponStatus() ;

                                                              /** ACCESSEURS **/
        /**
         * @brief Recuperer l'arme.
         * @return L'arme dont l'etat est decrit.
         */
        virtual Item* getItem() { return m_wpn ; }


        /**
		 * @brief Retourner les degats causes par l'arme. L'etat de l'arme a un
		 *        impact direct sur les dommages affliges.
		 * @return Degats causes par l'arme en fonction de son etat d'usure.
		 */
		virtual short getDamageShoot() {
		    short max = m_wpn -> evaluateDamageShoot() ;
		    short ratioHardness = (m_hardness * 100 / m_wpn -> getHardness()) ;
            return (max * ratioHardness) / 100 ;
	    }

        /**
         * @brief The weapons can be used to shove characters. It makes little
         *        damage and the weapon can be damaged. These damages have no
         *        magic element, it means magic element is "None".
         * @return Damage caused by the weapon on a shoved enemy.
         */
        virtual short getDamageStock() {
            short max = m_wpn -> evaluateDamageStock() ;
            short ratioHardness = (m_hardness * 100 / m_wpn -> getHardness()) ;
            return (max * ratioHardness) / 100 ;
        }

        /**
         * @brief Get the state of the weapon.
         * @return The state of the weapon.
         */
        inline WeaponStatus::STATE getState() {
            return m_state ;
        }


                                                                 /** ACTIONS **/
        /**
		 * @brief Perte de durete de l'arme.
		 * @return FALSE si l'arme est deja cassee, TRUE sinon.
		 */
        virtual bool consume() ;


    public:
        /**
         * @brief Shoot with the weapon in order to attack for example.
         *        It consumes the weapon.
         * @param Output parameter to return the damages induced.
         * @return The state of the weapon after shooting.
         */
        virtual inline WeaponStatus::STATE shoot(short& damage) {
            if (m_state == WeaponStatus::STATE_OK)
                damage = getDamageShoot() ;
            else
                damage = 0 ;

            consume() ;
            return m_state ;
        }

        /**
         * @brief The stock of the weapon is used to shove characters.
         *        It consumes the weapon.
         * @param Output parameter to return the damages induced.
         * @return The state of the weapon after shooting.
         */
        virtual inline WeaponStatus::STATE shove(short& damage) {
            if (m_state == WeaponStatus::STATE_OK)
                damage = getDamageStock() ;
            else
                damage = 0 ;

            consume() ;
            return m_state ;
        }
} ;
#endif
