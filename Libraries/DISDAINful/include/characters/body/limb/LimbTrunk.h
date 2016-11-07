#ifndef __LIMBTRUNK_H__
#define __LIMBTRUNK_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include "Limb.h"

/**
 * @brief The trunk is the main part of the body, linking every limb.
 * @see Character
 * @see Limb
 * @version 1.0 04/04/2013
 */
class LimbTrunk : public Limb {
    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Creation of a trunk (limb). */
        LimbTrunk() ;

        /** @brief Destruction of a trunk (limb). */
        virtual ~LimbTrunk() ;
        
                                                                 /** SETTERS **/
        /**
         * @brief Set the limb as a treated limb if was blown off.
         * @warning Do nothing here!
         */
        virtual inline void setAsTreated() {}

                                                                /** UTILITIES */
        /**
         * @brief Damage a limb. If the health points of the limb equal zero,
         *        it is either fractured or blown off (random).
         * @param points    Damage points.
         */
        virtual inline void damage(unsigned char points) {
            invariant() ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Limb damage BEFORE: "
                                 << " [state = " << m_state
                                 << " | health = " << (int) m_health << "]" ;
                LogGen::print() ;
            #endif

            points = points / 2 ;                 // Trunk is not easily damaged
            if (points == 0) points = 1 ;     // Yet, at least one point is lost

            if (points >= m_health)
                m_health = 0 ;
            else
                m_health = m_health - points ;

            testStateAfterDamage(Limb::STATE_FRACTURED) ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Limb damage AFTER : "
                                 << " [state = " << m_state
                                 << " | health = " << (int) m_health << "]" ;
                LogGen::print() ;
            #endif

            invariant() ;
        }

        /**
         * @brief Damage a limb. If the health points of the limb equal zero,
         *        it is either fractured or blown off according to the type of
         *        attack.
         * @param points    Damage points.
         * @param type      Type of damage providen by the attack (fractured or
         *                  blown off). No matter, it is always fractured.
         */
        virtual inline void damage(unsigned char points, STATE) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Limb damage with state (redirected)" ;
                LogGen::print() ;
            #endif

            damage(points) ;
        }

        /**
         * @brief Heal a limb. It automatically change its state to STATE_OK.
         */
        inline void heal(unsigned char points) {
            invariant() ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Limb healing BEFORE: "
                                 << " [state = " << m_state
                                 << " | health = " << (int) m_health << "]" ;
                LogGen::print() ;
            #endif

            m_health = m_health + points ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Limb healing WHILE: "
                                 << " [state = " << m_state
                                 << " | health = " << (int) m_health << "]" ;
                LogGen::print() ;
            #endif

            if (m_health > 100) m_health = 100 ;
            m_state = Limb::STATE_OK ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Limb healing AFTER : "
                                 << " [state = " << m_state
                                 << " | health = " << (int) m_health << "]" ;
                LogGen::print() ;
            #endif

            invariant() ;
        }

        /**
         * @brief Heal a limb.
         */
        void heal(unsigned char points, bool) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Limb healing (redirected)" ;
                LogGen::print() ;
            #endif

            heal(points) ;
        }

    protected:
        /** @brief Class invariant... */
        virtual inline void invariant() const {
            Limb::invariant() ;
            assert(m_state != STATE_BLOWNOFF) ;
        }
} ;

#endif
