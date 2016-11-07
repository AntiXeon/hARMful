#include <layouts/GUIListLayout.h>
#include <elements/GUIElement.h>
#include <elements/GUIPanel.h>


namespace Guile {

    GUIListLayout::GUIListLayout(GUIPanel* panel) : GUIBaseLayout(panel) {}

    GUIListLayout::~GUIListLayout() {}


    void GUIListLayout::update() {
        m_currentPositionOnAxis = 0 ;
    }

} ;