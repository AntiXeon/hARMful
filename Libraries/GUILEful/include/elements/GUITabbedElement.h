#ifndef __GUILE_TABBED_ELEMENT__
#define __GUILE_TABBED_ELEMENT__


#include <elements/GUIElement.h>
#include <elements/GUIPanel.h>
#include <string>
#include <vector>


namespace Guile {

   /**
    * @brief   A GUITabbedElement contains one or several GUIPanel, each being in a
    *          tab. Only the content on the active tab can be drawn, the others are
    *          hidden until the active tab is changed.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/31
    */
    class GUITabbedElement : public GUIElement {
        protected:
            /** @brief  Default tab name if name is not found. */
            static const std::string DEFAULT_TAB_NAME ;


            /** @brief  Index of the active tab. */
            size_t m_activeTab ;

            /** @brief  Name of the tabs. */
            std::vector<std::string> m_tabsNames ;

            /** @brief  List of the GUIPanels used in the tabs. */
            std::vector<GUIPanel*> m_panels ;


        public:
            /** @brief  Create an empty GUITabbedElement. */
            GUITabbedElement() ;

            /**
            * @brief   Destruction of the GUITabbedElement.
            * @warning This destructor does not delete the registered GUIPanels.
            */
            virtual ~GUITabbedElement() ;



            /**
            * @brief   Add a new tab with a name. A GUIPanel is created too.
            * @param   name    Name of the new tab.
            * @param   panel   Panel that is contained in the tab.
            * @return  The panel given as parameter for convenient use.
            * @warning The panel cannot be NULL pointer.
            */
            GUIPanel* addTab(const std::string& name, GUIPanel* panel) ;

            /**
            * @brief   Remove the tab at the given index.
            * @param   index   Index of the tab to remove in the GUITabbedElement.
            * @return  The found GUIPanel to be destroyed or reused.
            *          NULL is returned if index is out of bounds.
            */
            GUIPanel* removeTab(size_t index) ;


            /**
            * @brief   Return the amount of tabs available in the current
            *          GUITabbedElement.
            * @return  Amount of tabs in the GUITabbedElement.
            */
            size_t countTabs() const ;


            /**
            * @brief   Set the active tab.
            * @param   index   Index of the tab to make active. If out of bound,
            *                  the first tab will be the active one.
            */
            void setActiveTab(size_t index) ;



            /** @brief  Draw the element on screen. */
            void draw() ;



            /**
            * @brief   Get the name of the tab at the given index.
            * @param   index   Index of the wanted tab.
            * @return  Name of the wanted tab if found, empty string if the index
            *          is out of bounds.
            */
            const std::string& getName(size_t index) ;

            /**
            * @brief   Get the panel of the tab at the given index.
            * @param   index   Index of the wanted tab.
            * @return  Panel of the wanted tab if found, NULL if the index is out
            *          of bounds.
            */
            GUIPanel* getPanel(size_t index) ;


        protected:
            /** @brief   Method dedicated to the rendering of the tab. */
            virtual void drawTab() = 0 ;


        private:
            /**
            * @brief   Class invariant.
            * @return  Value of the class invariant.
            *          TRUE if the class is consistent, FALSE if it is not.
            */
            bool invariant() const ;
    } ;

} ;

#endif
