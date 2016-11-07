#ifndef __ARMORSTATUS_H__
#define __ARMORSTATUS_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "../ItemStatus.h"
#include "Armor.h"

class ArmorStatus : public ItemStatus {
    protected:
        /** @brief Armure dont il faut decrire l'etat d'usure. */
        Armor* m_armor ;

    public:
        /**
         * @brief Construction de l'etat d'une armure.
         * @param armor     Armure dont il faut decrire l'etat d'usure.
         * @param hardness  Usure de l'armure initiale.
         */
        ArmorStatus(Armor* armor, ItemStatus::QUALITY hardness) ;
        
        /** @brief Destruction de l'etat d'une armure. */
        virtual ~ArmorStatus() ;

                                                              /** ACCESSEURS **/
        /**
         * @brief Recuperer l'armure.
         * @return L'armure dont l'etat est decrit.
         */
        virtual Item* getItem() { return m_armor ; }

                                                                 /** ACTIONS **/
        /**
		 * @brief Perte de durete de l'armure.
		 * @return FALSE si l'armure est deja cassee, TRUE sinon.
		 */
        virtual bool consume() ;
} ;
#endif
