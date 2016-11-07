#ifndef __ITEM_H__
#define __ITEM_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include <string>

class Item {
    public:
        /**
         * @brief Liste des types d'objets :
         *          - ARMOR:    armures (bottes, gantelets, etc) ;
         *          - WEAPON:   arme (couteau, fusil, etc) ;
         *          - AMMO:     munition pour les armes a feu, arbaletes, arcs ;
         *          - POTION:   soins, magie, guerison d'etat, bonus ;
         *          - KEY:      objets cles ;
         *          - OTHER:    autres objets...
         */
        enum TYPE { TYPE_ARMOR = 0, TYPE_WEAPON, TYPE_AMMO, TYPE_POTION, TYPE_KEY, TYPE_OTHER } ;

	protected:
		/** @brief Nom de l'objet */
		std::string m_name ;
	
		/** @brief Description de l'objet */
		std::string m_desc ;
	
		/** @brief Type d'objet */
		TYPE m_type ;
	
	public:
		/**
		 * @brief Construction d'un objet quelconque
		 * @param name	Nom de l'objet
		 * @param desc	Description de l'objet
		 * @param type	Type d'objet (arme, armure, munitions...)
		 */
		Item(const std::string& name, const std::string& desc, TYPE type) ;
		
		/** @brief Destruction de l'objet */
		virtual ~Item() {}
		
		/**
		 * @brief Savoir si l'objet se tient a deux mains.
		 * @return TRUE si se tient a deux mains, FALSE sinon.
		 */
		virtual bool isTwoHands() const = 0 ;
		
		/**
		 * @brief Recuperer le nom de l'objet
		 * @return Le nom de l'objet
		 */
		const std::string& getName() const { return m_name ; }

		/**
		 * @brief Recuperer la description de l'objet
		 * @return La description de l'objet
		 */
		const std::string& getDesc() const { return m_desc ; }

		/**
		 * @brief Recuperer le type de l'objet
		 * @return Le type de l'objet
		 */
		TYPE getType() const { return m_type ; }
} ;
#endif
