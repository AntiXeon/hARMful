#include <layouts/GUIVerticalListLayout.h>
#include <elements/GUIElement.h>
#include <elements/GUIPanel.h>


namespace Guile {

    GUIVerticalListLayout::GUIVerticalListLayout(GUIPanel* panel) : GUIListLayout(panel) {}

    GUIVerticalListLayout::~GUIVerticalListLayout() {}


    void GUIVerticalListLayout::drawElement(
                                            GUIElement* element,
                                            size_t
                                        ) {
        int xOffset = m_margin.getWidth() + (m_parent -> getX()) ;
        int yOffset = m_currentPositionOnAxis + m_margin.getHeight() ;

        element -> draw(xOffset, yOffset + (m_parent -> getY())) ;

        // Go to the next element position
        m_currentPositionOnAxis = yOffset + element -> getHeight() ;
    }

} ;