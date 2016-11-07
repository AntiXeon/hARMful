#ifndef __WHITE_MAGIC_H__
#define __WHITE_MAGIC_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include "Magic.h"
#include "MagicEffect.h"
#include <string>
#include <vector>

/**
 * @brief Magie blanche pour soigner, guerir et soutenir des personnages.
 * @see Magic
 */
class WhiteMagic : public Magic {
    public:
        /**
         * @brief Power of the magic on limbs.
         *          - LOW:      the magic only stops bleedings.
         *          - MEDIUM:   the magic stops bleeding and heal broken limbs.
         *          - HIGH:     the magic heals blowned off limbs too.
         */
        enum POWER_LIMBS { POWER_LOW = 10, POWER_MEDIUM, POWER_HIGH } ;

        /**
	     * Effets apportes par la magie.
	     * BONUS      : Soutien permettant d'accroitre les stats du perso.
	     * HEAL       : Regain de vie.
	     * REVIVE     : Remise sur pied apres KO.
	     * CLEAR      : Dissiper les effets negatifs sur le personnage.
	     */
	    enum TYPE { TYPE_BONUS = 0, TYPE_HEAL, TYPE_REVIVE, TYPE_CLEAR } ;


	private:
		/** @brief Type de magie parmi celles qui soignent, guerissent et
		 *         renforcent les personnages. */
		WhiteMagic::TYPE m_type ;

        /** @brief Power of the magic. */
        POWER_LIMBS m_power ;


    public:
		/**
		 * @brief Creation d'un sortilege de magie blanche.
		 * @param name			Nom du sort magique.
		 * @param desc          Description de la magie.
		 * @param heal			Soins moyens apportes par le sort.
		 * @param variance		Puissance du sort (pourcentage).
 		 * @param mp_used		Quantite de MP utilisés par le sortilege.
		 */
		WhiteMagic(const std::string& name,
		           const std::string& desc,
				   unsigned short heal,
				   unsigned short variance,
				   unsigned short mp_used,
				   MagicElement* el,
				   TYPE type,
				   POWER_LIMBS power) ;
		
		/** @brief Destructeur */
		virtual ~WhiteMagic() ;

		/**
		 * @brief Retourner les soins apportés par l'attaque magique.
		 * @return Les points rendus apres calcul de la variance.
		 */
		unsigned short heal() ;
		
        /**
		 * @brief Retourner les soins theoriques apportés par l'attaque magique.
		 * @return Les points rendus en moyenne.
		 */
		unsigned short getHealPoints() { return m_damages ; }

        /** @brief Get the power of the magic on limbs. */
        POWER_LIMBS getPower() const { return m_power ; }

        /** @brief Retourner le type de magie blanche. */
        WhiteMagic::TYPE getType() const { return m_type ; }
} ;
#endif
