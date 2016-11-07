#include "Status.h"

#include <assert.h>

using namespace std ;

                                                            /** CONSTRUCTORS **/
Status::Status(Statistics* stats) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION " ;
        LogGen::print() ;
    #endif

    m_stats = stats ;

    m_silence = false ;
}

                                               /** STATUS EFFECTS MANAGEMENT **/
void Status::addStatusEffect(MagicEffect* effect) {
    assert(effect != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " add status effect " << (effect -> getName()) ;
        LogGen::print() ;
    #endif

	if (m_status_effect.count(effect) == 0) {
	    m_status_effect[effect] = effect -> getLast() ; // If the effect is not listed, add it
        m_stats -> addStatusEffect(effect) ;            // Statistics of the character are then modified

        // Switch states
        if (effect -> getSilenceState() == MagicEffect::STATE_ACTIVATE)
            m_silence = true ;
        else if (effect -> getSilenceState() == MagicEffect::STATE_DEACTIVATE)
            m_silence = false ;

        if (effect -> getImmobileState() == MagicEffect::STATE_ACTIVATE)
            m_immobile = true ;
        else if (effect -> getImmobileState() == MagicEffect::STATE_DEACTIVATE)
            m_immobile = false ;

        if (effect -> getParalysedState() == MagicEffect::STATE_ACTIVATE)
            m_paralysed = true ;
        else if (effect -> getParalysedState() == MagicEffect::STATE_DEACTIVATE)
            m_paralysed = false ;
	}
	else if (m_status_effect[effect] > 0)
        m_status_effect[effect] = effect -> getLast() ; // Restart the countdown
}

void Status::removeStatusEffect(MagicEffect* effect) {
    assert(effect != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " remove status effect " << (effect -> getName()) ;
        LogGen::print() ;
    #endif

    updateStatsRemovingEffect(effect) ;                // Restore the statistics
    m_status_effect.erase(effect) ;           // Remove the effect from the list
}

void Status::updateAllStatusEffects() {
    m_stats -> clearBonus() ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " update all status effects " ;
        LogGen::print() ;
    #endif

    MagicEffect* cur ;
    for(auto& effect : m_status_effect) {
        cur = effect.first ;
        if (cur -> getType() != MagicEffect::TYPE_POINTS_BONUS
                && cur -> getType() != MagicEffect::TYPE_POINTS_MALUS) {
            addStatusEffect(cur) ;
        }
    }
}

void Status::applyStatusEffects() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " apply all status effects " ;
        LogGen::print() ;
    #endif

    // This boolean avoid applying effects if the character dies in the meantime
    bool alive ;
    MagicEffect* cur ;
    for(auto& effect : m_status_effect) {
        cur = effect.first ;
        // Change the statistics of the character by a repeated effect
        if (cur -> isRepeat()) {
            alive = m_stats -> applyStatusEffect(cur) ;

            // Stop the loop if the character dies
            if (!alive) return ;
        }

        // Decrease the countdown of the effect if the effect is temporary
        if (cur -> getLast() > 0) {
            if (effect.second > 0) {
                effect.second = effect.second - 1 ;
            }
            else {
                // Remove the effect if it is not applied anymore
                updateStatsRemovingEffect(cur) ;
                // Remove the effect
                m_status_effect.erase(cur) ;
            }
        }
    }
}

void Status::updateStatsRemovingEffect(MagicEffect* effect) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " add update by removing effect "
                         << (effect -> getName()) ;
        LogGen::print() ;
    #endif

    m_stats -> removeStatusEffect(effect) ;
}


                                                                 /** GETTERS **/
unsigned short Status::evaluateEffectsDamages() {
    unsigned short total = 0 ;

    MagicEffect* cur ;
    for(auto& effect : m_status_effect) {
        cur = effect.first ;
        if (cur -> getType() == MagicEffect::TYPE_MALUS
                && cur -> getType() == MagicEffect::TYPE_POINTS_MALUS) {
            if (cur -> isPercent()) {
                // Damages are percent of total HP
                total += (-((m_stats -> getHPMaxBase() * cur-> getBM_HP()) / 100)) ;
            }
            else {
                // Strict damage value
                total += (-(cur -> getBM_HP())) ;
            }
        }
    }

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " evaluate total of damage caused by effects " 
                         << total << " HP" ;
        LogGen::print() ;
    #endif

    return total ;
}

unsigned short Status::countMalusEffects() {
    unsigned short total = 0 ;

    MagicEffect* cur ;
    for(auto& effect : m_status_effect) {
        cur = effect.first ;
        if (cur -> getType() == MagicEffect::TYPE_MALUS
                && cur -> getType() == MagicEffect::TYPE_POINTS_MALUS) {
            total++ ;
        }
    }

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " count of malus effects: " 
                         << total ;
        LogGen::print() ;
    #endif

    return total ;
}

unsigned short Status::countBonusEffects() {
    unsigned short total = 0 ;

    MagicEffect* cur ;
    for(auto& effect : m_status_effect) {
        cur = effect.first ;
        if (cur -> getType() == MagicEffect::TYPE_BONUS
                && cur -> getType() == MagicEffect::TYPE_POINTS_BONUS) {
            total++ ;
        }
    }

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " count of bonus effects: " 
                         << total ;
        LogGen::print() ;
    #endif

    return total ;
}
