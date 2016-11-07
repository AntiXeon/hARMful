#ifndef __ARMOR_H__
#define __ARMOR_H__
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include "../Item.h"
#include "../../magic/MagicElement.h"

/**
 * @brief Une armure de base meritant d'etre derivee en elements plus precis/
 *        Peut servir a attribuer un element a un personnage quelconque.
 */
class Armor : public Item {
    public:
        enum TYPE { TYPE_SHIELD = 0, TYPE_PLATE, TYPE_HELMET, TYPE_GAUNTLETS, TYPE_BOOTS } ;

    protected :
		/* BONUS */
        /** @brief Bonus de HP. */
        short m_hp ;
        /** @brief Bonus de MP. */
        short m_mp ;
        /** @brief Bonus de force physique. */
        char m_str ;
        /** @brief Bonus de defense physique. */
		char m_def ;
		/** @brief Bonus de force magique. */
		char m_mag ;
		/** @brief Bonus de defense magique. */
		char m_psy ;
		/** @brief Bonus de rapidite. */
		char m_vel ;
		/** @brief Bonus de chance (coups critiques). */
		char m_lck ;
		/** @brief Bonus de precision des attaques physiques. */
		char m_prc ;

        /* PROPRIETES PHYSIQUES */
		/** @brief Robustesse de l'armure. */
		short m_hardness ;
		/** @brief Risques que l'armure se degrade en pourcentage. */
		short m_percent_hardness ;
		/** @brief Element de l'arme. */
		MagicElement* m_element ;
		/** @brief Type d'armure. */
		TYPE m_type ;

	public:
	    Armor(std::string name,
	          std::string desc,
	          unsigned char hardness,
	          unsigned char percent_hardness,
	          MagicElement* el) ;

	   ~Armor() {}

        /**
		 * @brief Savoir si l'objet se tient a deux mains.
		 * @return TRUE si se tient a deux mains, FALSE sinon.
		 */
		virtual bool isTwoHands() const { return false ; }

        /**
		 * @brief Savoir si l'armure est cassee.
		 * @return Indique si l'armure est cassee (TRUE) ou pas (FALSE).
		 */
		bool isBroken() { return (m_hardness == 0) ? true : false ; }

        /** @brief Perte de durete de l'armure. */
		virtual void consume() ;

        /**
		 * @brief Recuperer la durete maximale de l'armure.
		 * @return La durete maximale que l'armure peut avoir.
		 */
		unsigned char getHardness() { return m_hardness ; }

        /**
		 * @brief Recuperer le pourcentage representant le risque que l'armure
		 *        s'use quand elle est utilisee.
		 * @return Le pourcentage de risque que l'armure s'abime.
		 */
		unsigned char getPercentHardness() { return m_percent_hardness ; }
		
        /**
		 * @brief Recuperer l'element de l'armure.
		 * @return L'element magique.
		 */
		MagicElement* getElement() const { return m_element ; }
		
        /**
		 * @brief Recuperer le type d'armure.
		 * @return Le type d'armure.
		 */
		TYPE getTYPE() const { return m_type ; }

        /**
         * @brief Definir les bonus/malus donnes par l'armure.
         * @param hp        Bonus de HP.
         * @param mp        Bonus de MP.
         * @param str       Bonus de force physique.
         * @param def       Bonus de defense physique.
         * @param mag       Bonus de magie.
         * @param psy       Bonus de defense magique.
         * @param vel       Bonus de rapidite.
         * @param lck       Bonus de chance.
         * @param prc       Bonus de precision.
         */
		void setBonus(short hp,
		              short mp,
		              char str,
		              char def,
		              char mag,
		              char psy,
		              char vel,
		              char lck,
		              char prc) ;
} ;
#endif
