#ifndef __GUILE_GRID_LAYOUT__
#define __GUILE_GRID_LAYOUT__


#include <layouts/GUIBaseLayout.h>
#include <geometry/dimensions/Dimension2Di.h>


namespace Guile {

    /**
    * @brief   GUIGridLayout is a way to display GUIElements in a grid of
    *          defined size.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/13
    */
    class GUIGridLayout : public GUIBaseLayout {
        protected:
            /** @brief  Dimensions of a unit square in the GUIGridLayout. */
            Mind::Dimension2Di m_unitSize ;

            /** @brief  Width of the GUIGridLayout in GUIElements. */
            unsigned char m_width ;

            /** @brief  Height of the GUIGridLayout in GUIElements. */
            unsigned char m_height ;

        private:
            /** @brief  Cache of the maximal index an element can have. */
            unsigned short m_maxElementIndex ;


        public:
            /**
            * @brief   Create a GUIGridLayout.
            * @param   panel   Parent panel.
            */
            GUIGridLayout(GUIPanel* panel) ;

            /**
            * @brief   Create a GUIGridLayout.
            * @param   panel   Parent panel.
            * @param   width   Width of the GUIGridLayout in GUIElements.
            * @param   height  Height of the GUIGridLayout in GUIElements.
            */
            GUIGridLayout(
                        GUIPanel* panel,
                        unsigned char width,
                        unsigned char height
                        ) ;

            /** @brief  Destruction of the GUIGridLayout. */
            virtual ~GUIGridLayout() ;


            /**
            * @brief   Draw a GUIElement thanks to its index that determines its
            *          position in the layer.
            * @param   element Element to be drawn.
            * @param   index   Index of the element to be drawn in the panel.
            */
            virtual void drawElement(
                                    GUIElement* element,
                                    size_t index
                                    ) ;

            /** @brief   Update some layout informations. */
            void update() ;


            /**
            * @brief   Set the size of the grid.
            * @param   width   Width of the GUIGridLayout in GUIElements.
            * @param   height  Height of the GUIGridLayout in GUIElements.
            */
            void setSize(unsigned char width, unsigned char height) ;
    } ;

} ;

#endif
