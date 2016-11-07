#include <layouts/GUIHorizontalListLayout.h>
#include <elements/GUIElement.h>
#include <elements/GUIPanel.h>


namespace Guile {

    GUIHorizontalListLayout::GUIHorizontalListLayout(GUIPanel* panel) : GUIListLayout(panel) {}

    GUIHorizontalListLayout::~GUIHorizontalListLayout() {}


    void GUIHorizontalListLayout::drawElement(
                                            GUIElement* element,
                                            size_t
                                            ) {
        int xOffset = m_currentPositionOnAxis + m_margin.getWidth() ;
        int yOffset = m_margin.getHeight() + (m_parent -> getY()) ;

        element -> draw(xOffset + (m_parent -> getX()), yOffset) ;

        // Go to the next element position.
        m_currentPositionOnAxis = xOffset + element -> getWidth() ;
    }

} ;
