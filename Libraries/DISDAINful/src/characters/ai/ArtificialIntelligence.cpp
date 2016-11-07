#include <algorithm>
#include <climits>
#include <stdlib.h>
#include <map>
#include <unordered_map>

#include "ArtificialIntelligence.h"
#include "../../AllMagic.h"
#include "../../AllPotions.h"

using namespace std ;

/******************************************************************************/
                                                            /** CONSTRUCTORS **/
ArtificialIntelligence::ArtificialIntelligence(ActionMemory* action_memory,
                                               Physique* physique,
                                               Statistics* statistics) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << "CREATION" ;
        LogGen::print() ;
    #endif

    m_inventory = new Inventory() ;
    m_magicmem = new MagicMemory() ;
    m_statistics = statistics ;
    m_status = new Status(m_statistics) ;
    m_physique = physique ;
    m_actionmem = action_memory ;
    m_colony = 0 ;
    m_lastEnemy = 0 ;

    m_changingWeaponTimer = new Timer(2) ;
    m_changingWeapon = false ;
}

ArtificialIntelligence::~ArtificialIntelligence() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << "DESTRUCTION" ;
        LogGen::print() ;
    #endif

    delete m_changingWeaponTimer ;
    delete m_status ;
    delete m_magicmem ;
    delete m_inventory ;
}

/******************************************************************************/
                                                               /** UTILITIES **/
void ArtificialIntelligence::healed(short value) {
    assert(value > -1) ;

    // Can be healed only if not in lethal condition
    if (!(m_physique -> lethalCondition())) {
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " healed with " << value << " HP" ;
            LogGen::print() ;
        #endif

        if (m_statistics -> isKO())
            m_colony -> setKOToAliveMembers((unsigned long) this) ;
        m_statistics -> gainHP(value) ;
    }
}

void ArtificialIntelligence::damaged(short value) {
    assert(value > -1) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " damaged with " << value << " HP" ;
        LogGen::print() ;
    #endif

    m_statistics -> loseHP(value) ;
	if (m_statistics -> isKO()) {
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " is KO..." ;
            LogGen::print() ;
        #endif

	    m_lastEnemy = 0 ;                               // Forget the last enemy
	    m_colony -> setAliveToKOMembers((unsigned long) this) ;
    }
}


void ArtificialIntelligence::run() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " AI runs..." ;
        LogGen::print() ;
    #endif


    // Check first if the body situation allows the character to live
    if (m_physique -> lethalCondition()) {
        // If it is not, the character loses all its life points and die
        damaged(m_statistics -> getHP()) ;
        return ;
    }

    // Start applying status effects
    m_status -> applyStatusEffects() ;

    // If the body is damaged, it makes lose some life points...
    if (m_physique -> seriouslyDamagedBody()) {
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this
                             << " damaged because seriously damaged body..." ;
            LogGen::print() ;
        #endif

        damaged(5) ;
    }

    fight() ;
}


void  ArtificialIntelligence::fight() {
    if (m_colony -> getToFight() != 0) {
        // The character is fighting, it does not care about the colony strategy
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " still fighting..." ;
            LogGen::print() ;
        #endif


        // Reset the last shot enemy if it has died since the last round
        if (m_lastEnemy != 0 && (m_lastEnemy -> m_statistics -> isKO())) {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << this << " has no more last enemy..." ;
                LogGen::print() ;
            #endif

            m_lastEnemy = 0 ;
        }


        specificFightAI() ;
    }
}


                                                                /* SELECTIONS */
Potion* ArtificialIntelligence::selectBestLifePotion(ArtificialIntelligence* other) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the best potion..." ;
        LogGen::print() ;
    #endif

    Potion* best = 0 ;                                  // The best potion found
    // Missing HP of the character to heal
    unsigned short to_heal = (other -> m_statistics -> getHPMax()) - (other -> m_statistics -> getHP()) ;
    unsigned short prev_hp_diff ;   // Lowest difference between missing HP and given HP
    unsigned short cur_hp_diff ;    // Difference between missing HP and given HP of the current potion

    Potion* cur ;
    if (other -> m_statistics -> isKO()) {
        prev_hp_diff = 0 ;

        unordered_map<std::string, Potion*> list = AllPotions::getPotions(Potion::TYPE_KO) ;
        for (auto& potion : list) {
            cur = potion.second ;
            if (m_inventory -> have(cur)) {
                cur_hp_diff = cur -> getPoints_HP() ;
                if (cur_hp_diff > prev_hp_diff) {
                    prev_hp_diff = cur_hp_diff ;
                    best = cur ;
                }
            }
        }
    }
    else {
        prev_hp_diff = USHRT_MAX ;

        unordered_map<std::string, Potion*> list = AllPotions::getPotions(Potion::TYPE_LIFE) ;
        for (auto& potion : list) {
            cur = potion.second ;
            if (m_inventory -> have(cur)) {
                cur_hp_diff = abs((cur -> getPoints_HP()) - to_heal) ;
                if (cur_hp_diff < prev_hp_diff) {
                    prev_hp_diff = cur_hp_diff ;
                    best = cur ;
                }
            }
        }
    }

    #ifdef DEBUG_MODE
        if (best != 0)
            LogGen::stream() << __FILE__ << " " << __LINE__
                             << ": " << this << " has selected " << (best -> getName()) ;
        else
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected nothing" ;
        LogGen::print() ;
    #endif

    return best ;
}

WhiteMagic* ArtificialIntelligence::selectBestLifeMagic(ArtificialIntelligence* other) {
    WhiteMagic* best = 0 ;                               // The best magic found

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the best white magic..." ;
        LogGen::print() ;
    #endif

    if (!(m_status -> getSilenceState() || m_status -> getParalysedState())) {
        // Missing HP of the character to heal
        unsigned short prev_hp_diff ;    // Lowest difference between missing HP and given HP
        unsigned short cur_hp_diff ;        // Difference between missing HP and given HP of the current potion
        unsigned short max = m_magicmem -> countWhiteMagic() ;

        WhiteMagic* cur ;
        if (other -> m_statistics -> isKO()) {
            prev_hp_diff = 0 ;
            for (unsigned short i = 0 ; i < max ; i++) {
                cur = m_magicmem -> getWhiteMagic(i) ;
                if (((cur -> getMPNeed()) <= (m_statistics -> getMP()))
                        && cur -> getType() == WhiteMagic::TYPE_REVIVE) {
                    cur_hp_diff = cur -> getHealPoints() ;

                    // Keep the most efficient magic if the character has enough MP
                    if ((cur_hp_diff > prev_hp_diff)) {
                        prev_hp_diff = cur_hp_diff ;
                        best = cur ;
                    }
                }
            }
        }
        else {
            prev_hp_diff = USHRT_MAX ;
            short to_heal = (other -> m_statistics -> getHPMax()) - (other -> m_statistics -> getHP()) ;
            for (unsigned short i = 0 ; i < max ; i++) {
                cur = m_magicmem -> getWhiteMagic(i) ;
                if (((cur -> getMPNeed()) < (m_statistics -> getMP()))) {
                    cur_hp_diff = abs(to_heal - (cur -> getHealPoints())) ;
                    if (cur_hp_diff < prev_hp_diff) {
                        prev_hp_diff = cur_hp_diff ;
                        best = cur ;
                    }
                }
            }
        }
    }

    #ifdef DEBUG_MODE
        if (best != 0)
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected " << (best -> getName()) ;
        else
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected nothing" ;
        LogGen::print() ;
    #endif

    return best ;
}


Potion* ArtificialIntelligence::selectBestManaPotion(ArtificialIntelligence* other) {
    Potion* best = 0 ;                                  // The best potion found
    // Missing MP of the character to heal
    unsigned short to_gain = (other -> m_statistics -> getMPMax()) - (other -> m_statistics -> getMP()) ;
    unsigned short prev_mp_diff = USHRT_MAX ;   // Lowest difference between missing HP and given HP
    unsigned short cur_mp_diff ;                // Difference between missing HP and given HP of the current potion

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the best mana potion..." ;
        LogGen::print() ;
    #endif

    Potion* cur ;

    unordered_map<std::string, Potion*> list = AllPotions::getPotions(Potion::TYPE_MANA) ;
    for (auto& potion : list) {
        cur = potion.second ;
        if (m_inventory -> have(cur)) {
            cur_mp_diff = abs((cur -> getPoints_MP()) - to_gain) ;
            if (cur_mp_diff < prev_mp_diff) {
                prev_mp_diff = cur_mp_diff ;
                best = cur ;
            }
        }
    }

    #ifdef DEBUG_MODE
        if (best != 0)
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected " << (best -> getName()) ;
        else
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected nothing" ;
        LogGen::print() ;
    #endif

    return best ;
}

//WhiteMagic* ArtificialIntelligence::selectBestProtectionMagic(ArtificialIntelligence* other) {
//    /* @TODO This method could be improved by saving the kind of the last
//             actions received by the other character */
//    WhiteMagic* selected ;

//    #ifdef DEBUG_MODE
//        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
//                         << this << " selects the best protection magic..." ;
//        LogGen::print() ;
//    #endif

//    MagicEffect* effect_def = (MagicEffect*) AllMagic::getMagicEffect("Shield") ;
//    MagicEffect* effect_psy = (MagicEffect*) AllMagic::getMagicEffect("Barrier") ;
//    unsigned char defense = (other -> m_status -> getStatusEffectDuration(effect_def)) ;
//    unsigned char psycho = (other -> m_status -> getStatusEffectDuration(effect_psy)) ;

//    // Test if the defense raising is a good option (less than 1/3 of the max duration)
//    if (effect_def -> getLast() != 0) {
//        if (((defense * 100) / defense) < ((effect_def -> getLast()) / 3)) {
//            selected = (WhiteMagic*) AllMagic::getWhiteMagic("Defense+") ;
//            if (((selected -> getMPNeed()) <= (m_statistics -> getMP()))
//                    && m_magicmem -> hasMagic(selected)) {
//                #ifdef DEBUG_MODE
//                    LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
//                                     << this << " has selected "
//                                     << (selected -> getName()) ;
//                    LogGen::print() ;
//                #endif

//                return selected ;
//            }
//        }
//    }

//    // Test if the psy raising is a good option (less than 1/3 of the max duration)
//    if (effect_psy -> getLast() != 0) {
//        if (((psycho * 100) / psycho) < ((effect_psy -> getLast()) / 3)) {
//            selected = (WhiteMagic*) AllMagic::getWhiteMagic("Psycho+") ;
//            if (((selected -> getMPNeed()) <= (m_statistics -> getMP()))
//                    && m_magicmem -> hasMagic(selected)) {
//                #ifdef DEBUG_MODE
//                    LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
//                                     << this << " has selected "
//                                     << (selected -> getName()) ;
//                    LogGen::print() ;
//                #endif

//                return selected ;
//            }
//        }
//    }

//    #ifdef DEBUG_MODE
//        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
//                         << this << " has selected nothing " ;
//        LogGen::print() ;
//    #endif

//    // Nothing seems good
//    return 0 ;
//}

WhiteMagic* ArtificialIntelligence::selectBestStatusMagicForAlly(ArtificialIntelligence* other) {
    WhiteMagic* selected = 0 ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the best status magic for ally..." ;
        LogGen::print() ;
    #endif

    if (other -> m_status -> countMalusEffects() > 0) {
        if (!(m_status -> getSilenceState() || m_status -> getParalysedState())) {
            unordered_map<MagicEffect*, unsigned char> clearing ;
            MagicEffect* effect ;

            vector<WhiteMagic*> list = m_magicmem -> getWhiteMagic() ;
            unsigned char cur_match, max_match = 0 ;                            // Amount of matches of effects
            for (auto& magic : list) {
                cur_match = 0 ;

                if ((magic -> getMPNeed()) <= (m_statistics -> getMP())) {
                    // Find the magic with the most clearing effects
                    clearing = magic -> getClearEffects() ;

                    for (auto& current : clearing) {
                        effect = current.first ;

                        /* Test if the enemy has the bonus effect */
                        if ((effect -> getType() == MagicEffect::TYPE_BONUS
                                || effect -> getType() == MagicEffect::TYPE_POINTS_BONUS)
                                && other -> m_status -> hasStatusEffect(effect)) {
                            cur_match++ ;
                        }
                    }

                    if (cur_match > max_match) {
                        max_match = cur_match ;
                        selected = magic ;
                    }
                }
            }
        }
    }

    #ifdef DEBUG_MODE
        if (selected != 0)
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected " << (selected -> getName()) ;
        else
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected nothing" ;
        LogGen::print() ;
    #endif

    return selected ;
}

WhiteMagic* ArtificialIntelligence::selectBestWhiteStatusMagicForEnemy(ArtificialIntelligence* other) {
    WhiteMagic* selected = 0 ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the best white status magic for enemy..." ;
        LogGen::print() ;
    #endif

    if (!(m_status -> getSilenceState() || m_status -> getParalysedState())) {
        unordered_map<MagicEffect*, unsigned char> clearing ;
        MagicEffect* effect ;

        vector<WhiteMagic*> list = m_magicmem -> getWhiteMagic() ;
        unsigned char cur_match, max_match = 0 ;                                // Amount of matches of effects
        for (auto& magic : list) {
            cur_match = 0 ;

            if ((magic -> getMPNeed()) <= (m_statistics -> getMP())) {
                // Find the magic with the most clearing effects
                clearing = magic -> getClearEffects() ;

                for (auto& current : clearing) {
                    effect = current.first ;

                    /* Test if the enemy has the bonus effect */
                    if ((effect -> getType() == MagicEffect::TYPE_MALUS
                            || effect -> getType() == MagicEffect::TYPE_POINTS_MALUS)
                            && other -> m_status -> hasStatusEffect(effect)) {
                        cur_match++ ;
                    }
                }

                if (cur_match > max_match) {
                    max_match = cur_match ;
                    selected = magic ;
                }
            }
        }
    }

    #ifdef DEBUG_MODE
        if (selected != 0)
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected " << (selected -> getName()) ;
        else
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected nothing" ;
        LogGen::print() ;
    #endif

    return selected ;
}

BlackMagic* ArtificialIntelligence::selectBestBlackStatusMagicForEnemy(ArtificialIntelligence* other) {
    BlackMagic* selected = 0 ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the best black status magic for enemy..." ;
        LogGen::print() ;
    #endif

    if (!(m_status -> getSilenceState() || m_status -> getParalysedState())) {
        unordered_map<MagicEffect*, unsigned char> clearing ;
        MagicEffect* effect ;

        vector<BlackMagic*> list = m_magicmem -> getBlackMagic() ;
        unsigned char cur_match, max_match = 0 ;                                // Amount of matches of effects
        for (auto& magic : list) {
            cur_match = 0 ;

            // Find the magic with the most clearing effects
            clearing = magic -> getClearEffects() ;

            for (auto& current : clearing) {
                effect = current.first ;

                /* Test if the enemy has the bonus effect */
                if ((effect -> getType() == MagicEffect::TYPE_MALUS
                        || effect -> getType() == MagicEffect::TYPE_POINTS_MALUS)
                        && other -> m_status -> hasStatusEffect(effect)) {
                    cur_match++ ;
                }
            }

            if (cur_match > max_match) {
                max_match = cur_match ;
                selected = magic ;
            }
        }
    }

    #ifdef DEBUG_MODE
        if (selected != 0)
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected " << (selected -> getName()) ;
        else
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected nothing" ;
        LogGen::print() ;
    #endif

    return selected ;
}


WeaponStatus* ArtificialIntelligence::selectBestWeapon(ArtificialIntelligence* other, short& damages) {
    WeaponStatus* selected = m_physique -> getEquipment() -> getDefaultWeapon();
    Weapon* wpn = (Weapon*) selected ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the best weapon..." ;
        LogGen::print() ;
    #endif

    // Damage of the currently assessed weapon and the best found at the moment
    short cur_damages, max_damages = evaluatePhysicalDamages(selected -> getDamageShoot(), other) ;

    unordered_map<Weapon*, WeaponStatus*> weaponsList = m_inventory -> getWeapons() ;
    WeaponStatus* status ;

    for(auto& current : weaponsList) {
        status = current.second ;
        if ((status -> getState()) != WeaponStatus::STATE_BROKEN) {
            // The weapon must be ready to use
            wpn = current.first ;

            if (testWeapon(wpn)) {
                cur_damages = wpn -> getDamageShoot() ;
                cur_damages = evaluatePhysicalDamages(cur_damages, other) ;

                if (cur_damages > 9999) {
                    // Nothing will be better, its is useless to continue!
                    max_damages = 9999 ;
                    return status ;
                }

                if (cur_damages > max_damages) {
                    max_damages = cur_damages ;
                    selected = status ;
                }
            }
        }
    }

    #ifdef DEBUG_MODE
        if (selected != 0)
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected " << (selected -> getItem() -> getName()) ;
        else
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected nothing" ;
        LogGen::print() ;
    #endif

    damages = max_damages ;
    return selected ;
}

BlackMagic* ArtificialIntelligence::selectBestBlackMagic(ArtificialIntelligence* other, short& damages) {
    short cur_damages, max_damages = 0 ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the best black magic..." ;
        LogGen::print() ;
    #endif

    BlackMagic* current ;
    BlackMagic* selected = 0 ;
    bool max_reached = false ;
    unsigned short count_magic = m_magicmem -> countBlackMagic() ;
    for (unsigned short i = 0 ; i < count_magic && !max_reached ; i++) {
        current = m_magicmem -> getBlackMagic(i) ;

        if ((current -> getMPNeed()) <= (m_statistics -> getMP())) {
            cur_damages = current -> getDamages(other -> m_physique -> getElement()) ;
            cur_damages = evaluateMagicDamages(cur_damages, other) ;

            if (cur_damages > 9999) {
                cur_damages = 9999 ;
                max_reached = true ;
            }

            if (cur_damages > max_damages) {
                max_damages = cur_damages ;
                selected = current ;
            }
        }
    }

    #ifdef DEBUG_MODE
        if (selected != 0)
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected " << (selected -> getName()) ;
        else
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected nothing" ;
        LogGen::print() ;
    #endif

    damages = max_damages ;
    return selected ;
}


ArtificialIntelligence* ArtificialIntelligence::selectBestKOAlly() {
    assert(!(m_colony -> getKOMembers()).empty()) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the best KO ally..." ;
        LogGen::print() ;
    #endif

    ArtificialIntelligence* selected = selectStrongestCharacter(m_colony -> getKOMembers()) ;
    assert(selected != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " has selected " << selected ;
        LogGen::print() ;
    #endif

    return selected ;
}

ArtificialIntelligence* ArtificialIntelligence::selectMostAffectedAlly() {
    assert(!(m_colony -> getAliveMembers()).empty()) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the most affected ally..." ;
        LogGen::print() ;
    #endif

    set<unsigned long> allies = m_colony -> getAliveMembers() ;
    set<unsigned long>::iterator it ;

    ArtificialIntelligence* selected = 0 ;
    ArtificialIntelligence* cur ;
    unsigned short selected_score = 0 ;
    unsigned short running_score ;
    for (it = allies.begin() ; it != allies.end() ; it++) {
        cur = convert(*it) ;
        running_score = cur -> m_status -> countMalusEffects() ;

        if (running_score > selected_score) {
            selected = cur ;
            selected_score = running_score ;
        }
    }

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " has selected " << selected ;
        LogGen::print() ;
    #endif

    return selected ;
}


ArtificialIntelligence* ArtificialIntelligence::selectMostHelpedEnemy() {
    assert(!(m_colony -> getToFight() -> getAliveMembers()).empty()) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the most helped enemy..." ;
        LogGen::print() ;
    #endif

    set<unsigned long> enemies = m_colony -> getToFight() -> getAliveMembers() ;
    set<unsigned long>::iterator it ;

    ArtificialIntelligence* selected = 0 ;
    ArtificialIntelligence* cur ;
    unsigned short selected_score = 0 ;
    unsigned short running_score ;
    for (it = enemies.begin() ; it != enemies.end() ; it++) {
        cur = convert(*it) ;
        running_score = cur -> m_status -> countBonusEffects() ;

        if (running_score > selected_score) {
            selected = cur ;
            selected_score = running_score ;
        }
    }

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " has selected " << selected ;
        LogGen::print() ;
    #endif

    return selected ;
}

ArtificialIntelligence* ArtificialIntelligence::selectWeakestCharacter(const set<unsigned long>& list) {
    assert(list.size() > 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the weakest character..." ;
        LogGen::print() ;
    #endif

    if (list.size() == 1) { // Do not need analysis if only one character listed
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected the only one "
                             << (*(list.begin())) ;
            LogGen::print() ;
        #endif

        return convert(*(list.begin())) ;
    }


    ArtificialIntelligence* selected = 0 ;  // The selected character at the end
    ArtificialIntelligence* current ;
    Statistics* stats ;
    set<unsigned long>::iterator it = list.begin() ;
    // Scoring system to evaluate the weakest character
    unsigned short running_score = 0, selected_score = USHRT_MAX ;

    for (it = list.begin() ; it != list.end() ; it++) {
        current = convert(*it) ;
        stats = current -> m_statistics ;

        /* Compute the score for the currently analyzed character.
           It is based on the most used action given by the character, and can
           be wrong as the character can lie!
           For a fair scoring system, all the statistics are normalized. */
        switch (current -> m_actionmem -> getMostPerformedAction()) {
            case ActionMemory::ACTION_NONE:
            case ActionMemory::ACTION_PHYSICAL:
                running_score = (stats -> getStrBase() * 100) / 255 ;
                running_score += (stats -> getDefBase() * 100) / 255 ;
                running_score += (stats -> getPrcBase() * 100) / 255 ;
                running_score += (stats -> getVelBase() * 100) / 255 ;
                running_score += (stats -> getHPMaxBase() * 100) / 9999 ;
                break ;

            case ActionMemory::ACTION_MAGICAL:
            case ActionMemory::ACTION_HEALING:
                running_score = (stats -> getMagBase() * 100) / 255 ;
                running_score += (stats -> getDefBase() * 100) / 255 ;
                running_score += (stats -> getPsyBase() * 100) / 255 ;
                running_score += (stats -> getMPMaxBase() * 100) / 999 ;
                running_score += (stats -> getHPMaxBase() * 100) / 9999 ;
                break ;
        }

        if (running_score < selected_score) {
            selected_score = running_score ;
            selected = current ;
        }
    }

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " has selected " << selected ;
        LogGen::print() ;
    #endif

    return selected ;
}

ArtificialIntelligence* ArtificialIntelligence::selectStrongestCharacter(const set<unsigned long>& list) {
    assert(list.size() > 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects the strongest character..." ;
        LogGen::print() ;
    #endif

    if (list.size() == 1) {  // Do not need analysis if only one character listed
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected the only one "
                             << (*(list.begin())) ;
            LogGen::print() ;
        #endif

        return convert(*(list.begin())) ;
    }


    ArtificialIntelligence* selected = 0 ;  // The selected character at the end

    ArtificialIntelligence* current ;
    Statistics* stats ;
    // Scoring system to evaluate the strongest character
    unsigned short running_score = 0, selected_score = 0 ;

    set<unsigned long>::iterator it ;
    for (it = list.begin() ; it != list.end() ; it++) {
        current = convert(*it) ;

        if (!(current -> m_physique -> lethalCondition())) {
            stats = current -> m_statistics ;

            /* Compute the score for the currently analyzed character.
               It is based on the most used action given by the character, and
               can be wrong as the character can lie!
               For a fair scoring system, all the statistics are normalized. */
            switch (current -> m_actionmem -> getMostPerformedAction()) {
                case ActionMemory::ACTION_NONE:
                case ActionMemory::ACTION_PHYSICAL:
                    running_score = (stats -> getStrBase() * 100) / 255 ;
                    running_score += (stats -> getDefBase() * 100) / 255 ;
                    running_score += (stats -> getPrcBase() * 100) / 255 ;
                    running_score += (stats -> getVelBase() * 100) / 255 ;
                    running_score += (stats -> getHPMaxBase() * 100) / 9999 ;
                    break ;

                case ActionMemory::ACTION_MAGICAL:
                case ActionMemory::ACTION_HEALING:
                    running_score = (stats -> getMagBase() * 100) / 255 ;
                    running_score += (stats -> getDefBase() * 100) / 255 ;
                    running_score += (stats -> getPsyBase() * 100) / 255 ;
                    running_score += (stats -> getMPMaxBase() * 100) / 999 ;
                    running_score += (stats -> getHPMaxBase() * 100) / 9999 ;
                    break ;
            }

            if (running_score > selected_score) {
                selected_score = running_score ;
                selected = current ;
            }
        }
    }

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " has selected " << selected ;
        LogGen::print() ;
    #endif

    return selected ;
}

ArtificialIntelligence* ArtificialIntelligence::selectRandomCharacter(const std::set<unsigned long>& list) {
    assert(list.size() > 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " selects a character randomly..." ;
        LogGen::print() ;
    #endif

    if (list.size() == 1) {  // Do not need analysis if only one character listed
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " has selected the only one "
                             << (*(list.begin())) ;
            LogGen::print() ;
        #endif

        return convert(*(list.begin())) ;
    }

    unsigned int index = rand() % list.size() ;
    std::set<unsigned long>::iterator it = list.begin() ;
    advance(it, index) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " has selected " << (*it) ;
        LogGen::print() ;
    #endif

    return convert(*it) ;
}


                                                                   /* ACTIONS */
bool ArtificialIntelligence::tryToHeal(ArtificialIntelligence* other, Status::HEALING what) {
    unsigned short min = thresholdToHeal() ;
    unsigned short hp_level ;
    Potion* potion ;
    WhiteMagic* magic ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " tries to heal " << other << " from " ;
    #endif

    switch (what) {
        case Status::HEAL_ALL:
            // not implemented here
                #ifdef DEBUG_MODE
                    LogGen::stream() << "HEAL_ALL" ;
                    LogGen::print() ;
                    LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                     << "Nothing done, not implemented here!" ;
                    LogGen::print() ;
                #endif
            break ;

        case Status::HEAL_HP:
            hp_level = ((other -> m_statistics -> getHP() * 100) / other -> m_statistics -> getHPMax()) ;

                #ifdef DEBUG_MODE
                    LogGen::stream() << "HEAL_HP with hp_level = "
                                     << hp_level
                                     << " and threshold = "
                                     << min ;
                    LogGen::print() ;
                #endif

            if (hp_level < min)
                return giveHP(other) ;

                #ifdef DEBUG_MODE
                    LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                     << "Nothing done, too much HP" ;
                    LogGen::print() ;
                #endif

            break ;

        case Status::HEAL_MP:
                #ifdef DEBUG_MODE
                    LogGen::stream() << "HEAL_MP" ;
                    LogGen::print() ;
                #endif

            potion = selectBestManaPotion(other) ;
            if (potion) {
                #ifdef DEBUG_MODE
                    LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                     << (potion -> getName()) << "used!" ;
                    LogGen::print() ;
                #endif

                usePotion(other, selectBestManaPotion(other)) ;
                return true ;
            }

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Nothing done, no mana potion found..." ;
                LogGen::print() ;
            #endif

            break ;

        case Status::HEAL_KO:
            #ifdef DEBUG_MODE
                LogGen::stream() << "HEAL_KO" ;
                LogGen::print() ;
            #endif

            return giveHP(other) ;

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Nothing done, still KO..." ;
                LogGen::print() ;
            #endif
            break ;

        case Status::HEAL_STATUS:
            #ifdef DEBUG_MODE
                LogGen::stream() << "HEAL_STATUS" ;
                LogGen::print() ;
            #endif

            magic = selectBestStatusMagicForAlly(other) ;
            if (magic) {
                #ifdef DEBUG_MODE
                    LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                     << "Uses magic to heal..." ;
                    LogGen::print() ;
                #endif

                useWhiteMagic(other, magic) ;
                return true ;
            }

            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Nothing done, still sick" ;
                LogGen::print() ;
            #endif

            break ;
    }

    return false ;
}

bool ArtificialIntelligence::giveHP(ArtificialIntelligence* other) {
    Potion* potion = selectBestLifePotion(other) ;
    WhiteMagic* magic = selectBestLifeMagic(other) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " tries to give HP to " << other ;
        LogGen::print() ;
    #endif

    if (!potion && !magic) {            // No potion, no magic found... no heal!
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << "Nothing found to give HP" ;
            LogGen::print() ;
        #endif
        return false ;
    }
    else if (!potion) {                    // No potion found, use magic instead
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << "Magic " << (magic -> getName())
                             << "used because no potion found" ;
            LogGen::print() ;
        #endif

        useWhiteMagic(other, magic) ;
        return true ;
    }
    else if (!magic) {                     // No magic found, use potion instead
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << "Potion " << (potion -> getName())
                             << "used because no magic found" ;
            LogGen::print() ;
        #endif

        usePotion(other, potion) ;
        return true ;
    }


    // Evaluate best option with a small scoring system
    unsigned char score_potion = 0 ;
    unsigned char score_magic = 0 ;

    // Comparison between MP usage and potion usage
    if ((m_statistics -> getMP()) / ((float) (magic -> getMPNeed())) > (m_inventory -> countItems(potion)))
        score_magic++ ;
    else
        score_potion++ ;

    // Comparison between life points given by both magic and potion
    if (magic -> heal() > potion -> getPoints_HP())
        score_magic++ ;
    else
        score_potion++ ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << "Potion score = " << (int) score_potion
                         << " | Magic score = " << (int) score_magic ;
        LogGen::print() ;
    #endif

    // Assess the result of the scoring system
    unsigned char max_score = max(score_potion, score_magic) ;
    if (score_potion == max_score) {
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << "Potion " << (potion -> getName())
                             << " is best" ;
            LogGen::print() ;
        #endif

        usePotion(other, potion) ;
        return true ;
    }
    else if (score_magic == max_score) {
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << "Magic " << (magic -> getName())
                             << " is best" ;
            LogGen::print() ;
        #endif

        useWhiteMagic(other, magic) ;
            return true ;
    }
    else {
        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << "Cannot decide, random choice" ;
            LogGen::print() ;
        #endif

        // Cannot decide...
        if ((rand() % 2) == 0)
            usePotion(other, potion) ;
        else
            useWhiteMagic(other, magic) ;
        return true ;
    }
}

void ArtificialIntelligence::usePotion(ArtificialIntelligence* other, Potion* potion) {
    assert(other != 0) ;
    assert(potion != 0) ;
    assert(m_inventory -> have(potion)) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " uses potion "
                         << (potion -> getName())
                         << " on " << other ;
        LogGen::print() ;
    #endif

    m_actionmem -> setLastAction(ActionMemory::ACTION_HEALING) ;
    
    // Use the potion, it is removed from the inventory
    m_inventory -> use(potion, 1) ;

    bool statsChange = false ;
    // Apply bonuses
    if (m_statistics -> gainHP(potion -> getPoints_HP())) statsChange = true ;
    if (m_statistics -> gainMP(potion -> getPoints_MP())) statsChange = true ;
    if (m_statistics -> increaseHPMax(potion -> getBonus_HPMax())) statsChange = true ;
    if (m_statistics -> increaseMPMax(potion -> getBonus_MPMax())) statsChange = true ;
    if (m_statistics -> increaseStr(potion -> getBonus_str())) statsChange = true ;
    if (m_statistics -> increaseDef(potion -> getBonus_def())) statsChange = true ;
    if (m_statistics -> increaseMag(potion -> getBonus_mag())) statsChange = true ;
    if (m_statistics -> increasePsy(potion -> getBonus_psy())) statsChange = true ;
    if (m_statistics -> increaseVel(potion -> getBonus_vel())) statsChange = true ;
    if (m_statistics -> increaseLck(potion -> getBonus_lck())) statsChange = true ;
    if (m_statistics -> increasePrc(potion -> getBonus_prc())) statsChange = true ;

    if (statsChange)
        m_status -> updateAllStatusEffects() ;

    // Status effects are always removed using a potion
    vector<MagicEffect*> effects = potion -> getClearEffects() ;
    vector<MagicEffect*>::iterator it ;
    for (it = effects.begin() ; it != effects.end() ; it++)
        m_status -> removeStatusEffect((*it)) ;
}

void ArtificialIntelligence::usePotion(ArtificialIntelligence* other, LifePotion* potion) {
    usePotion(other, (Potion*) potion) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " uses LifePotion "
                         << (potion -> getName())
                         << " on " << other ;
        LogGen::print() ;
    #endif

    short points ;
    switch (potion -> getPower()) {
        case LifePotion::POWER_LOW:
            m_physique -> setBlownOffToTreatedLimbs() ;
            break ;

        case LifePotion::POWER_MEDIUM:
            points = potion -> getPoints_HP() ;
            points = (points * 100) / (m_statistics -> getHPMax()) ;
            if (points < 0) points = 0 ;
            if (points > 100) points = 100 ;
            m_physique -> healFracturedLimbs(points) ;
            break ;

        case LifePotion::POWER_HIGH:
            m_physique -> fullBodyRestore() ;
            break ;
    }
}

void ArtificialIntelligence::useWhiteMagic(ArtificialIntelligence* other, WhiteMagic* magic) {
    assert(other != 0) ;
    assert(magic != 0) ;
    assert((magic -> getMPNeed()) <= (m_statistics -> getMP())) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " uses white magic "
                         << (magic -> getName())
                         << " on " << other ;
        LogGen::print() ;
    #endif

    m_actionmem -> setLastAction(ActionMemory::ACTION_HEALING) ;

    if (!(m_status -> getSilenceState() || m_status -> getParalysedState())) {
        assert(other != 0) ;
        assert(magic != 0) ;
        assert((magic -> getMPNeed()) <= (m_statistics -> getMP())) ;

        m_statistics -> loseMP(magic -> getMPNeed()) ;
        other -> healed((magic -> heal() * (100 + getStatistics() -> getMag())) / 100) ;

        applyMagicStatusEffects(other, magic) ;

        short points ;
        switch (magic -> getPower()) {
            case WhiteMagic::POWER_LOW:
                m_physique -> setBlownOffToTreatedLimbs() ;
                break ;

            case WhiteMagic::POWER_MEDIUM:
                points = magic -> getHealPoints() ;
                points = (points * 100) / (m_statistics -> getHPMax()) ;
                if (points < 0) points = 0 ;
                if (points > 100) points = 100 ;
                m_physique -> healFracturedLimbs(points) ;
                break ;

            case WhiteMagic::POWER_HIGH:
                m_physique -> fullBodyRestore() ;
                break ;
        }
    }
}

void ArtificialIntelligence::useBlackMagic(ArtificialIntelligence* other, BlackMagic* magic) {
    assert(other != 0) ;
    assert(magic != 0) ;
    assert((magic -> getMPNeed()) <= (m_statistics -> getMP())) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " uses black magic "
                         << (magic -> getName())
                         << " on " << other ;
        LogGen::print() ;
    #endif

    m_actionmem -> setLastAction(ActionMemory::ACTION_MAGICAL) ;

    if ((magic -> getMPNeed()) < (m_statistics -> getMP())) {
        m_magicmem -> setLastMagicUsed(magic) ;
        m_statistics -> loseMP(magic -> getMPNeed()) ;
        
        // Compute the damages
        unsigned short damage = magic -> getDamages(other -> m_physique -> getElement()) ;
        short final ;
        final = (damage * (100 + m_statistics -> getMag())) / 100 ;
        final = final - (damage * (other -> m_statistics -> getPsy())) / 100 ;
        other -> damaged(final) ;

        applyMagicStatusEffects(other, magic) ;
    }
}

void ArtificialIntelligence::useWeapon(ArtificialIntelligence* other, bool useStock) {
    assert(other != 0) ;

    /* Check if the character misses its target. Then nothing is done... */
    if ((rand() % 256) > m_statistics -> getPrc()) {
        // The more the character has precision, the less it can miss the target

        #ifdef DEBUG_MODE
            LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                             << this << " misses its target " << other ;
            LogGen::print() ;
        #endif

        return ;
    }

    // Define the last action made by the character
    m_actionmem -> setLastAction(ActionMemory::ACTION_PHYSICAL) ;

    // Prepare the data used to attack
    short damage = 0 ;
    WeaponStatus* held_weapon = (WeaponStatus*) m_physique -> getHeldItem() ;
    Weapon* held_type = (Weapon*) held_weapon -> getItem() ;
    WeaponStatus::STATE state = held_weapon -> getState() ;
    Weapon::DAMAGE_EFFECT effect ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " uses its weapon "
                         << (held_type -> getName())
                         << " on " << other ;
        LogGen::stream() << ((useStock) ? " using stock" : " not using stock") ;
        LogGen::stream() << "Weapon state = " << state ;
        LogGen::print() ;
    #endif

    // Apply the damages to the enemy
    if (state == WeaponStatus::STATE_OK) {
        // Apply the mode of attack
        if (useStock) {
            held_weapon -> shove(damage) ;
            effect = Weapon::EFFECT_FRACTURE ;
        }
        else {
            held_weapon -> shoot(damage) ;
            effect = held_type -> getDamageEffect() ;
        }

        // If the weapon is working, it can damage the targeted character
        other -> damaged(evaluatePhysicalDamages(damage, other)) ;

        // Limbs are damaged too
        if (damage > 0) {
            unsigned short other_hp = other -> m_statistics -> getHPMax() ;
            damage = (damage * 100) / other_hp ;
            other -> m_physique -> damageBody(damage, effect) ;
        }
    }
    else if (held_type -> getWeaponType() == Weapon::TYPE_FIREARM) {
        FirearmStatus* gun = (FirearmStatus*) held_weapon ;

        /* When the weapon cannot be used, try to solve the problem... */
        if (state == WeaponStatus::STATE_JAMMED) {
            gun -> unjam() ;
        }
        else if (state == WeaponStatus::STATE_RELOADING) {
            unsigned char request = gun -> getAmmoRequest() ;
            Firearm* gunDef = (Firearm*) gun -> getItem() ;
            unsigned short gotAmmo = m_inventory -> useAmmo(gunDef, request) ;
            gun -> reload(gotAmmo) ;
        }
    }

    // If the weapon is broken, it is dropped from both inventory and equipment
    if (state == WeaponStatus::STATE_BROKEN) {
        m_inventory -> drop(held_weapon) ;
        m_physique -> clearHeldItem(held_weapon) ;
    }
}

void ArtificialIntelligence::applyMagicStatusEffects(ArtificialIntelligence* other, Magic* magic) {
    assert(other != 0) ;
    assert(magic != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " apply status magic "
                         << (magic -> getName()) << " on " << other ;
        LogGen::print() ;
    #endif

    unordered_map<MagicEffect*, unsigned char> effects ;

    // Add applied side effects
    effects = magic -> getStatusEffects() ;
    for (auto& current : effects) {
        // When magic is used to apply a side effect, it may not work!
        if ((rand() % 100) < current.second)
            other -> m_status -> addStatusEffect(current.first) ;
    }

    // Removed side effects
    effects = magic -> getClearEffects() ;
    for (auto& current : effects) {
        // When magic is used to remove a side effect, it may not work!
        if ((rand() % 100) < current.second)
            other -> m_status -> removeStatusEffect(current.first) ;
    }
}

// @TODO improve with the distance
bool ArtificialIntelligence::hasTooMuchAssaillants(unsigned char threshold) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " tests if has too much assaillants... " ;
        LogGen::print() ;
    #endif

    // Counter
    unsigned int count = 0 ;

    // This is used for the second loop...
    set<unsigned long> colonyMembers ;
    set<unsigned long>::iterator member ;
    ArtificialIntelligence* currentMember ;

    // Prepation of the first loop
    vector<ColonyData*> allColonies = ColonyData::getAllColonies() ;
    vector<ColonyData*>::iterator colony ;
    // Stop if the threshold is reached
    for (colony = allColonies.begin() ; colony != allColonies.end() && count < threshold ; colony++) {
        // Look for the assaillants in every colony
        if ((*colony) -> hasEnemy(m_colony)) {
            colonyMembers = ((*colony) -> getAliveMembers()) ;
            // Stop if the threshold is reached
            for (member = colonyMembers.begin() ; member != colonyMembers.end() && count < threshold ; member++) {
                // Count assaillants
                currentMember = convert(*member) ;
                if ((currentMember -> m_lastEnemy) == this)
                    count++ ;
            }
        }
    }

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << this << " decides with "
                         << count << ", max: " << threshold
                         << " that it is " << (count == threshold) ;
        LogGen::print() ;
    #endif

    return (count == threshold) ;
}


/******************************************************************************/
                                                         /** INITIALIZATIONS **/
void ArtificialIntelligence::initTargetedEnemies(map<ArtificialIntelligence*, unsigned short>& list) {
    ArtificialIntelligence* cur ;                  // Current character analyzed

    set<unsigned long>::iterator it ;
    for (it = (m_colony -> getAliveMembers()).begin() ; it != (m_colony -> getAliveMembers()).end() ; it++) {
        cur = convert(*it) ;
    
        // Insert or increase the amount of allies fighting the same enemy
        if (list.count(cur -> m_lastEnemy) > 0)
            list[cur -> m_lastEnemy]++ ;
        else if ((cur -> m_lastEnemy) != 0)
            list[(cur -> m_lastEnemy)] = 1 ;
    }
}
