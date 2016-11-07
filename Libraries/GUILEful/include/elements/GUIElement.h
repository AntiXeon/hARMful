#ifndef __GUILE_ELEMENT__
#define __GUILE_ELEMENT__


#include <geometry/rectangles/Rectangle2Di.h>


namespace Guile {

    /**
    * @brief   A GUIElement can be drawn, resized, activated by user with
    *          keyboard and/or mouse.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/13
    */
    class GUIElement {
        protected:
            /** @brief  Parent containing the current GUIElement. */
            GUIElement* m_parent ;

            /** @brief  Bounds of the element. */
            Mind::Rectangle2Di m_bounds ;


        public:
            /** @brief  Create a GUIElement. */
            GUIElement() ;

            /** @brief  Destruction of the GUIElement. */
            virtual ~GUIElement() ;


            /** @brief  Draw the element on screen at its own position. */
            virtual void draw() = 0 ;

            /**
            * @brief   Draw the element on screen at the given position.
            * @param   x       Position where to draw the GUIElement on X axis.
            * @param   y       Position where to draw the GUIElement on Y axis.
            */
            virtual void draw(int x, int y) = 0 ;

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
            */
            virtual bool trigger(
                                int x,
                                int y,
                                int keyboardKeys,
                                int mouseButtons,
                                void* data
                                ) = 0 ;


            /** @brief  Get absolute position of the element on X axis. */
            int getX() const ;

            /** @brief  Get absolute position of the element on Y axis. */
            int getY() const ;

            /** @brief  Get the element width. */
            int getWidth() const ;

            /** @brief  Get the element height. */
            int getHeight() const ;

            /**
            * @brief   Get the parent of the GUIElement.
            * @return  Parent of the GUIElement.
            */
            const GUIElement* getParent() ;

            /**
            * @brief   Set the parent of the GUIElement.
            * @param   parent  Parent of the GUIElement.
            */
            void setParent(GUIElement* parent) ;


        protected:
            /** @brief  Compute size of the GUIElement. */
            virtual void computeSize() = 0 ;
    } ;

} ;


#endif
