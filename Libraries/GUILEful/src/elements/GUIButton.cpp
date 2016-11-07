#include <elements/GUIButton.h>


namespace Guile {

    GUIButton::GUIButton(
                        const std::string& text,
                        Action mainAction
                        ) : GUILabel(text) {
        m_mainAction = mainAction ;
    }

    GUIButton::~GUIButton() {}



    bool GUIButton::trigger(
                            int x,
                            int y,
                            int keyboardKeys,
                            int mouseButtons,
                            void* data
                        ) {
        if (m_mainAction == NULL)
            return false ;

        if (m_bounds.contains(x, y)) {
        m_mainAction(keyboardKeys, mouseButtons, data) ;
        return true ;
    }

    return false ;
    }

} ;
