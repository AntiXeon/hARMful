#ifndef __STATUS_H__
#define __STATUS_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include "../magic/MagicEffect.h"
#include "Statistics.h"

#include <unordered_map>

/**
 * @brief Status of the character. It includes positive and negative status
 *        effects such as poisoning, life regeneration, etc. It affects the
 *        statistics of the character as decreasing points of life, increase of
 *        strength, etc.
 * @see Character
 * @see Statistics
 * @version 1.0 01/04/2013
 */
class Status {
    private:
        /** @brief Statistics linked to the status effects applied. */
        Statistics* m_stats ;

        /**
         * @brief Magic effects applied to the character.
         *        The key is used to easily find the MagicEffect applied.
         *        The value is the duration of the effect :
         *          - -1 if the effect is applied by an item ;
         *          -  0 if the duration is unlimited ;
         *          -  positive value for a limited duration.
         */
        std::unordered_map<MagicEffect*, char> m_status_effect ;

        /** @brief The character cannot use magic if this value is TRUE. */
        bool m_silence ;

        /** @brief The character cannot move in the space if TRUE. */
        bool m_immobile ;

        /**
         * @brief The character cannot move at all (displacements, actions...)
         *        if TRUE.
         */
        bool m_paralysed ;

    public:
        /**
	     * @brief Used to select what is to be healed.
	     * ALL      Select the most important element according to the situation.
	     * HP       Give HP to the character.
	     * MP       Give MP to the character.
	     * STATUS   Heal a status effect.
	     * KO       Revive a KO character.
	     */
	    enum HEALING {HEAL_ALL = 0, HEAL_HP, HEAL_MP, HEAL_STATUS, HEAL_KO} ;

                                                            /** CONSTRUCTORS **/
        /** @brief Creation of a Status object. */
        Status(Statistics* stats) ;

        /** @brief Destruction of a Status object. */
        virtual ~Status() {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " DESTRUCTION " ;
                LogGen::print() ;
            #endif
        }

                                               /** STATUS EFFECTS MANAGEMENT **/
        /**
         * @brief Add a status effect.
         * @param effect    The effect to add.
         */
        void addStatusEffect(MagicEffect* effect) ;

        /**
         * @brief Remove a status effect.
         * @param effect    The effect to remove.
         */
        void removeStatusEffect(MagicEffect* effect) ;

        /**
         * @brief Update all the statistics of the character (but not the one
         *        modifying HP/MP amounts). Useful when base statistics are
         *        changed, for example after a level up.
         */
        void updateAllStatusEffects() ;

        /** @brief Apply all the status effects. */
        void applyStatusEffects() ;

        /**
         * @brief Update of the status effects while removing one of them.
         * @param effect    The status effect to ignore while updating.
         */
        void updateStatsRemovingEffect(MagicEffect* effect) ;


        /** @brief Set if the character can use magic. */
        inline void setSilenceState(bool flag) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " set silence " << flag ;
                LogGen::print() ;
            #endif

            m_silence = flag ;
        }

        /** @brief Set if the character can move in the space. */
        inline void setImmobileState(bool flag) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " set immobile " << flag ;
                LogGen::print() ;
            #endif

            m_immobile = flag ;
        }

        /** @brief Set if the character can move and act. */
        inline void setParalysedState(bool flag) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " set paralysed " << flag ;
                LogGen::print() ;
            #endif

            m_paralysed = flag ;
        }



                                                                 /** GETTERS **/
        /**
         * @brief Evaluation of the damages on HP caused by all the status
         *        effects.
         * @return The value corresponds to an average loss of HP per second.
         */
        unsigned short evaluateEffectsDamages() ;

        /**
         * @brief Count all the status effets, positive and negative.
         * @return Total amount of status effects applied to the character.
         */
        inline unsigned short countTotalEffects() {
            return m_status_effect.size() ;
        }

        /**
         * @brief Count all the negative status effets.
         * @return Amount of negative status effects applied to the character.
         */
        unsigned short countMalusEffects() ;

        /**
         * @brief Count all the positive status effets.
         * @return Amount of positive status effects applied to the character.
         */
        unsigned short countBonusEffects() ;

        /**
         * @brief Test if the character has the status effect.
         */
        inline bool hasStatusEffect(MagicEffect* effect) {
            return (m_status_effect.count(effect) > 0) ? true : false ;
        }

        /**
         * @brief Test if the character has the status effect.
         */
        inline bool getStatusEffectDuration(MagicEffect* effect) {
            return (m_status_effect.count(effect) > 0) ? m_status_effect[effect] : 0 ;
        }

        /** @brief To know if the character can use magic. */
        inline bool getSilenceState() {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " is silence: " << m_silence ;
                LogGen::print() ;
            #endif

            return m_silence ;
        }

        /** @brief To know if the character can move in the space. */
        inline bool getImmobileState() {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " is immobile: " << m_immobile ;
                LogGen::print() ;
            #endif

            return m_immobile ;
        }

        /** @brief To know if the character can move and act. */
        inline bool getParalysedState() {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " is paralysed: " << m_paralysed ;
                LogGen::print() ;
            #endif

            return m_paralysed ;
        }
} ;

#endif
