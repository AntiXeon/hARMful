#ifndef __GUILE_TEXT_ELEMENT__
#define __GUILE_TEXT_ELEMENT__


#include <elements/GUIElement.h>
#include <elements/text/GUICaret.h>


namespace Guile {

    /**
    * @brief   A GUITextElement is an abstract object that is used to display
    *          and/or receive text from application user.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/31
    */
    class GUITextElement : public GUIElement {
        protected:
            /** @brief  Caret used by the GUITextElement. */
            GUICaret* m_caret ;

            /** @brief  Text contained in the GUITextElement. */
            std::string m_text ;


        public:
            /**
            * @brief   Create a new GUITextElement.
            * @param   initialText     Text displayed on first apparition of the
            *                          GUITextElement.
            * @param   caret           GUICaret subclass to use. NULL to use no
            *                          GUICaret.
            */
            GUITextElement(const char* initialText = "", GUICaret* caret = NULL) ;

            /**
            * @brief   Destruction of the GUITextElement.
            * @warning This destructor deletes the GUICaret.
            */
            virtual ~GUITextElement() ;


            /**
            * @brief   Insert a character at position of the GUICaret.
            *          When no GUICaret is set, the character is added to the end.
            * @param   character   The character to insert.
            */
            void insertCharacter(char character) ;

            /**
            * @brief   Delete the character just before the GUICaret in the content
            *          of the GUITextElement.
            */
            void deleteCharacterBeforeCaret() ;


        protected:
            /** @brief  Get the text width in pixels. */
            virtual unsigned int getTextWidth() = 0 ;
    } ;

} ;

#endif
