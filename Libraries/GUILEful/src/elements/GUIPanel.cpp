#include <elements/GUIPanel.h>
#include <GUILEStrings.h>
#include <GUILayouts.h>
#include <debug/Test.h>


namespace Guile {

    GUIPanel::GUIPanel(GUILayoutType layoutType) : GUIElement() {
        setLayout(layoutType) ;
    }

    GUIPanel::~GUIPanel() {}



    bool GUIPanel::addElement(GUIElement* child) {
        if (child == NULL)
            return false ;

        if ((child -> getParent()) == NULL) {
            child -> setParent(this) ;
            m_children.push_back(child) ;
            m_layout -> update() ;
            return true ;
        }

        return false ;
    }

    bool GUIPanel::removeElement(GUIElement* child) {
        if (child == NULL)
            return false ;

        size_t maxIndex = m_children.size() ;
        for (size_t childIndex = 0 ; childIndex < maxIndex ; ++childIndex) {
            if (child == m_children[childIndex]) {
                child -> setParent(NULL) ;
                m_children.erase(m_children.begin() + childIndex) ;
                m_layout -> update() ;
                return true ;
            }
        }

        return false ;
    }

    bool GUIPanel::removeElement(size_t index) {
        if (index < m_children.size()) {
            m_children[index] -> setParent(NULL) ;
            m_children.erase(m_children.begin() + index) ;
            m_layout -> update() ;
            return true ;
        }

        return false ;
    }

    void GUIPanel::removeAll() {
        size_t maxIndex = m_children.size() ;
        for (size_t childIndex = 0 ; childIndex < maxIndex ; ++childIndex)
            m_children[childIndex] -> setParent(NULL) ;

        m_children.clear() ;
        m_layout -> update() ;
    }



    void GUIPanel::draw() {
        ABORT_CONDITION((m_layout != NULL), GUIPanelMsg::Error::UndefinedLayer) ;

        m_layout -> update() ;

        size_t maxIndex = m_children.size() ;
        for (size_t childIndex = 0 ; childIndex < maxIndex ; ++childIndex)
            m_layout -> drawElement(m_children[childIndex], childIndex) ;
    }

    bool GUIPanel::trigger(
                        int x,
                        int y,
                        int keyboardKeys,
                        int mouseButtons,
                        void* data
                        ) {
        bool childActivated ;

        size_t maxIndex = m_children.size() ;
        for (size_t childIndex = maxIndex ; childIndex > 0 ; --childIndex) {
            childActivated = m_children[childIndex] -> trigger(x, y, keyboardKeys, mouseButtons, data) ;
            if (childActivated)
                return true ;
        }

        return false ;
    }



    void GUIPanel::setLayout(GUILayoutType layoutType) {
        changeLayout(layoutType) ;
        m_layout -> update() ;
    }

    GUIBaseLayout* GUIPanel::getLayout() const {
        return m_layout ;
    }

    void GUIPanel::getDimensionOfLargestElements(Mind::Dimension2Di& size) const {
        int width = 0 ;
        int height = 0 ;

        size_t maxIndex = m_children.size() ;
        for (size_t childIndex = 0 ; childIndex < maxIndex ; ++childIndex) {
            int childWidth = m_children[childIndex] -> getWidth() ;
            int childHeight = m_children[childIndex] -> getHeight() ;

            if (childWidth > width)
                width = childWidth ;

            if (childHeight > height)
                height = childHeight ;
        }

        size.set(width, height) ;
    }


    void GUIPanel::createLayout(GUILayoutType layoutType) {
        switch(layoutType) {
            case Layout_VerticalList:
                m_layout = new GUIVerticalListLayout(this) ;
                break ;

            case Layout_HorizontalList:
                m_layout = new GUIHorizontalListLayout(this) ;
                break ;

            case Layout_Grid:
                m_layout = new GUIGridLayout(this) ;
                break ;
        }

        ABORT_CONDITION((m_layout != NULL), GUIPanelMsg::Error::CreationFailed) ;
    }

    void GUIPanel::destroyLayout() {
        if (m_layout != NULL)
            delete m_layout ;
    }

    void GUIPanel::changeLayout(GUILayoutType layoutType) {
        destroyLayout() ;
        createLayout(layoutType) ;
    }

} ;
