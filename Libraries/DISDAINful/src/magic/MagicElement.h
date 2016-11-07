#ifndef __MAGIC_ELEMENT_H__
#define __MAGIC_ELEMENT_H__

    #ifdef DEBUG_MODE
        #include "../utils/LogGen.h"
    #endif

#include <assert.h>
#include <string>
#include <vector>

class MagicElement {
	private:
	    /** @brief To know if the program allows the creation of new elements. */
        static bool AllowCreation ;

	    /**
	     * @brief ID of the MagicElement newly created. It is increased at each
	     * element creation. It is unique.
	     */
        static unsigned char CurrentID ;

		/** @brief Nom de l'Element magique */
		std::string m_name ;
		
		/** @brief ID de l'Element magique */
		unsigned char m_id ;

	public:
		/** @brief Constructeur d'Element magique */
		MagicElement(const std::string& name) ;
		
		/** @brief Destructeur d'Element magique */
		virtual ~MagicElement() ;


		/* ** ACCESSEURS ** */
		/**
		 * @brief Recuperer le nom de l'Element magique
		 * @return Le nom de l'Element magique
		 */
		const std::string& getName() { return m_name ; }
		
		/**
		 * @brief Recuperer l'ID de l'element
		 * @return L'ID de l'element
		 */
		unsigned char getID() const { return m_id ; }

        /** @brief Count the number of elements created. */
        static unsigned char countElements() {
            return MagicElement::CurrentID ;
        }

        /* ** MODIFIEURS ** */
        /**
         * @brief Call this function to stop the creation of new elements.
         * @warning Creating a new magic element after calling this method will
         *          rise an unchecked assertion.
         */
        static void stopCreation() {
            MagicElement::AllowCreation = false ;
        }
} ;
#endif
