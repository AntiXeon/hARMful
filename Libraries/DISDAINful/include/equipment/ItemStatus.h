#ifndef __ITEMSTATUS_H__
#define __ITEMSTATUS_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include "Item.h"

class ItemStatus {
    public:
        /**
         * @brief Qualite initiale de l'objet a sa creation:
         *          - MAXIMAL: qualite maximale par rapport au type d'arme ;
         *          - RANDOM: qualite aleatoire entre 0 et le max du type d'arme.
         */
        enum QUALITY {MAXIMAL = 0, RANDOM } ;

    protected:
        /** @brief Durete de l'objet. Plus cette valeur est proche de 0, plus
         *         l'objet est endommage et risque de se casser. */
        unsigned char m_hardness ;

    public:
        /**
         * @brief Generer l'etat d'un objet.
         * @param hardness  Definir la durete actuelle de l'objet (usure).
         */
        ItemStatus() ;

        /** @brief Detruire l'etat. */
        virtual ~ItemStatus() ;


        /**
		 * @brief Recuperer l'objet.
		 * @return L'objet dont il est question.
		 */
		virtual Item* getItem() = 0 ;

        /**
         * @brief Recuperer l'etat actuel de l'objet.
         * @return La valeur de la durete qui traduit l'usure de l'objet.
         */
        virtual unsigned char getHardness() { return m_hardness ; }

        /**
		 * @brief Savoir si l'objet est casse.
		 * @return TRUE si l'objet est casse, FALSE sinon.
		 */
		virtual bool isBroken() const { return (m_hardness == 0) ? true : false ; }

        /**
		 * @brief Perte de durete de l'arme.
		 * @return FALSE si l'arme est deja cassee, TRUE sinon.
		 */
		virtual bool consume() = 0 ; 
} ;

#endif
