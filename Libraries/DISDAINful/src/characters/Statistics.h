#ifndef __STATISTICS_H__
#define __STATISTICS_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include "../magic/MagicEffect.h"

/**
 * @brief Statistiques d'un personnage comme ses force et defense physiques,
 *        magiques, rapidite... ainsi que son evolution (niveau, experience).
 * @see Character
 * @version 1.0 29/10/2012
 */
// @TODO manage evolution of the character...
class Statistics {
    private:
        /** @brief Le niveau atteint par le personnage. */
        unsigned char m_level ;
        /** @brief Points d'experience acquis par le personnage. */
        unsigned int m_exp ;

        /* base  : designe les caracteristiques de base sans bonus/malus*/
        /* bonus : designe les caracteristiques de base avec bonus/malus*/
        /** @brief Nombre de points de vie maximum. */
        short m_hpmaxbase, m_hpmaxbonus ;
        /** @brief Nombre de points de magie maximum. */
        short m_mpmaxbase, m_mpmaxbonus ;

        /** @brief Quantite de points de vie dont dispose le personnage. */
        short m_hp ;
        /** @brief Quantite de points de magie dont dispose le personnage. */
        short m_mp ;
        /** @brief Points de force physique. */
        unsigned short m_strbase, m_strbonus ;
        /** @brief Points de defense physique. */
		unsigned short m_defbase, m_defbonus ;
		/** @brief Points de force magique. */
		unsigned short m_magbase, m_magbonus ;
		/** @brief Points de defense magique. */
		unsigned short m_psybase, m_psybonus ;
		/** @brief Points de rapidite. */
		unsigned short m_velbase, m_velbonus ;
		/** @brief Points de chance (coups critiques). */
		unsigned short m_lckbase, m_lckbonus ;
		/** @brief Points de precision des attaques physiques. */
		unsigned short m_prcbase, m_prcbonus ;


    public:
        /**
	     * @brief Creation des statistiques d'un personnage avec des valeurs par
	     *        defaut initialisees.
	     */
		Statistics() ;
        /**
	     * @brief Creation des statistiques d'un personnage avec des valeurs
	     *        donnees.
	     */
		Statistics(int level, int exp,
                   int hp, int mp,
                   int str, int def, int mag, int psy, int vel, int lck, int prc) ;

        /** @brief Destruction de statistiques. */
		virtual ~Statistics() ;


                                                              /** MODIFIEURS **/
        /** @brief Definir les caracteristiques de base du personnage. */
		 void setStats(int level, int exp,
	                   int hp, int mp,
	                   int str, int def, int mag, int psy, int vel, int lck, int prc) ;

        /** @brief Supprimer tous les bonus appliques aux statistiques. */
        void clearBonus() {
            m_hpmaxbonus = m_hpmaxbase ;
            m_mpmaxbonus = m_mpmaxbase ;
            m_strbonus = m_strbase ;
            m_defbonus = m_defbase ;
            m_magbonus = m_magbase ;
            m_psybonus = m_psybase ;
            m_velbonus = m_velbase ;
            m_lckbonus = m_lckbase ;
            m_prcbonus = m_prcbase ;
        }

        /** @brief Passer au niveau superieur. */
        void levelUp() {
            if (m_level < 100)
                m_level = m_level + 1 ;
        }
        /** @brief Gagner des points d'experience. */
        void increaseExp(unsigned int count) { m_exp += count ; }

        /**
         * @brief Augmenter les HP max de base (et ceux avec bonus).
         * @return TRUE if count is greater than zero.
         */
        bool increaseHPMax(unsigned char count) {
            if (count > 0) {
                m_hpmaxbase += count ;
                if (m_hpmaxbase > 9999) m_hpmaxbase = 9999 ;
                m_hpmaxbonus += count ;
                if (m_hpmaxbonus > 9999) m_hpmaxbonus = 9999 ;
                return true ;
            }
            return false ;
        }
        /**
         * @brief Gagner des HP.
         * @param count     La quantite de HP recus.
         */
        bool gainHP(unsigned short count) {
            if (count > 0) {
                m_hp += count ;
                if (m_hp > m_hpmaxbonus) m_hp = m_hpmaxbonus ;
                return true ;
            }
            return false ;
        }
        /**
         * @brief Perdre des HP.
         * @param count     La quantite de HP perdus.
         */
        bool loseHP(unsigned short count) {
            if (count > 0) {
                if (m_hp < count) m_hp = 0 ;
                else  m_hp -= count ;
                return true ;
            }
            return false ;
        }

        /** @brief Augmenter les MP max de base (et ceux avec bonus). */
        bool increaseMPMax(unsigned char count) {
            if (count > 0) {
                m_mpmaxbase += count ;
                if (m_mpmaxbase > 999) m_mpmaxbase = 999 ;
                m_mpmaxbonus += count ;
                if (m_mpmaxbonus > 999) m_mpmaxbonus = 999 ;
                return true ;
            }
            return false ;
        }
        /**
         * @brief Gagner des HP.
         * @param count     La quantite de HP recus.
         */
        bool gainMP(unsigned short count) {
            if (count > 0) {
                m_mp += count ;
                if (m_mp > m_mpmaxbonus) m_mp = m_mpmaxbonus ;
                return true ;
            }
            return false ;
        }
        /**
         * @brief Perdre des HP.
         * @param count     La quantite de HP perdus.
         */
        bool loseMP(unsigned short count) {
            if (count > 0) {
                if (m_mp < count) m_mp = 0 ;
                else  m_mp -= count ;
                return true ;
            }
            return false ;
        }
        /** @brief Augmenter la force de base (et celle avec bonus). */
        bool increaseStr(unsigned char count) {
            if (count > 0) {
                m_strbase += count ;
                if (m_strbase > 255) m_strbase = 255 ;
                m_strbonus += count ;
                if (m_strbonus > 255) m_strbonus = 255 ;
                return true ;
            }
            return false ;
        }
        /** @brief Augmenter la defense de base (et celle avec bonus). */
        bool increaseDef(unsigned char count) {
            if (count > 0) {
                m_defbase += count ;
                if (m_defbase > 255) m_defbase = 255 ;
                m_defbonus += count ;
                if (m_defbonus > 255) m_defbonus = 255 ;
                return true ;
            }
            return false ;
        }
        /** @brief Augmenter la magie de base (et celle avec bonus). */
        bool increaseMag(unsigned char count) {
            if (count > 0) {
                m_magbase += count ;
                if (m_magbase > 255) m_magbase = 255 ;
                m_magbonus += count ;
                if (m_magbonus > 255) m_magbonus = 255 ;
                return true ;
            }
            return false ;
        }
        /** @brief Augmenter la defense magique de base (et celle avec bonus). */
        bool increasePsy(unsigned char count) {
            if (count > 0) {
                m_psybase += count ;
                if (m_psybase > 255) m_psybase = 255 ;
                m_psybonus += count ;
                if (m_psybonus > 255) m_psybonus = 255 ;
                return true ;
            }
            return false ;
        }
        /** @brief Augmenter la vitesse de base (et celle avec bonus). */
        bool increaseVel(unsigned char count) {
            if (count > 0) {
                m_velbase += count ;
                if (m_velbase > 255) m_velbase = 255 ;
                m_velbonus += count ;
                if (m_velbonus > 255) m_velbonus = 255 ;
                return true ;
            }
            return false ;
        }
        /** @brief Augmenter la vitesse de base (et celle avec bonus). */
        bool increaseLck(unsigned char count) {
            if (count > 0) {
                m_lckbase += count ;
                if (m_lckbase > 255) m_lckbase = 255 ;
                m_lckbonus += count ;
                if (m_lckbonus > 255) m_lckbonus = 255 ;
                return true ;
            }
            return false ;
        }
        /** @brief Augmenter la vitesse de base (et celle avec bonus). */
        bool increasePrc(unsigned char count) {
            if (count > 0) {
                m_prcbase += count ;
                if (m_prcbase > 255) m_prcbase = 255 ;
                m_prcbonus += count ;
                if (m_prcbonus > 255) m_prcbonus = 255 ;
                return true ;
            }
            return false ;
        }


        /**
         * @brief Ajouter un effet secondaire qui s'applique en se basant sur
         *        les statistiques de base.
         * @param effect    L'effet a appliquer aux statistiques.
         */
        void addStatusEffect(MagicEffect* effect) ;
        /**
         * @brief Appliquer un effet secondaire sur les statistiques.
         * @param effect    L'effet a appliquer aux statistiques.
         * @return TRUE si le personnage est toujours vivant, FALSE s'il meurt
         *         en appliquant l'effet...
         */
        bool applyStatusEffect(MagicEffect* effect) ;
        /**
         * @brief Retirer un effet secondaire qui s'applique en se basant sur
         *        les statistiques de base.
         * @param effect    L'effet a effacer des statistiques.
         */
        void removeStatusEffect(MagicEffect* effect) ;

                                                              /** ACCESSEURS **/
        /**
         * @brief Recuperer le niveau actuel du personnage.
         * @return Le niveau du personnage.
         */
        virtual unsigned char getLevel() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " level = " << (int) m_level ;
                LogGen::print() ;
            #endif

            return m_level ;
        }
        /**
         * @brief Recuperer les points d'experience accumules par le personnage.
         * @return Les points d'experience du personnage.
         */
        virtual unsigned int getExperience() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " experience = " << m_level ;
                LogGen::print() ;
            #endif

            return m_exp ;
        }
        /**
		 * @brief Recuperer le nombre de points de vie max au personnage.
		 * @return Les HP maximum avec bonus.
		 */
        virtual unsigned short getHPMax() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " HP max (bonus) = " << m_hpmaxbonus ;
                LogGen::print() ;
            #endif

            return m_hpmaxbonus ;
        }
        /**
		 * @brief Recuperer le nombre de points de magie max au personnage.
		 * @return Les HP maximum avec bonus.
		 */
		virtual unsigned short getMPMax() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " MP max (bonus) = " << m_mpmaxbonus ;
                LogGen::print() ;
            #endif

		    return m_mpmaxbonus ;
	    }
        /**
		 * @brief Recuperer le nombre de points de vie restants au personnage.
		 * @return Les HP restants.
		 */
		virtual unsigned short getHP() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " HP = " << m_hp ;
                LogGen::print() ;
            #endif

		    return m_hp ;
	    }
        /**
		 * @brief Recuperer le nombre de points de magie restants au personnage.
		 * @return Les HP restants.
		 */
		virtual unsigned short getMP() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " MP = " << m_mp ;
                LogGen::print() ;
            #endif

		    return m_mp ;
	    }
        /**
		 * @brief Recuperer les points d'attaque physique du personnage.
		 * @return Les points d'attaque physique et les bonus cumules.
		 */
		virtual unsigned char getStr() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " Strength (bonus) = " << m_strbonus ;
                LogGen::print() ;
            #endif

		    return m_strbonus ;
	    }
		/**
		 * @brief Recuperer les points de defense physique du personnage.
		 * @return Les points de defense physique et les bonus cumules.
		 */
		virtual unsigned char getDef() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " Defense (bonus) = " << m_defbonus ;
                LogGen::print() ;
            #endif

		    return m_defbonus ;
	    }
        /**
		 * @brief Recuperer les points d'attaque magique du personnage.
		 * @return Les points d'attaque magique et les bonus cumules.
		 */
		virtual unsigned char getMag() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " Magic (bonus) = " << m_magbonus ;
                LogGen::print() ;
            #endif

		    return m_magbonus ;
        }
        /**
		 * @brief Recuperer les points de defense magique du personnage.
		 * @return Les points de defense magique et les bonus cumules.
		 */
		virtual unsigned char getPsy() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " Psy (bonus) = " << m_psybonus ;
                LogGen::print() ;
            #endif

		    return m_psybonus ;
		}
        /**
		 * @brief Recuperer les points de rapidite du personnage.
		 * @return Les points de rapidite et les bonus cumules.
		 */
		virtual unsigned char getVel() const {
//            #ifdef DEBUG_MODE
//                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
//                                 << " Velocity (bonus) = " << m_velbonus ;
//                LogGen::print() ;
//            #endif

		    return m_velbonus ;
	    }
        /**
		 * @brief Recuperer les points de chance du personnage.
		 * @return Les points de chance et les bonus cumules.
		 */
		virtual unsigned char getLck() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " Luck (bonus) = " << m_lckbonus ;
                LogGen::print() ;
            #endif

		    return m_lckbonus ;
		}
        /**
		 * @brief Recuperer les points de precision du personnage.
		 * @return Les points de precision et les bonus cumules.
		 */
		virtual unsigned char getPrc() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " Precision (bonus) = " << m_prcbonus ;
                LogGen::print() ;
            #endif

		    return m_prcbonus ;
	    }


                                                    /** STATISTIQUES DE BASE **/
        /**
		 * @brief Recuperer le nombre de points de vie max au personnage.
		 * @return Les HP maximum de base.
		 */
		virtual unsigned short getHPMaxBase() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " HP max (base) = " << m_hpmaxbase ;
                LogGen::print() ;
            #endif

		    return m_hpmaxbase ;
	    }
        /**
		 * @brief Recuperer le nombre de points de magie max au personnage.
		 * @return Les HP maximum de base.
		 */
		virtual unsigned short getMPMaxBase() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << " MP max (base) = " << m_mpmaxbase ;
                LogGen::print() ;
            #endif

		    return m_mpmaxbase ;
	    }
        /**
		 * @brief Recuperer les points d'attaque physique du personnage.
		 * @return Les points d'attaque physique de base.
		 */
		virtual unsigned char getStrBase() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Strength (base) = " << m_strbase ;
                LogGen::print() ;
            #endif

		    return m_strbase ;
	    }
		/**
		 * @brief Recuperer les points de defense physique du personnage.
		 * @return Les points de defense physique de base.
		 */
		virtual unsigned char getDefBase() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Defense (base) = " << m_defbase ;
                LogGen::print() ;
            #endif

		    return m_defbase ;
	    }
        /**
		 * @brief Recuperer les points d'attaque magique du personnage.
		 * @return Les points d'attaque magique de base.
		 */
		virtual unsigned char getMagBase() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Magic (base) = " << m_magbase ;
                LogGen::print() ;
            #endif

		    return m_magbase ;
	    }
        /**
		 * @brief Recuperer les points de defense magique du personnage.
		 * @return Les points de defense magique de base.
		 */
		virtual unsigned char getPsyBase() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Psy (base) = " << m_psybase ;
                LogGen::print() ;
            #endif

		    return m_psybase ;
	    }
        /**
		 * @brief Recuperer les points de rapidite du personnage.
		 * @return Les points de rapidite de base.
		 */
		virtual unsigned char getVelBase() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Velocity (base) = " << m_velbase ;
                LogGen::print() ;
            #endif

		    return m_velbase ;
	    }
        /**
		 * @brief Recuperer les points de chance du personnage.
		 * @return Les points de chance de base.
		 */
		virtual unsigned char getLckBase() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Luck (base) = " << m_lckbase ;
                LogGen::print() ;
            #endif

		    return m_lckbase ;
	    }
        /**
		 * @brief Recuperer les points de precision du personnage.
		 * @return Les points de precision de base.
		 */
		virtual unsigned char getPrcBase() const {
            #ifdef DEBUG_MODE
                LogGen::stream() << __FILE__ << " " << __LINE__ << ": "
                                 << "Precision (base) = " << m_prcbase ;
                LogGen::print() ;
            #endif

		    return m_prcbase ;
	    }

                                                             /** UTILITAIRES **/
        /**
         * @brief Connaitre le ratio normalise de points de vie restants.
         * @return Le ratio calcul en valeurs entieres (plus rapide qu'en
         *         virgule flottante sur CPU). Une valeur de 100 correspond
         *         au maximum par rapport aux HP maximaux si bonus, ou maximaux
         *         de base si malus.
         */
        virtual unsigned char getHPRatio() {
            if (m_hpmaxbonus < m_hpmaxbase)
                return (m_hp * 100) / m_hpmaxbase ;
            else
                return (m_hp * 100) / m_hpmaxbonus ;
        }

        /**
         * @brief Connaitre le ratio normalise de points de magie restants.
         * @return Le ratio calcul en valeurs entieres (plus rapide qu'en
         *         virgule flottante sur CPU). Une valeur de 100 correspond
         *         au maximum par rapport aux HP maximaux si bonus, ou maximaux
         *         de base si malus.
         */
        virtual unsigned char getMPRatio() {
            if (m_mpmaxbonus < m_mpmaxbase)
                return (m_mp * 100) / m_mpmaxbase ;
            else
                return (m_mp * 100) / m_mpmaxbonus ;
        }

        /**
         * @brief Savoir si le personnage est KO.
         * @return TRUE si le personnage est mort, FALSE s'il est vivant.
         */
        virtual bool isKO() { return (m_hp == 0) ? true : false ; }        
} ;

#endif
