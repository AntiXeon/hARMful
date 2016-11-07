#ifndef __GUILE_SEPARATOR__
#define __GUILE_SEPARATOR__


#include <elements/GUIElement.h>


namespace Guile {

   /**
    * @brief   A GuiSeparator is used to separate several elements on a GUI.
    *          It can be used to separate on vertical and/or horizontal directions.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/13
    */
    class GUISeparator : public GUIElement {
        public:
            /** @brief  Directions a GUISeparator can have. */
            enum Direction {
                            DIR_VERTICAL        = 1,
                            DIR_HORIZONTAL      = 2,
                            DIR_BOTH            = (DIR_VERTICAL | DIR_HORIZONTAL)
                        } ;

        private:
            /**
            * @brief   To know if the separation is expressed as absolute size if
            *          TRUE. If FALSE, the separation is done relatively to the
            *          size of the parent element.
            */
            bool m_isAbsolute ;

            /** @brief  Direction of the separation (vertical and/or horizontal). */
            Direction m_direction ;


        public:
            /**
            * @brief   Create a GUISeparator.
            * @param   size        Size of the separation.
            * @param   direction   Direction of the separation.
            * @param   isAbsolute  TRUE to have an absolute separation in pixels,
            *                      FALSE to have a relative separation in
            *                      percentage of the parent element size.
            */
            GUISeparator(int size = 10,
                        Direction direction = DIR_HORIZONTAL,
                        bool isAbsolute = true) ;

            /** @brief  Destruction of the GUISeparator. */
            virtual ~GUISeparator() ;



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
            bool trigger(
                        int x,
                        int y,
                        int keyboardKeys,
                        int mouseButtons,
                        void* data = NULL
                        ) ;
    } ;

} ;

#endif
