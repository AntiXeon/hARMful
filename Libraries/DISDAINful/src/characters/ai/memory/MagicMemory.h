#ifndef __MAGICMEMORY_H__
#define __MAGICMEMORY_H__

    #ifdef DEBUG_MODE
        #include "../../../utils/LogGen.h"
    #endif

#include "../../../AllMagic.h"

/**
 * @brief The magic memory is used to store all the learned magic spells and the
 * status effects applied to the character.
 * @version 1.0 01/04/2013
 */
class MagicMemory {
    private:
        /** @brief The last black magic spell used by the character. */
        BlackMagic* m_lastMagicUsed ;

        /** @brief White magic spells learned by the character. */
        std::vector<WhiteMagic*> m_white_magic ;

        /** @brief Black magic spells learned by the character. */
        std::vector<BlackMagic*> m_black_magic ;

    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Creation of a MagicMemory object. */
        MagicMemory() ;

        /** @brief Destruction of a MagicMemory object. */
        virtual ~MagicMemory() ;

                                                         /** LAST MAGIC USED **/
        /** @brief Get the last magic used by the character. */
        BlackMagic* getLastMagicUsed() {
            return m_lastMagicUsed ;
        }

        /** @brief Get the last magic used by the character. */
        void setLastMagicUsed(BlackMagic* last) {
            m_lastMagicUsed = last ;
        }

                                                      /** BLACK MAGIC SPELLS **/
		/**
         * @brief Learn black magic spell.
         * @param magic     The new spell to learn.
         */
        inline void learnBlackMagic(BlackMagic* const magic) {
            if (!hasMagic(magic))
                m_black_magic.push_back(magic) ;
        }

        /**
         * @brief Learn black magic spell from its name.
         * @param magic     The new spell to learn.
         */
        void learnBlackMagic(const std::string& magic) ;

        /**
         * @brief Forget black magic spell.
         * @param magic     The spell to forget.
         */
        void forgetBlackMagic(BlackMagic* const magic) ;

        /**
         * @brief Forget black magic spell from its name.
         * @param magic     The spell to forget.
         */
        void forgetBlackMagic(const std::string& magic) ;

        /**
         * @brief Get the black magic at the given index.
         * @param index Index of the searched magic.
         * @return Pointer to the black magic ou null pointer if out of range.
         * @warning Assertion thrown if index is out of range.
         */
        inline BlackMagic* getBlackMagic(unsigned short index) const {
            assert (index < m_black_magic.size()) ;
            return m_black_magic[index] ;
        }

        /**
         * @brief Get the list of the learned black magic.
         * @return List of the learned black magic.
         */
        inline const std::vector<BlackMagic*>& getBlackMagic() const {
            return m_black_magic ;
        }

        /**
         * @brief Count amount of learned black magic spells.
         * @return Amount of learned black magic spells.
         */
        inline unsigned short countBlackMagic() {
            return m_black_magic.size() ;
        }

        /**
         * @brief To know if the character has learned the magic.
         * @return TRUE if the character has learned the magic, FALSE else.
         */
        bool hasMagic(BlackMagic* magic) ;

                                                      /** WHITE MAGIC SPELLS **/
        /**
         * @brief Learn white magic spell.
         * @param magic		The new spell to learn.
         */
        inline void learnWhiteMagic(WhiteMagic* const magic) {
	        if (!hasMagic(magic))
	            m_white_magic.push_back(magic) ;
        }

        /**
         * @brief Learn white magic spell from its name.
         * @param magic		The new spell to learn.
         */
        void learnWhiteMagic(const std::string& magic) ;

        /**
         * @brief Forget white magic spell.
         * @param magic     The spell to forget.
         */
        void forgetWhiteMagic(WhiteMagic* const magic) ;

        /**
         * @brief Forget white magic spell from its name.
         * @param magic     The spell to forget.
         */
        void forgetWhiteMagic(const std::string& magic) ;

        /**
         * @brief Get the white magic at the given index.
         * @param index Index of the searched magic.
         * @return Pointer to the white magic.
         * @warning Assertion thrown if index is out of range.
         */
        inline WhiteMagic* getWhiteMagic(unsigned short index) const {
            assert (index < m_white_magic.size()) ;
            return m_white_magic[index] ;
        }

        /**
         * @brief Count amount of learned white magic spells.
         * @return Amount of learned white magic spells.
         */
        inline unsigned short countWhiteMagic() {
            return m_white_magic.size() ;
        }

        /**
         * @brief Get the list of the learned white magic.
         * @return List of the learned white magic.
         */
        inline const std::vector<WhiteMagic*>& getWhiteMagic() const {
            return m_white_magic ;
        }

        /**
         * @brief To know if the character has learned the magic.
         * @return TRUE if the character has learned the magic, FALSE else.
         */
        bool hasMagic(WhiteMagic* magic) ;
} ;

#endif
