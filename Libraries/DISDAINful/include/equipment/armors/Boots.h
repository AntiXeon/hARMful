#ifndef __BOOTS_H__
#define __BOOTS_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "Armor.h"

/** @brief Creer des bottes pour l'armure du personnage. */
class Boots : public Armor {
    public:
        /**
         * @brief Constructeur de bottes.
         * @param name              Nom des bottes.
         * @param desc              Description des bottes.
         * @param hardness          Durete des bottes.
         * @param percent_hardness  Aleas dans la perte de durete des bottes.
         * @param element           Element des bottes.
         */
        Boots(std::string name,
	          std::string desc,
	          unsigned char hardness,
	          unsigned char percent_hardness,
	          MagicElement* el) ;
       
       /**
        * @brief Destructeur d'armure (tronc).
        */
       virtual ~Boots() {}
} ;
#endif
