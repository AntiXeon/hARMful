#ifndef __MAGIC_EFFECT_H__
#define __MAGIC_EFFECT_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include <string>

/**
 * @brief Effets secondaires indésirables.
 */
class MagicEffect {
    public :
        /**
         * @brief Les differents types d'effets secondaires possibles.
         *        BONUS:  apporte des bonus aux statistiques.
         *        MALUS:  apporte des malus aux statistiques.
         *        POINTS: modifie la quantite de HP ou de MP au cours du temps.
         */
        enum TYPES { TYPE_BONUS = 0, TYPE_MALUS, TYPE_POINTS_BONUS, TYPE_POINTS_MALUS } ;

        /**
         * @brief Les differents effets sur les "interrupteurs" des personnages.
         *        NONE:         ne modifie pas les interrupteurs (actives ou
         *                      non par un autre effet) ;
         *        DEACTIVATE:   fait passer l'interrupteur a FALSE, le
         *                      personnage peut de nouveau faire l'action.
         *        ACTIVATE:     fait passer l'interrupteur' a TRUE, le
         *                      personnage ne peut plus effectuer l'action en
         *                      question (utiliser de la magie, bouger,
         *                      attaquer...).
         */
        enum SWITCH_STATE { STATE_NONE = 10, STATE_DEACTIVATE, STATE_ACTIVATE } ;

	private :
		/** @brief Nom de l'effet. */
		std::string m_name ;
		
		/** @brief Description de l'effet. */
		std::string m_desc ;
		
		/** @brief Phrase affichee lorsque le personnage est affecte par l'effet. */
		std::string m_applied ;

        /** @brief Type d'effet secondaire. */
		TYPES m_type ;
		
		/**
		 * @brief Duree de l'effet en "tours", 0 pour une duree indeterminee
		 * @TODO Remplacer les tours par du temps reel en secondes.
		 */
		unsigned char m_last ;
		
		/** @brief Savoir si les bonus sont sous la forme de pourcentages ou pas. */
		bool m_percent ;
		
		/**
		 * @brief Repetition de l'effet si TRUE. S'applique une seule fois si
		 *        vaut FALSE.
		 */
		bool m_repeat ;
		
		/**
		 * @brief Liste des interrupteurs d'etats associes a l'effet.
		 *          - m_switchState[0] : silence
		 *          - m_switchState[1] : immobile
		 *          - m_switchState[2] : paralysed
		 *
		 *        Valeurs utilisees :
		 *          - 0 : desactive l'interrupteur
		 *          - 1 : aucun changement (neutre)
		 *          - 2 : active l'interrupteur
		 */
		SWITCH_STATE m_switchState[3] ;

        /** @brief Bonus malus sur chaque statistique associe a l'effet. */
        char m_bonusMalus[11] ;

	public :
		/* ** CONSTRUCTEURS ** */
		/**
		 * @brief Créer un nouvel effet secondaire.
		 * @param name		Nom de l'effet secondaire.
		 * @param desc      Description de l'effet.
		 * @param applied   Phrase affichee lorsque le personnage est affecte
		 *                  par l'effet.
		 * @param last		Durée moyenne de l'effet en tours.
		 * @param variance  Variance des bonus possibles.
		 * @param frequency Chance que l'effet se produise à un tour donné (en
		 *					pourcentages).
		 */
		MagicEffect(TYPES type,
		            const std::string& name,
		            const std::string& desc,
		            const std::string& applied,
				 	unsigned char last,
				 	bool repeat,
				 	bool percent) ;

		/** @brief Destructeur d'un effet. */
		virtual ~MagicEffect() ;
		
		
		/** MODIFIEURS **/
		/**
		 * @brief Definir les interrupteurs d'etat lies a l'effet.
		 * @param silence   Affecter l'utilisation des magies.
		 * @param immobile  Affecter les deplacement du personnage.
		 * @param paralysed Affecter tous les mouvements du personnage.
		 */
		void setSwitchesState(SWITCH_STATE silence,
		                      SWITCH_STATE immobile,
		                      SWITCH_STATE paralysed) {
		    m_switchState[0] = silence ;
		    m_switchState[1] = immobile ;
		    m_switchState[2] = paralysed ;
		}

		/**
		 * @brief Definir les bonus/malus associes a l'effet.
		 * @param hp    Affecter la sante.
		 * @param mp    Affecter les points de magie.
		 * @param str   Affecter la force.
		 * @param def   Affecter la defense.
		 * @param mag   Affecter la puissance magique.
		 * @param psy   Affecter la defense magique.
		 * @param vel   Affecter la rapidite.
		 * @param lck   Affecter la chance.
		 * @param prc   Affecter la precision.
		 */
		void setBonusMalus(char hp = 0,
		                   char mp = 0,
		                   char hpmax = 0,
		                   char mpmax = 0,
		                   char str = 0,
		                   char def = 0,
		                   char mag = 0,
		                   char psy = 0,
		                   char vel = 0,
		                   char lck = 0,
		                   char prc = 0) {
            m_bonusMalus[0]  = hp ;
            m_bonusMalus[1]  = mp ;
            m_bonusMalus[2]  = hpmax ;
            m_bonusMalus[3]  = mpmax ;
            m_bonusMalus[4]  = str ;
            m_bonusMalus[5]  = def ;
            m_bonusMalus[6]  = mag ;
            m_bonusMalus[7]  = psy ;
            m_bonusMalus[8]  = vel ;
            m_bonusMalus[9]  = lck ;
            m_bonusMalus[10] = prc ;
        }

		/* ** ACCESSEURS ** */
		/**
		 * @brief Recuperer le nom de l'effet.
		 * @return Le nom de l'effet.
		 */
		const std::string& getName() { return m_name ; }
        /**
		 * @brief Recuperer la description de l'effet.
		 * @return La description de l'effet.
		 */
        const std::string& getDesc() { return m_desc ; }
        /**
		 * @brief Recuperer la phrase associee a l'effet.
		 * @return La phrase associee a l'effet quand il est active.
		 */
        const std::string& getApplied() { return m_applied ; }
        /**
		 * @brief Recuperer le type d'effet.
		 * @return Le type d'effet dont il s'agit.
		 */
		TYPES getType() const { return m_type ; }
		/**
		 * @brief Recuperer la durée de l'effet en tours.
		 * @return La durée de l'effet en tours.
		 */
		unsigned char getLast() const { return m_last ; }
        /**
		 * @brief Savoir si le bonus/malus s'exprime en pourcentage (par rapport
		 *        aux statistiques sans bonus) ou non.
		 * @return TRUE si l'effet s'applique sous forme de pourcentage,
		 *         FALSE si la valeur est figee.
		 */
		bool isPercent() const { return m_percent ; }
        /**
		 * @brief Savoir si l'effet se repete.
		 * @return TRUE si l'effet se repete, FALSE s'il ne s'applique qu'une
		 *         seule fois.
		 */
		bool isRepeat() const { return m_repeat ; }


                                                           /** INTERRUPTEURS **/
        /**
		 * @brief Recuperer la possibilite d'utiliser la magie.
		 * @return La possibilite en question.
		 */
		 SWITCH_STATE getSilenceState() const { return m_switchState[0] ; }

        /**
		 * @brief Recuperer la possibilite de bouger.
		 * @return La possibilite en question.
		 */
		 SWITCH_STATE getImmobileState() const { return m_switchState[1] ; }

        /**
		 * @brief Recuperer la possibilite d'etre paralyse.
		 * @return La possibilite en question.
		 */
		 SWITCH_STATE getParalysedState() const { return m_switchState[2] ; }


                                                             /** BONUS/MALUS **/
        /**
         * @brief Recuperer le bonus/malus en HP.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_HP() { return m_bonusMalus[0] ; }
        /**
         * @brief Recuperer le bonus/malus en MP.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_MP() { return m_bonusMalus[1] ; }
        /**
         * @brief Recuperer le bonus/malus en HP.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_HPMax() { return m_bonusMalus[2] ; }
        /**
         * @brief Recuperer le bonus/malus en MP.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_MPMax() { return m_bonusMalus[3] ; }
        /**
         * @brief Recuperer le bonus/malus en force.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_str() { return m_bonusMalus[4] ; }
        /**
         * @brief Recuperer le bonus/malus en defense.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_def() { return m_bonusMalus[5] ; }
        /**
         * @brief Recuperer le bonus/malus en puissance magique.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_mag() { return m_bonusMalus[6] ; }
        /**
         * @brief Recuperer le bonus/malus en defense magique.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_psy() { return m_bonusMalus[7] ; }
        /**
         * @brief Recuperer le bonus/malus en rapidite.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_vel() { return m_bonusMalus[8] ; }
        /**
         * @brief Recuperer le bonus/malus en chance.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_lck() { return m_bonusMalus[9] ; }
        /**
         * @brief Recuperer le bonus/malus en precision.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBM_prc() { return m_bonusMalus[10] ; }
} ;
#endif
