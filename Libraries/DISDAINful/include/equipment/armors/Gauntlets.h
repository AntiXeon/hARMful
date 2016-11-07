#ifndef __GAUNTLETS_H__
#define __GAUNTLETS_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "Armor.h"

/** @brief Creer des gants pour l'armure du personnage. */
class Gauntlets : public Armor {
    public:
        /**
         * @brief Constructeur de gants.
         * @param name              Nom des gants.
         * @param desc              Description des gants.
         * @param hardness          Durete des gants.
         * @param percent_hardness  Aleas dans la perte de durete des gants.
         * @param element           Element des gants.
         */
        Gauntlets(std::string name,
	              std::string desc,
	              unsigned char hardness,
	              unsigned char percent_hardness,
	              MagicElement* el) ;
       
       /**
        * @brief Destructeur d'armure (tronc).
        */
       virtual ~Gauntlets() {}
} ;
#endif
