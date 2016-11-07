#ifndef __LIMBHEAD_H__
#define __LIMBHEAD_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include "Limb.h"

class LimbHead : public Limb {
    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Creation of a head (limb). */
        LimbHead() ;

        /** @brief Destruction of a head (limb). */
        virtual ~LimbHead() ;
        
                                                                 /** SETTERS **/
        /**
         * @brief Set the limb as a treated limb if was blown off.
         * @warning Do nothing here!
         */
        virtual inline void setAsTreated() {}

                                                                /** UTILITIES */
        /**
         * @brief Damage a limb. If the health points of the limb equal zero,
         *        it is only blown off.
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

            points = points * 5 ;   // head is weaker

            if (points >= m_health)
                m_health = 0 ;
            else
                m_health = m_health - points ;

            testStateAfterDamage(Limb::STATE_BLOWNOFF) ;

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
         *                  blown off). No matter, it is always blown off.
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
         * @brief Heal a limb. A head cannot be healed if blown off...
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

            if (m_state == STATE_OK) {
                m_health = m_health + points ;
                if (m_health > 100) m_health = 100 ;
            }

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
         * @brief Heal a limb. A head cannot be healed if blown off...
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
            assert(m_state != STATE_FRACTURED) ;
            assert(m_state != STATE_TREATED) ;
        }
} ;

#endif
