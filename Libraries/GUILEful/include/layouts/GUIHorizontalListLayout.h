#ifndef __GUILE_HORIZONTAL_LIST_LAYOUT__
#define __GUILE_HORIZONTAL_LIST_LAYOUT__


#include <layouts/GUIListLayout.h>


namespace Guile {

    /**
    * @brief   GUIHorizontalListLayout simply displays GUIElements side by side,
    *          from left to right.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/13
    */
    class GUIHorizontalListLayout : public GUIListLayout {
        public:
            /** @brief  Create a GUIHorizontalListLayout. */
            GUIHorizontalListLayout(GUIPanel* panel) ;

            /** @brief  Destruction of the GUIHorizontalListLayout. */
            virtual ~GUIHorizontalListLayout() ;


            /**
            * @brief   Draw a GUIElement thanks to its index that determines its
            *          position in the layer.
            * @param   element Element to be drawn.
            * @param   index   Index of the element to be drawn in the panel.
            */
            void drawElement(
                            GUIElement* element,
                            size_t index
                            ) ;
    } ;

} ;

#endif
