#ifndef __GUILE_VERTICAL_LIST_LAYOUT__
#define __GUILE_VERTICAL_LIST_LAYOUT__


#include <layouts/GUIListLayout.h>


namespace Guile {

    /**
    * @brief   GUIHorizontalListLayout simply displays GUIElements vertically,
    *          from top to bottom.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/13
    */
    class GUIVerticalListLayout : public GUIListLayout {
        public:
            /** @brief  Create a GUIHorizontalListLayout. */
            GUIVerticalListLayout(GUIPanel* panel) ;

            /** @brief  Destruction of the GUIHorizontalListLayout. */
            virtual ~GUIVerticalListLayout() ;


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
