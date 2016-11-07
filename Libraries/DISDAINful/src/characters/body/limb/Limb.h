#ifndef __LIMB_H__
#define __LIMB_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include <assert.h>
#include <stdlib.h>

/**
 * @brief A limb can be damaged and fractured. Then, the character may be unable
 *        to accomplish some actions such as running and jumping.
 * @see Body
 * @version 1.0 01/04/2013  Limbs are added to the Body class in order to
 *                          improve and complete the capabilities of the game
 *                          engine.
 */
class Limb {
    public:
        /**
         * @brief Possible states of the limbs. Must be registered from the
         * most OK status to the worst one.
         */
        enum STATE {STATE_OK = 0, STATE_TREATED, STATE_FRACTURED, STATE_BLOWNOFF} ;

    protected:
        /** @brief "Health points" of the limb, from 0 to 100. */
        short m_health ;

        /** @brief State of the limb. */
        Limb::STATE m_state ;

    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Creation of a healthy limb. */
        Limb() ;

        /** @brief Destruction of a Limb object. */
        virtual ~Limb() ;

                                                                 /** GETTERS **/
        /**
         * @brief Get health of the limb.
         * @return Health of the limb, between 0 and 100.
         */
        inline unsigned char getHealth() const {
            invariant() ;
            return m_health ;
        }

        /**
         * @brief Get state of the limb.
         * @return State of the limb.
         */
        inline Limb::STATE getState() const {
            return m_state ;
        }

        /**
         * @brief Set the limb as a treated limb if was blown off.
         */
        virtual inline void setAsTreated() {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Limb set as treated BEFORE: "
                                 << " [state = " << m_state
                                 << " | health = " << (int) m_health << "]" ;
                LogGen::print() ;
            #endif

            if (m_state == Limb::STATE_BLOWNOFF)
                m_state = Limb::STATE_TREATED ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Limb set as treated AFTER : "
                                 << " [state = " << m_state
                                 << " | health = " << (int) m_health << "]" ;
                LogGen::print() ;
            #endif
        }

                                                                /** UTILITIES */
        /**
         * @brief Damage a limb. If the health points of the limb equal zero,
         *        it is either fractured or blown off (random).
         * @param points    Damage points.
         */
        virtual void damage(unsigned char points) ;

        /**
         * @brief Damage a limb. If the health points of the limb equal zero,
         *        it is either fractured or blown off according to the type of
         *        attack.
         * @param points    Damage points.
         * @param type      Type of damage providen by the attack (fractured or
         *                  blown off).
         */
        virtual void damage(unsigned char points, Limb::STATE type) ;

        /**
         * @brief Heal a limb. It automatically change its state to STATE_OK.
         * @param points            Heal points.
         * @param fractured_only    Heal only fractured limbs if TRUE.
         */
        void heal(unsigned char points, bool fractured_only = false) ;

        /**
         * @brief To know if the limb is blown off.
         * @return TRUE if the limb is blown off, FALSE if not.
         */
        inline bool isBlownOff() {
            return (m_state == Limb::STATE_BLOWNOFF) ;
        }

        /**
         * @brief To know if the limb is fractured.
         * @return TRUE if the limb is fractured, FALSE if not.
         */
        inline bool isFractured() {
            return (m_state == Limb::STATE_FRACTURED) ;
        }

    protected:
        virtual inline void testStateAfterDamage(Limb::STATE type) {
            if (type > m_state) {
                // The more the limb is damaged, the more the chance its state changes increases
                if ((rand() % 100) > m_health)
                    m_state = type ;
            }
        }

        /** @brief Class invariant... */
        virtual inline void invariant() const {
            assert(m_health > -1) ;
            assert(m_health < 101) ;
        }
} ;

#endif
