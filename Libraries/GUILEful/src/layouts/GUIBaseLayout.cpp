#include <layouts/GUIBaseLayout.h>
#include <elements/GUIElement.h>
#include <elements/GUIPanel.h>


namespace Guile {

    GUIBaseLayout::GUIBaseLayout(GUIPanel* parent) : m_parent(parent) {}

    GUIBaseLayout::~GUIBaseLayout() {}


    void GUIBaseLayout::update() {}


    void GUIBaseLayout::setMargin(const Mind::Dimension2Di& margin) {
        m_margin = margin ;
    }

    void GUIBaseLayout::setMargin(int x, int y) {
        m_margin.set(x, y) ;
    }

} ;