#include <elements/text/GUITextElement.h>
#include <debug/Test.h>


namespace Guile {

    GUITextElement::GUITextElement(
                                const char* initialText,
                                GUICaret* caret
                                ) : GUIElement() {
        m_text.append(initialText) ;
        m_caret = caret ;
    }

    GUITextElement::~GUITextElement() {
        if (m_caret != NULL)
            delete m_caret ;
    }


    void GUITextElement::insertCharacter(char character) {
        if (m_caret != NULL) {
            size_t caretPosition = m_caret -> getPositionInText() ;
            m_text.insert(m_text.begin() + caretPosition, character) ;
        }
        else {
            m_text.push_back(character) ;
        }
            
    }

    void GUITextElement::deleteCharacterBeforeCaret() {
        size_t position ;

        if (m_caret != NULL)
            position = (m_caret -> getPositionInText()) - 1 ;
        else
            position = m_text.size() - 1 ;

        m_text.erase(position, 1) ;
    }

} ;