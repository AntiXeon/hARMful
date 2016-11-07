#ifndef __FIREARMSTATUS_H__
#define __FIREARMSTATUS_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include "../WeaponStatus.h"
#include "../../inventory/AmmoStock.h"

/**
 * @brief A firearm that can be damaged and used.
 * @version 1.0
 * @version 2.0 20/04/2013  Jammed weapons are available. Improved ammo
 *                          management.
 */
 // @TODO USE TIMERS!!!!!!!! ---------------------------------------------------
class FirearmStatus : public WeaponStatus {
    protected:
        /**
         * @brief Maximal amount of attempts before getting the weapon
         *        unjammed.
         */
        unsigned char m_attemptsUnjamWeapon ;

        /**
         * @brief Maximal amount of attempts before getting the weapon
         *        unjammed.
         */
        unsigned char m_timeReloadWeapon ;

        /**
         * @brief Remaining time before reloading (used when the weapon is
         *        being reloaded).
         */
        char m_reloadingTimer ;

        /** @brief Remaining time before the weapon is unjammed. */
        char m_unjammingTimer ;

        /** @brief Amount of remaining ammo in the cylinder. */
        unsigned char m_ammoRemaining ;

    public:
                                                            /** CONSTRUCTORS **/
        /**
         * @brief Creation of a FirearmStatus.
         * @param weapon    The weapon definition.
         * @param hardness  The way the hardness of the weapon is generated.
         */
        FirearmStatus(Firearm* weapon, ItemStatus::QUALITY hardness) ;

        /** @brief Destruction of a FirearmStatus. */
        virtual ~FirearmStatus() ;

                                                                 /** GETTERS **/
        /**
         * @brief Get the remaining amount of ammo in the cylinder.
         */
        inline unsigned char getAmmoRemaining() const {
            return m_ammoRemaining ;
        }

        /**
         * @brief Get the quantity of ammo needed to fill the cylinder.
         * @return Difference between the amount of ammo to have a full cylinder
         *        and the current amount of ammo in the cylinder.
         */
        inline unsigned char getAmmoRequest() {
            unsigned char max = ((Firearm*) m_wpn) -> getAmmoMax() ;
            assert(m_ammoRemaining < max) ;

            return (max - m_ammoRemaining) ;
        }

    protected:
        /** @brief Set both unjamming and reloading timers. */
        virtual void setTimers() {
            m_reloadingTimer = m_attemptsUnjamWeapon ;
            m_unjammingTimer = m_timeReloadWeapon ;
        }

        /**
		 * @brief Get damage caused by the weapon.
		 * @return Damage caused by the weapon.
		 */
		virtual inline short getDamageShoot() {
		    return m_wpn -> evaluateDamageShoot() ;
		}

        /**
         * @brief The weapon can be jammed after using it... Depends on its
         *        hardness.
         * @return TRUE if the weapon is jammed, FALSE else.
         */
        virtual inline bool testJammed() {
            unsigned char maxHardness = m_wpn -> getHardness() ;
            if (rand() % maxHardness < m_hardness)
                return true ;
            return false ;
        }

        /**
         * @brief The weapon can be need tp be reloaded after using it...
         * @return TRUE if the weapon is jammed, FALSE else.
         */
        virtual inline bool testReload() {
            Firearm* def = ((Firearm*) m_wpn) ;
            // Consume ammo and test if the weapon needs to be reloaded
            unsigned char ammoUsed = (def -> getAmmoUsed()) ;
            m_ammoRemaining = m_ammoRemaining - ammoUsed ;
            return (m_ammoRemaining < ammoUsed) ;
        }

    public:
                                                                 /** ACTIONS **/
        virtual inline void unjam() {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << (getItem() -> getName()) << " ("
                                 << this << ") being unjammed!" ;
                LogGen::print() ;
            #endif

            m_unjammingTimer = m_unjammingTimer - 1 ;
            m_unjammingTimer = m_unjammingTimer - (rand() % 5) ;

            if (m_unjammingTimer < 0)
                m_state = WeaponStatus::STATE_OK ;
        }

        /**
         * @brief Reload the firearm.
         * @param addedAmmo Amount of ammo added to the cylinder.
         * @return Difference of unused ammo.
         */
        virtual inline void reload(unsigned char addedAmmo) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << (getItem() -> getName()) << " ("
                                 << this << ") being reloaded!" ;
                LogGen::print() ;
            #endif

            unsigned char max = ((Firearm*) m_wpn) -> getAmmoMax() ;
            assert(addedAmmo <= max) ;

            m_reloadingTimer = m_reloadingTimer - 1 ;

            if (m_reloadingTimer < 0) {
                m_ammoRemaining = m_ammoRemaining + addedAmmo ;
                m_hardness = m_hardness - 1 ;
                m_state = WeaponStatus::STATE_OK ;
            }
            
            assert(m_ammoRemaining <= max) ;
        }


        /**
         * @brief Shoot with the weapon in order to attack for example.
         *        It consumes the weapon.
         * @param Output parameter to return the damage induced.
         * @return The state of the weapon after shooting.
         */
        virtual inline WeaponStatus::STATE shoot(short& damage) {
            if (m_state == WeaponStatus::STATE_OK) {
                damage = getDamageShoot() ;

                if (testReload()) {
                    m_reloadingTimer = m_timeReloadWeapon ;
                    m_state = WeaponStatus::STATE_RELOADING ;
                }
                else if (testJammed()) {
                    m_unjammingTimer = m_attemptsUnjamWeapon ;
                    m_state = WeaponStatus::STATE_JAMMED ;
                }
            }
            else
                damage = 0 ;

            return m_state ;
        }
} ;

#endif
