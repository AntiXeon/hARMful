#ifndef __WEAPON_H__
#define __WEAPON_H__

    #ifdef DEBUG_MODE
        #include "../../utils/LogGen.h"
    #endif

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../Item.h"
#include "../../magic/MagicElement.h"

/**
 * @brief A weapon is used to attack other characters.
 * @version 1.0     Primitive version
 * @version 2.0 20/04/2013  Added stock damage.
 */
class Weapon : public Item {
    public:
        /**
         * @brief Type of weapon.
         *          - BLADE:    blade weapons ;
         *          - FIREARM:  shotguns, bows, etc ;
         *          - DEFAULT:  default weapons linked to the bodies.
         */
        enum WEAPON_TYPES { TYPE_BLADE = 0, TYPE_FIREARM, TYPE_DEFAULT } ;

        /**
         * @brief Type of damage caused by the weapon:
         *          - NONE:     undefined damage type ;
         *          - BLOWOFF:  limbs are blown off ;
         *          - FRACTURE: limbs are fractured ;
         *          - RANDOM:   limbs are either blown off or fractured.
         */
        enum DAMAGE_EFFECT { EFFECT_NONE = 10, EFFECT_BLOWOFF, EFFECT_FRACTURE, EFFECT_RANDOM } ;

	protected :
//        /* BONUS */
//        /** @brief Bonus de HP. */
//        short m_hp ;
//        /** @brief Bonus de MP. */
//        short m_mp ;
//        /** @brief Bonus de force physique. */
//        char m_str ;
//        /** @brief Bonus de defense physique. */
//		char m_def ;
//		/** @brief Bonus de force magique. */
//		char m_mag ;
//		/** @brief Bonus de defense magique. */
//		char m_psy ;
//		/** @brief Bonus de rapidite. */
//		char m_vel ;
//		/** @brief Bonus de chance (coups critiques). */
//		char m_lck ;
//		/** @brief Bonus de precision des attaques physiques. */
//		char m_prc ;

		/* PROPRIETES */
		/** @brief Dommages moyens causes par l'arme elle-meme (sans puissance
		 *         du personnage qui la porte). */
		unsigned short m_damageShoot ;
		/** @brief Dommages moyens causes par un coup de crosse. */
		unsigned short m_damageStock ;
		/** @brief Variance des degats causes par l'arme. */
		unsigned char m_variance ;
		/** @brief Robustesse de l'arme. */
		unsigned char m_hardness ;
		/** @brief Risques que l'arme se degrade en pourcentage. */
		unsigned char m_percentHardness ;
		/** @brief Savoir si l'arme se tient a deux mains ou non. */
		bool m_twoHands ;
		/** @brief Element de l'arme. */
		MagicElement* m_element ;
        /** @brief Type of the weapon. */
        Weapon::WEAPON_TYPES m_weaponType ;
        /** @brief Type of damage caused by the weapon of limbs. */
        Weapon::DAMAGE_EFFECT m_damageShootEffect ;

	public :
		/**
		 * @brief Construction d'une definition d'arme.
		 * @param damageShoot		Points de degats induits par l'arme en
		 *                          "tirant" (balles, lame...).
		 * @param damageStock       Points de degats induits par un coup de
		 *                          crosse.
		 * @param variance			Aleas dans les points de degat en pourcents.
		 * @param hardness 			Nombre d'utilisations restantes.
		 * @param percentHardness	Pourcentage du risque que l'arme s'abime a
		 *							chaque coup porte par son utilisateur.
		 * @param hands				Nombre de mains pour tenir l'arme.
		 */
		Weapon(const std::string& name,
			   const std::string& desc,
			   unsigned short damageShoot,
			   unsigned short damageStock,
			   unsigned char variance,
			   unsigned char hardness,
			   unsigned char percentHardness,
			   Weapon::WEAPON_TYPES type,
			   Weapon::DAMAGE_EFFECT effect,
			   MagicElement* el,
			   bool twoHands = false) ;

		virtual ~Weapon() {}

//        /**
//         * @brief Definir les bonus/malus donnes par l'arme.
//         * @param hp        Bonus de HP.
//         * @param mp        Bonus de MP.
//         * @param str       Bonus de force physique.
//         * @param def       Bonus de defense physique.
//         * @param mag       Bonus de magie.
//         * @param psy       Bonus de defense magique.
//         * @param vel       Bonus de rapidite.
//         * @param lck       Bonus de chance.
//         * @param prc       Bonus de precision.
//         */
//		void setBonus(short hp,
//		              short mp,
//		              char str,
//		              char def,
//		              char mag,
//		              char psy,
//		              char vel,
//		              char lck,
//		              char prc) ;
		/**
		 * @brief Savoir si l'arme se tient a deux mains.
		 * @return Indique si l'arme se tient a deux mains.
		 */
		bool isTwoHands() const { return m_twoHands ; }

        /**
		 * @brief Recuperer la durete maximale de l'arme.
		 * @return La durete maximale que l'arme peut avoir.
		 */
		unsigned char getHardness() { return m_hardness ; }

		/**
		 * @brief Recuperer le pourcentage representant le risque que l'arme
		 *        s'use quand elle est utilisee.
		 * @return Le pourcentage de risque que l'arme s'abime.
		 */
		unsigned char getPercentHardness() { return m_percentHardness ; }

        /**
		 * @brief Recuperer l'element de l'arme
		 * @return L'element magique
		 */
		MagicElement* getElement() const { return m_element ; }

        /**
         * @brief Recuperer les degats moyens au tir (balle, lame...).
         * @return Les degats moyens causes par l'arme en tirant.
         */
        unsigned short getDamageShoot() { return m_damageShoot ; }

        /**
         * @brief Recuperer les degats moyens d'un coup de crosse.
         * @return Les degats moyens causes par l'arme par coup de crosse.
         */
        unsigned short getDamageStock() { return m_damageStock ; }

        /**
		 * @brief Evaluer les degats que l'arme peut causer en tirant.
		 * @return Degats causes par l'arme au tir.
		 */
		virtual short evaluateDamageShoot() ;

        /**
		 * @brief Evaluer les degats que l'arme peut causer par coup de crosse.
		 * @return Degats causes par un coup de crosse.
		 */
		virtual short evaluateDamageStock() ;

        /**
         * @brief Get the type of the weapon.
         * @return Type of the weapon.
         */
        Weapon::WEAPON_TYPES getWeaponType() {
            return m_weaponType ;
        }

        /**
         * @brief Get the type of damage caused by the weapon.
         * @return Type of damage.
         */
        Weapon::DAMAGE_EFFECT getDamageEffect() {
            return m_damageShootEffect ;
        }
} ;
#endif
