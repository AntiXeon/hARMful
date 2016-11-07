#ifndef __MAGIC_H__
#define __MAGIC_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include "MagicEffect.h"
#include "MagicElement.h"
#include <string>
#include <unordered_map>

/**
 * @brief Classe abstraite pour creer les differents types de magie du jeu.
 */
class Magic {
	protected :
		/** @brief Nom de la magie. */
		std::string m_name ;
		
		/** @brief Description de la magie. */
		std::string m_desc ;
		
		/** @brief Degats moyens causes par la magie. */
		unsigned short m_damages ;
		
		/** @brief Variance des degats causes. */
		unsigned short m_variance ;
		
		/** @brief Consommation en points de magie pour le personnage. */
		unsigned short m_mp_used ;
		
		/** @brief Element de la magie. */
		MagicElement* m_element ;

        /** @brief Liste des effets que la magie peut causer avec le pourcentage
         *         de reussite. */
        std::unordered_map<MagicEffect*, unsigned char> m_status_effect ;

        /** @brief Liste des effets que la magie peut effacer avec le
         *         pourcentage de reussite. */
        std::unordered_map<MagicEffect*, unsigned char> m_clear_effect ;
		
	public :
                                                           /** CONSTRUCTEURS **/	
		/**
		 * @brief Constructeur de sortilege de base.
		 * @param name		Nom du sort.
		 * @param desc		Description de la magie.
		 * @param damage	Dommages causes par le sortilege.
		 * @param variance	Variance des degats causés par le sortilege.
		 * @param mp_used	Quantité de MP utilisés par le sortilege.
		 */
		Magic(const std::string& name,
			  const std::string& desc,
			  unsigned short damages,
			  unsigned short variance,
			  unsigned short mp_used,
			  MagicElement* el) ;
		
		/**
		 * @brief Destructeur de magie basique
		 */
		virtual ~Magic() ;

		                                                      /** MODIFIEURS **/
        /**
         * @brief Ajouter une alteration d'etat avec son taux de reussite quand
         *        la magie est lancee.
         * @param effect    L'alteration d'etat.
         * @param precision Taux de reussite de l'alteration d'etat en
         *                  pourcentage, superieur a 0 et inferieure ou egale a
         *                  100 (sinon il sera compris entre 1% et 100%).
         */
        void addStatusEffect(MagicEffect* effect, unsigned char precision) {
            if (precision < 1) precision = 1 ;
            else if (precision > 100) precision = 100 ;

            m_status_effect.insert(std::pair<MagicEffect*, unsigned char> (effect, precision)) ;
        }

        /**
         * @brief Ajouter une alteration d'etat qui peut etre supprimee quand la
         *        magie est lancee.
         * @param effect    L'alteration d'etat qui peut etre supprimee par le
         *                  sortilege.
         * @param precision Taux de reussite de suppression en pourcentage,
         *                  superieur a 0 et inferieure ou egale a 100 (sinon il
         *                  sera compris entre 1% et 100%).
         */
        void addClearEffect(MagicEffect* effect, unsigned char precision) {
            if (precision < 1) precision = 1 ;
            else if (precision > 100) precision = 100 ;

            m_clear_effect.insert(std::pair<MagicEffect*, unsigned char> (effect, precision)) ;
        }

                                                              /** ACCESSEURS **/
        /**
         * @brief Retourner le nom du sortilege.
         * @return Le nom du sort.
         */
		const std::string& getName() { return m_name ; }
		
		/**
         * @brief Retourner la description du sortilege.
         * @return La description du sort.
         */
		const std::string& getDesc() { return m_desc ; }
		
		/**
		 * @brief Retourner les degats moyens causes par le sortilege.
		 * @return Le degats moyens.
		 */
		unsigned short getDamages() { return m_damages ; } ;

        /**
         * @brief Retourner les MP requis par le sortilege.
         * @return La quantité de MP requis.
         */
		unsigned short getMPNeed() const { return m_mp_used ; }
		
		/**
		 * @brief Retourner l'element de la magie.
		 * @return L'element de la magie.
		 */
		MagicElement* getElement() const { return m_element ; }

        /**
         * @brief Retourner la liste des alterations d'etats applicables et leur
         *        taux de reussite.
         * @return La liste des alterations d'etats qui peuvent etre causes par
         *         le sortilege.
         */
        const std::unordered_map<MagicEffect*, unsigned char>& getStatusEffects() {
            return m_status_effect ;
        }

        /**
         * @brief Retourner la liste des alterations d'etats qui peuvent etre
         *        supprimees par la magie.
         * @return La liste des alterations d'etats qui peuvent etre supprimees.
         */
        const std::unordered_map<MagicEffect*, unsigned char>& getClearEffects() {
            return m_clear_effect ;
        }
} ;
#endif
