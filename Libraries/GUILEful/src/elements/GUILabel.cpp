#include <elements/GUILabel.h>


namespace Guile {

    GUILabel::GUILabel(const std::string& text) : GUIElement() {
        adjustText(text) ;
    }

    GUILabel::~GUILabel() {}



    bool GUILabel::trigger(int, int, int, int, void*) {
        return false ;
    }



    const std::string& GUILabel::getText() const {
        return m_text ;
    }

    void GUILabel::setText(const std::string& text) {
        adjustText(text) ;
    }


    void GUILabel::adjustText(const std::string&) {}

} ;