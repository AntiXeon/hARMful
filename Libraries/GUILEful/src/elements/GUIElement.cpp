#include <elements/GUIElement.h>


namespace Guile {

    GUIElement::GUIElement() : m_parent(NULL) {}

    GUIElement::~GUIElement() {}


    int GUIElement::getX() const {
        return m_bounds.getBottomLeftCornerX() ;
    }

    int GUIElement::getY() const {
        return m_bounds.getBottomLeftCornerY() ;
    }

    int GUIElement::getWidth() const {
        return m_bounds.getWidth() ;
    }

    int GUIElement::getHeight() const {
        return m_bounds.getHeight() ;
    }


    const GUIElement* GUIElement::getParent() {
        return m_parent ;
    }

    void GUIElement::setParent(GUIElement* parent) {
        m_parent = parent ;
    }

} ;
