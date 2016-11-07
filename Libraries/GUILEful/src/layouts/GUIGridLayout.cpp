#include <layouts/GUIGridLayout.h>
#include <elements/GUIElement.h>
#include <elements/GUIPanel.h>


namespace Guile {

    GUIGridLayout::GUIGridLayout(GUIPanel* panel) : GUIBaseLayout(panel) {
        setSize(1, 1) ;
    }

    GUIGridLayout::GUIGridLayout(
                                GUIPanel* panel,
                                unsigned char width,
                                unsigned char height
                                ) : GUIBaseLayout(panel) {
        setSize(width, height) ;
    }

    GUIGridLayout::~GUIGridLayout() {}



    void GUIGridLayout::drawElement(
                                    GUIElement* element,
                                    size_t index
                                ) {
        if (index < m_maxElementIndex) {
            // Compute the position in the grid according to the parent GUIPanel
            // position and the margin within the layout.
            unsigned int xOffset = ((index % m_width) * m_unitSize.getWidth())
                                        + (m_margin.getWidth())
                                        + (m_parent -> getX()) ;

            unsigned int yOffset = ((index / m_width) * m_unitSize.getHeight())
                                        + (m_margin.getHeight())
                                        + (m_parent -> getY()) ;

            element -> draw(xOffset, yOffset) ;
        }
    }

    void GUIGridLayout::update() {
        m_parent -> getDimensionOfLargestElements(m_unitSize) ;
    }

    void GUIGridLayout::setSize(unsigned char width, unsigned char height) {
        m_width = width ;
        m_height = height ;
        m_maxElementIndex = width * height ;
    }

} ;