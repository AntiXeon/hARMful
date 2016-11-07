#ifndef __GUILE_PANEL__
#define __GUILE_PANEL__


#include <elements/GUIElement.h>
#include <layouts/GUILayoutTypes.h>
#include <vector>


namespace Guile {

    class GUIBaseLayout ;

    /**
    * @brief   A GUIPanel contains one or several GUIElements to build the
    *          application GUI.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/13
    */
    class GUIPanel : public GUIElement {
        protected:
            /** @brief  Layout of the GUIPanel. */
            GUIBaseLayout* m_layout ;

            /** @brief  List of the GUIElements inserted in the GUIPanel. */
            std::vector<GUIElement*> m_children ;


        public:
            /**
            * @brief   Create an empty GUIPanel with the wanted layout type.
            * @param   layoutType  Type of GUILayout used in the GUIPanel.
            */
            GUIPanel(GUILayoutType layoutType = Layout_HorizontalList) ;

            /** @brief  Destruction of the GUIPanel. */
            virtual ~GUIPanel() ;


            /**
            * @brief   Add a GUIElement to the GUIPanel.
            * @param   child   GUIElement to add to the GUIPanel.
            * @return  TRUE if the child has been added, FALSE else.
            * @warning The child is not added if already linked to another parent.
            *          Remove the child from its previous parent by calling
            *          removeElement() or removeAll() methods.
            */
            bool addElement(GUIElement* child) ;

            /**
            * @brief   Remove a GUIElement from the GUIPanel.
            * @param   child   GUIElement to remove from the GUIPanel.
            * @return  TRUE if the child has been removed (but not freed),
            *          FALSE else.
            */
            bool removeElement(GUIElement* child) ;

            /**
            * @brief   Remove a GUIElement from the GUIPanel.
            * @param   index   Index of the child in the GUIPanel.
            * @return  TRUE if the child has been removed (but not freed),
            *          FALSE else.
            */
            bool removeElement(size_t index) ;

            /**
            * @brief   Remove all children from the GUIPanel.
            * @warning The memory of dynamically allocated children is not freed
            *          after calling this method. This should be handled by the
            *          application to avoid memory leaks.
            */
            void removeAll() ;



            /** @brief  Draw the element on screen. */
            virtual void draw() ;

            /**
            * @brief   Trigger an action if the coordinates are in the boundaries
            *          of the GUIElement.
            * @param   x               Position of mouse on X axis.
            * @param   y               Position of mouse on Y axis.
            * @param   keyboardKeys    Keyboard keys that have been pressed when
            *                          the action has been triggered. This can be
            *                          a combination of keys and mask keys (CTRL,
            *                          SHIFT, etc).
            * @param   mouseButtons    Mouse buttons that have been pressed when
            *                          the action was triggered.
            * @param   data            Data that can be used by the action.
            * @return  TRUE if the GUIElement has been triggered, FALSE else.
            * @warning The behaviour of the GUIPanel is to activate the first child
            *          listed from the last to the first inserted one.
            */
            virtual bool trigger(
                                int x,
                                int y,
                                int keyboardKeys,
                                int mouseButtons,
                                void* data = NULL
                                ) ;



            /**
            * @brief   Set the GUILayout of the GUIPanel.
            * @param   layoutType  Type of the GUILayout to use in the GUIPanel.
            */
            void setLayout(GUILayoutType layoutType) ;

            /**
            * @brief   Get the GUILayout of the GUIPanel.
            * @param   The GUILayout used by the GUIPanel.
            */
            GUIBaseLayout* getLayout() const ;


            /**
            * @brief   Get the width and height of the largest GUIElements in the
            *          GUIPanel.
            * @return  The size of the largest GUIElements.
            */
            void getDimensionOfLargestElements(Mind::Dimension2Di& size) const ;


        protected:
            /**
            * @brief   Create the GUILayout of the GUIPanel.
            * @param   layoutType  Type of GUILayout used in the GUIPanel.
            */
            void createLayout(GUILayoutType layoutType) ;

            /**
            * @brief   Properly destroy the GUILayout.
            * @param   layoutType  Type of GUILayout used in the GUIPanel.
            */
            void destroyLayout() ;

            /**
            * @brief   Change the layout type.
            * @param   layoutType  New type of GUILayout to use.
            */
            void changeLayout(GUILayoutType layoutType) ;
    } ;

} ;

#endif
