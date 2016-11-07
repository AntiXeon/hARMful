#include <elements/GUITabbedElement.h>
#include <GUILEStrings.h>
#include <debug/Test.h>


namespace Guile {

    const std::string GUITabbedElement::DEFAULT_TAB_NAME = "" ;



    GUITabbedElement::GUITabbedElement() : GUIElement() {}

    GUITabbedElement::~GUITabbedElement() {
        ABORT_CONDITION(
                        invariant(),
                        GUITabbedElementMsg::Error::IsInconsistentOnDestruction
                       ) ;

        size_t maxPanel = m_panels.size() ;
        for (size_t indexPanel = 0 ; indexPanel < maxPanel ; ++indexPanel)
            m_panels[indexPanel] -> setParent(NULL) ;
        m_panels.clear() ;
    }


    GUIPanel* GUITabbedElement::addTab(
                                    const std::string& name,
                                    GUIPanel* panel
                                    ) {
        ABORT_CONDITION(
                        invariant(),
                        GUITabbedElementMsg::Error::IsInconsistentBeforeAddingTab
                       ) ;
        ABORT_CONDITION(
                        (panel != NULL),
                        GUITabbedElementMsg::Error::UndefinedPanel
                       ) ;

        panel -> setParent(this) ;
        m_tabsNames.push_back(name) ;
        m_panels.push_back(panel) ;

        ABORT_CONDITION(
                        invariant(),
                        GUITabbedElementMsg::Error::IsInconsistentAfterAddingTab
                       ) ;

        return m_panels.back() ;
    }

    GUIPanel* GUITabbedElement::removeTab(size_t index) {
        // No invariant needed as already tested by countTabs() method

        GUIPanel* foundPanel = NULL ;
        if (index < countTabs()) {
            foundPanel = m_panels[index] ;
            foundPanel -> setParent(NULL) ;

            m_tabsNames.erase(m_tabsNames.begin() + index) ;
            m_panels.erase(m_panels.begin() + index) ;
        }

        // No invariant needed as already tested by countTabs() method

        // Set the active tab to the previous one if needed...
        if (m_activeTab >= countTabs())
            m_activeTab = countTabs() - 1 ;

        return foundPanel ;
    }

    size_t GUITabbedElement::countTabs() const {
        ABORT_CONDITION(
                        invariant(),
                        GUITabbedElementMsg::Error::IsInconsistent
                       ) ;
        return m_panels.size() ;
    }



    void GUITabbedElement::setActiveTab(size_t index) {
        // No invariant needed as already tested by countTabs() method
        if (index < countTabs())
            m_activeTab = index ;
    }


    void GUITabbedElement::draw() {
        drawTab() ;

        size_t activeTabIndex = (m_activeTab < countTabs()) ? m_activeTab : 0 ;
        m_panels[activeTabIndex] -> draw() ;
    }



    const std::string& GUITabbedElement::getName(size_t index) {
        // No invariant needed as already tested by countTabs() method
        if (index < countTabs())
            return m_tabsNames[index] ;
        return DEFAULT_TAB_NAME ;
    }

    GUIPanel* GUITabbedElement::getPanel(size_t index) {
        // No invariant needed as already tested by countTabs() method
        if (index < countTabs())
            return m_panels[index] ;
        return NULL ;
    }



    bool GUITabbedElement::invariant() const {
        return (m_tabsNames.size() == m_panels.size()) ;
    }

} ;
