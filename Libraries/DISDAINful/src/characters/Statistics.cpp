#include "Statistics.h"

#include <assert.h>

using namespace std ;

Statistics::Statistics() {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION from scratch" ;
        LogGen::print() ;
    #endif

    /* Statistiques de base d'un personnage, si non modifiees avec setStats() */
    m_level = 1 ;
    m_exp = 0 ;
    m_hp = m_hpmaxbase = m_hpmaxbonus = 150 ;
    m_mp = m_mpmaxbase = m_mpmaxbonus = 30 ;
    m_strbase = m_strbonus = 15 ;		// Coup porté = arme + % de force ;
	m_defbase = m_defbonus = 10 ;		// Coup reçu = arme - % de défense ;
	m_magbase = m_magbonus = 10 ;		// Magie lancée = magie + % magie ;
	m_psybase = m_psybonus = 8 ;	    // Coup reçu = magie - % de défense ;
	m_velbase = m_velbonus = 120 ;	    // Vitesse de remplissage de la jauge d'action (voir Character.h)
	m_lckbase = m_lckbonus = 5 ;		// % de chance de faire un coup critique (double les dégats)
	m_prcbase = m_prcbonus = 100 ;		// % de chance de réussir une attaque physique
}

Statistics::Statistics(int level, int exp,
	                   int hp, int mp,
	                   int str, int def, int mag, int psy, int vel, int lck, int prc) {
    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " CREATION with parameters" ;
        LogGen::print() ;
    #endif

    setStats(level, exp, hp, mp, str, def, mag, psy, vel, lck, prc) ;
}

Statistics::~Statistics() {}


void Statistics::setStats(int level, int exp,
		                  int hp, int mp,
		                  int str, int def, int mag, int psy, int vel, int lck, int prc) {
    assert(level > 0) ;
    assert(exp > -1) ;
    assert(hp > 0) ;
    assert(mp > 0) ;
    assert(str > -1) ;
    assert(def > -1) ;
    assert(mag > -1) ;
    assert(psy > -1) ;
    assert(vel > -1) ;
    assert(lck > -1) ;
    assert(prc > -1) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " stats modification" ;
        LogGen::print() ;
    #endif

    m_level = (level < 101) ? level : 100 ;
    m_exp = exp ;

    if (hp == 0) hp = 1 ;
    if (mp == 0) mp = 1 ;
    if (hp > 9999)  hp = 9999 ;
    if (mp > 999)   mp = 999 ;
    if (str > 255)  str = 255 ;
    if (def > 255)  def = 255 ;
    if (mag > 255)  mag = 255 ;
    if (psy > 255)  psy = 255 ;
    if (vel > 255)  vel = 255 ;
    if (lck > 255)  lck = 255 ;
    if (prc > 255)  prc = 255 ;

    m_hpmaxbase = m_hpmaxbonus = m_hp = hp ;
    m_mpmaxbase = m_mpmaxbonus = m_mp = mp ;
    
    m_strbase = m_strbonus = str ;
    m_defbase = m_defbonus = def ;
    m_magbase = m_magbonus = mag ;
    m_psybase = m_psybonus = psy ;
    m_velbase = m_velbonus = vel ;
    m_lckbase = m_lckbonus = lck ;
    m_prcbase = m_prcbonus = prc ;
}

// @TODO utiliser methodes pour verifier si depassement de capacite
// Ne s'applique pas aux HP/MP restants car le decompte se fait a chaque tour.
void Statistics::addStatusEffect(MagicEffect* effect) {
    assert(effect != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " add effect " << (effect -> getName()) ;
        LogGen::print() ;
    #endif
    
    /* Le fait de multiplier par 21 puis de shifter de 11 bits produit une
       division par 100 plus optimisee (et rapide) qu'en passant par des float. */
    if (effect -> isPercent()) {
        // Effet exprime en pourcentages.
        m_hpmaxbonus += (m_hpmaxbase * effect -> getBM_HPMax()) / 100 ;
        m_mpmaxbonus += (m_mpmaxbase * effect -> getBM_MPMax()) / 100 ;
        m_strbonus   += (m_strbase * effect -> getBM_str()) / 100 ;
        m_defbonus   += (m_defbase * effect -> getBM_def()) / 100 ;
        m_magbonus   += (m_magbase * effect -> getBM_mag()) / 100 ;
        m_psybonus   += (m_psybase * effect -> getBM_psy()) / 100 ;
        m_velbonus   += (m_velbase * effect -> getBM_vel()) / 100 ;
        m_lckbonus   += (m_lckbase * effect -> getBM_lck()) / 100 ;
        m_prcbonus   += (m_prcbase * effect -> getBM_prc()) / 100 ;
    }
    else {
        // Effet exprime en valeurs brutes.
        m_hpmaxbonus    = m_hpmaxbonus + effect -> getBM_HPMax() ;
        m_mpmaxbonus    = m_mpmaxbonus + effect -> getBM_MPMax() ;
        m_strbonus      = m_strbonus + effect -> getBM_str() ;
        m_defbonus      = m_defbonus + effect -> getBM_def() ;
        m_magbonus      = m_magbonus + effect -> getBM_mag() ;
        m_psybonus      = m_psybonus + effect -> getBM_psy() ;
        m_velbonus      = m_velbonus + effect -> getBM_vel() ;
        m_lckbonus      = m_lckbonus + effect -> getBM_lck() ;
        m_prcbonus      = m_prcbonus + effect -> getBM_prc() ;
    }
}

bool Statistics::applyStatusEffect(MagicEffect* effect) {
    assert(effect != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " apply effect " << (effect -> getName()) ;
        LogGen::print() ;
    #endif

    bool alive = true ;
    if (effect -> isPercent()) {
        // Effet exprime en pourcentages.
        // HP
        if ((effect -> getBM_HP()) < 0) {
            loseHP(-(m_hpmaxbase * effect -> getBM_HP()) / 100) ;
            if (m_hp < 1) alive = false ;
        }
        else
            gainHP((m_hpmaxbase * effect -> getBM_HP()) / 100) ;
        // MP
        if ((effect -> getBM_MP()) < 0)
            loseMP(-(m_mpmaxbase * effect -> getBM_MP()) / 100) ;
        else
            gainMP((m_mpmaxbase * effect -> getBM_MP()) / 100) ;

        // Effet exprime en pourcentages.
        m_hpmaxbonus += (m_hpmaxbase * effect -> getBM_HPMax()) / 100 ;
        m_mpmaxbonus += (m_mpmaxbase * effect -> getBM_MPMax()) / 100 ;
        m_strbonus   += (m_strbase * effect -> getBM_str()) / 100 ;
        m_defbonus   += (m_defbase * effect -> getBM_def()) / 100 ;
        m_magbonus   += (m_magbase * effect -> getBM_mag()) / 100 ;
        m_psybonus   += (m_psybase * effect -> getBM_psy()) / 100 ;
        m_velbonus   += (m_velbase * effect -> getBM_vel()) / 100 ;
        m_lckbonus   += (m_lckbase * effect -> getBM_lck()) / 100 ;
        m_prcbonus   += (m_prcbase * effect -> getBM_prc()) / 100 ;
    }
    else {
        // Effet exprime en valeurs brutes.
        // HP
        if ((effect -> getBM_HP()) < 0) {
            loseHP((effect -> getBM_HP())) ;
            if (m_hp < 1) alive = false ;
        }
        else gainHP((effect -> getBM_HP())) ;
        // MP
        if ((effect -> getBM_MP()) < 0) loseMP((effect -> getBM_MP())) ;
        else gainMP(effect -> getBM_MP()) ;

        m_hpmaxbonus    = m_hpmaxbonus + effect -> getBM_HPMax() ;
        m_mpmaxbonus    = m_mpmaxbonus + effect -> getBM_MPMax() ;
        m_strbonus      = m_strbonus + effect -> getBM_str() ;
        m_defbonus      = m_defbonus + effect -> getBM_def() ;
        m_magbonus      = m_magbonus + effect -> getBM_mag() ;
        m_psybonus      = m_psybonus + effect -> getBM_psy() ;
        m_velbonus      = m_velbonus + effect -> getBM_vel() ;
        m_lckbonus      = m_lckbonus + effect -> getBM_lck() ;
        m_prcbonus      = m_prcbonus + effect -> getBM_prc() ;
    }
    return alive ;
}

void Statistics::removeStatusEffect(MagicEffect* effect) {
    assert(effect != 0) ;

    #ifdef DEBUG_MODE
        LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                         << " remove effect " << (effect -> getName()) ;
        LogGen::print() ;
    #endif

    if (!(effect -> isRepeat())) {
        /* Si le personnage n'a plus a etre affecte par un effet non
           repetitif, il retrouve ses statistiques */
        if (effect -> isPercent()) {
            // Effet exprime en pourcentages.
            m_hpmaxbonus -= (m_hpmaxbase * effect -> getBM_HPMax()) / 100 ;
            m_mpmaxbonus -= (m_mpmaxbase * effect -> getBM_MPMax()) / 100 ;
            m_strbonus   -= (m_strbase * effect -> getBM_str()) / 100 ;
            m_defbonus   -= (m_defbase * effect -> getBM_def()) / 100 ;
            m_magbonus   -= (m_magbase * effect -> getBM_mag()) / 100 ;
            m_psybonus   -= (m_psybase * effect -> getBM_psy()) / 100 ;
            m_velbonus   -= (m_velbase * effect -> getBM_vel()) / 100 ;
            m_lckbonus   -= (m_lckbase * effect -> getBM_lck()) / 100 ;
            m_prcbonus   -= (m_prcbase * effect -> getBM_prc()) / 100 ;
        }
        else {
            // Effet exprime en valeurs brutes.
            m_hpmaxbonus    = m_hpmaxbonus - effect -> getBM_HPMax() ;
            m_mpmaxbonus    = m_mpmaxbonus - effect -> getBM_MPMax() ;
            m_strbonus      = m_strbonus - effect -> getBM_str() ;
            m_defbonus      = m_defbonus - effect -> getBM_def() ;
            m_magbonus      = m_magbonus - effect -> getBM_mag() ;
            m_psybonus      = m_psybonus - effect -> getBM_psy() ;
            m_velbonus      = m_velbonus - effect -> getBM_vel() ;
            m_lckbonus      = m_lckbonus - effect -> getBM_lck() ;
            m_prcbonus      = m_prcbonus - effect -> getBM_prc() ;
        }
    }
}
