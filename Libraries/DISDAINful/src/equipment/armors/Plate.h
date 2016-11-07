#ifndef __PLATE_H__
#define __PLATE_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "Armor.h"

/** @brief Creer une armure (tronc) du personnage. */
class Plate : public Armor {
    public:
        /**
         * @brief Constructeur d'armure (tronc).
         * @param name              Nom de l'armure.
         * @param desc              Description de l'armure.
         * @param hardness          Durete de l'armure.
         * @param percent_hardness  Aleas dans la perte de durete de l'armure.
         * @param element           Element de l'armure.
         */
        Plate(std::string name,
	          std::string desc,
	          unsigned char hardness,
	          unsigned char percent_hardness,
	          MagicElement* el) ;
       
       /**
        * @brief Destructeur d'armure (tronc).
        */
       virtual ~Plate() {}
} ;
#endif
