#ifndef __POTION_H__
#define __POTION_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include <string>
#include <vector>
#include "../../Item.h"
#include "../../../magic/MagicEffect.h"

class Potion : public Item {
    public:
        /**
         * @brief Les differents types de potions qu'il peut exister
         *        LIFE  pour le regain de vie ;
         *        MANA  pour le regain de magie ;
         *        CARE  pour les soins (antidote, collyre...) ;
         *        BONUS pour les points de caracteristique (force, defense...) ;
         *        KO    pour remettre les personnages KO sur pied.
         */
        enum TYPE {TYPE_LIFE = 0, TYPE_MANA, TYPE_CARE, TYPE_BONUS, TYPE_KO} ;

    private:
        /**  @brief Type de potion dont il s'agit. */
        Potion::TYPE m_type ;

        /** @brief HP et MP redonnes par la potion. */
        short m_points[2] ;

        /** @brief Bonus sur chaque statistique donne definitvement par la potion. */
        char m_bonus[9] ;

        /** @brief Liste des effets que la poition peut effacer. */
        std::vector<MagicEffect*> m_clear_effect ;
    
    public:
        /**
         * @brief Constructeur de potion
         * @param name      Nom de la potion
         * @param desc      Description de la potion
         * @param types     Type de potion dont il s'agit
         */
        Potion(const std::string& name,
               const std::string& desc,
               Potion::TYPE type) ;

        /** @brief Destructeur de potion */
        virtual ~Potion() ;

        /**
         * @brief Ajouter une alteration d'etat qui peut etre supprimee par la
         *        potion.
         * @param effect    L'alteration d'etat qui peut etre supprimee.
         */
        void addClearEffect(MagicEffect* effect) ;

        /**
         * @brief Ajouter les bonus donnes definitivement par la potion.
         */
        void setBonus(short hp = 0,
	                  short mp = 0,
	                  char hpmax = 0,
	                  char mpmax = 0,
	                  char str = 0,
	                  char def = 0,
	                  char mag = 0,
	                  char psy = 0,
	                  char vel = 0,
	                  char lck = 0,
	                  char prc = 0) {
            m_points[0] = hp ;
            m_points[1] = mp ;
            m_bonus[0]  = hpmax ;
            m_bonus[1]  = mpmax ;
            m_bonus[2]  = str ;
            m_bonus[3]  = def ;
            m_bonus[4]  = mag ;
            m_bonus[5]  = psy ;
            m_bonus[6]  = vel ;
            m_bonus[7]  = lck ;
            m_bonus[8]  = prc ;
        }
        
                                                                   /** BONUS **/
        /**
         * @brief Recuperer les HP redonnes par la potion.
         * @return La valeur des soins en HP.
         */
        short getPoints_HP() { return m_points[0] ; }
        /**
         * @brief Recuperer les MP redonnes par la potion.
         * @return La valeur des soins en MP.
         */
        short getPoints_MP() { return m_points[1] ; }
        /**
         * @brief Recuperer le bonus/malus en HP.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBonus_HPMax() { return m_bonus[0] ; }
        /**
         * @brief Recuperer le bonus/malus en MP.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBonus_MPMax() { return m_bonus[1] ; }
        /**
         * @brief Recuperer le bonus/malus en force.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBonus_str() { return m_bonus[2] ; }
        /**
         * @brief Recuperer le bonus/malus en defense.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBonus_def() { return m_bonus[3] ; }
        /**
         * @brief Recuperer le bonus/malus en puissance magique.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBonus_mag() { return m_bonus[4] ; }
        /**
         * @brief Recuperer le bonus/malus en defense magique.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBonus_psy() { return m_bonus[5] ; }
        /**
         * @brief Recuperer le bonus/malus en rapidite.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBonus_vel() { return m_bonus[6] ; }
        /**
         * @brief Recuperer le bonus/malus en chance.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBonus_lck() { return m_bonus[7] ; }
        /**
         * @brief Recuperer le bonus/malus en precision.
         * @return Le bonus (valeur positive) ou malus (valeur negative).
         */
        char getBonus_prc() { return m_bonus[8] ; }

        /**
         * @brief Retourner la liste des alterations d'etats qui peuvent etre
         *        supprimees par la potion.
         * @return La liste des alterations d'etats qui peuvent etre supprimees.
         */
        const std::vector<MagicEffect*>& getClearEffects() {
            return m_clear_effect ;
        }



        /**
		 * @brief Savoir si l'objet se tient a deux mains.
		 * @return TRUE si se tient a deux mains, FALSE sinon.
		 */
		virtual bool isTwoHands() const { return false ; }

        /**
         * @brief Recuperer le type de potion dont il s'agit
         * @return Le type de la potion en question
         */
        Potion::TYPE getType() const { return m_type ; }
} ;
#endif
