#ifndef __GUILE_BASE_LAYOUT__
#define __GUILE_BASE_LAYOUT__


#include <geometry/dimensions/Dimension2Di.h>


namespace Guile {

    class GUIElement ;
    class GUIPanel ;


    /**
    * @brief   GUIBaseLayout is an abstract class to provide a common API to all
    *          inherited layout classes.
    *          Layouts are used to define the position of GUIElements in a
    *          GUIPanel on rendering.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/13
    */
    class GUIBaseLayout {
        protected:
            /** @brief  GUIPanel to which the layout is linked. */
            GUIPanel* m_parent ;

            /** @brief  Marge between the elements of the GUIBaseLayout. */
            Mind::Dimension2Di m_margin ;


        public:
            /**
            * @brief   Create a GUIBaseLayout.
            * @param   parent  GUIPanel which uses the layout.
            */
            GUIBaseLayout(GUIPanel* parent) ;

            /** @brief  Destruction of the GUIBaseLayout. */
            virtual ~GUIBaseLayout() ;


            /**
            * @brief   Draw a GUIElement thanks to its index that determines its
            *          position in the layer.
            * @param   element Element to be drawn.
            * @param   index   Index of the element to be drawn in the panel.
            */
            virtual void drawElement(
                                    GUIElement* element,
                                    size_t index
                                    ) = 0 ;

            /** @brief   Update some layout informations. */
            virtual void update() ;


            /**
            * @brief   Set the margin between elements displayed by the layout.
            * @param   margin  Marge on X and Y axes.
            */
            void setMargin(const Mind::Dimension2Di& margin) ;

            /**
            * @brief   Set the margin between elements displayed by the layout.
            * @param   x       Marge on X axis.
            * @param   y       Marge on Y axis.
            */
            void setMargin(int x, int y) ;
    } ;

} ;


#endif
