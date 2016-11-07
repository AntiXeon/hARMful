#include <elements/GUISeparator.h>


namespace Guile {

    GUISeparator::GUISeparator(int size,
                            Direction direction,
                            bool isAbsolute) : GUIElement(),
                                                m_isAbsolute(isAbsolute),
                                                m_direction(direction) {
        if (direction & DIR_VERTICAL)
            m_bounds.setHeight(size) ;

        if (direction & DIR_HORIZONTAL)
            m_bounds.setWidth(size) ;
    }

    GUISeparator::~GUISeparator() {}



    bool GUISeparator::trigger(int, int, int, int, void*) {
        return false ;
    }

} ;