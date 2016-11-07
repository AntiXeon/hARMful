#ifndef __BLACK_MAGIC_H__
#define __BLACK_MAGIC_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include "Magic.h"
#include "MagicEffect.h"
#include <string>
#include <vector>

/**
 * @brief Magie noire, de la simple braise à la foudre qui ravage tout.
 * @see Magic
 */
class BlackMagic : public Magic {
	public :
		/**
		 * @brief Creation d'un sortilège de magie noire.
		 * @param name			Nom du sort magique.
		 * @param damage		Dégats moyens causés par le sort.
		 * @param variance		Puissance du sort (pourcentage).
		 * @param mp_used		Quantité de MP utilisés par le sortilège.
		 */
		BlackMagic(const std::string& name,
				   const std::string& desc,
				   unsigned short damages,
				   unsigned short variance,
				   unsigned short mp_used,
				   MagicElement* el) ;
		
		/** @brief Destructeur de magie noire */
		virtual ~BlackMagic() ;
		
		/**
		 * @brief Retourner les dégâts causés par l'attaque magique
		 */
		short getDamages(MagicElement* target) ;
} ;
#endif
