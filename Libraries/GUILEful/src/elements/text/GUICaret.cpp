#include <elements/text/GUICaret.h>


namespace Guile {

    GUICaret::GUICaret() {}

    GUICaret::~GUICaret() {}


    void GUICaret::move(int x, int y) {
        m_bounds.setAt(x, y) ;
    }



    size_t GUICaret::getPositionInText() const {
        return m_positionInText ;
    }

    void GUICaret::setPositionInText(size_t position) {
        m_positionInText = position ;
    }


    void GUICaret::setBlinkRate(unsigned char rate) {
        m_blinkRate = rate ;
    }

    unsigned char GUICaret::getBlinkRate() const {
        return m_blinkRate ;
    }


    void GUICaret::setVisible(bool visible) {
        m_isVisible = visible ;
    }

    bool GUICaret::isVisible() const {
        return m_isVisible ;
    }

} ;