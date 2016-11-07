#ifndef __SHIELD_H__
#define __SHIELD_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "Armor.h"

/** @brief Creer un bouclier pour l'armure du personnage. Un bouclier n'utilise.
 *         Toujours qu'une seule main du personnage. */
class Shield : public Armor {
	/** @brief Pourcentage de parade possible avec le bouclier */
	unsigned char m_parade ; // Boucliers uniquement

    public:
        /**
         * @brief Constructeur de bouclier.
         * @param name              Nom du bouclier.
         * @param desc              Description du bouclier.
         * @param parade            Niveau de parade (esquive) apporte.
         * @param hardness          Durete du bouclier.
         * @param percent_hardness  Aleas dans la perte de durete du bouclier.
         * @param element           Element du bouclier.
         */
        Shield(std::string name,
	           std::string desc,
	           unsigned char parade,
	           unsigned char hardness,
	           unsigned char percent_hardness,
	           MagicElement* el) ;
       
       /**
        * @brief Destructeur de bouclier
        */
       virtual ~Shield() {}
       
       /**
        * @brief Recuperer le niveau de parade du bouclier
        * @return Le niveau de parade
        */
       unsigned char getParade() const { return m_parade ; }
} ;
#endif
