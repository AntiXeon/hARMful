#ifndef __HELMET_H__
#define __HELMET_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "Armor.h"

/** @brief Creer un casque pour l'armure du personnage. */
class Helmet : public Armor {
    public:
        /**
         * @brief Constructeur de casque.
         * @param name              Nom du casque.
         * @param desc              Description du casque.
         * @param hardness          Durete du casque.
         * @param percent_hardness  Aleas dans la perte de durete du casque.
         * @param element           Element du casque.
         */
        Helmet(std::string name,
	          std::string desc,
	          unsigned char hardness,
	          unsigned char percent_hardness,
	          MagicElement* el) ;
       
       /**
        * @brief Destructeur d'armure (tronc).
        */
       virtual ~Helmet() {}
} ;
#endif
