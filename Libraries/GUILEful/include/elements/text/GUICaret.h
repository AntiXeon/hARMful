#ifndef __GUILE_CARET__
#define __GUILE_CARET__


#include <geometry/points/Point2Di.h>
#include <geometry/rectangles/Rectangle2Di.h>



namespace Guile {

    /**
    * @brief   A GUICaret is used to indicate where the text is typed in text
    *          fields.
    *          It should be entirely managed by the parent GUIElement.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/31
    */
    class GUICaret {
        protected:
            /** @brief  Bounds of the element. */
            Mind::Rectangle2Di m_bounds ;


            /** @brief  Position of the GUICaret in the text. */
            size_t m_positionInText ;

            /** @brief  Blink rate in frame per second. */
            unsigned char m_blinkRate ;

            /** @brief  To know if the GUICaret is visible or hidden. */
            bool m_isVisible ;


        public:
            /**
            * @brief   Create a GUICaret.
            * @param   parent  GUITextElement parent of the GUICaret.
            */
            GUICaret() ;

            /** @brief  Destruction of the GUICaret. */
            virtual ~GUICaret() ;



            /** @brief  Move the caret in its parent GUITextElement. */
            void move(int x, int y) ;



            /** @brief  Draw the GUICaret. */
            virtual void draw() = 0 ;



            /**
            * @brief   Get the position of the GUICaret in the content of its
            *          parent GUITextElement.
            * @return  Position of the GUICaret in the text.
            */
            size_t getPositionInText() const ;

            /**
            * @brief   Get the position of the GUICaret in the content of its
            *          parent GUITextElement.
            * @param   position    Position of the GUICaret in the text.
            */
            void setPositionInText(size_t position) ;


            /**
            * @brief   Set the caret blink rate.
            * @param   rate    Blink rate of the caret in frame per second.
            */
            void setBlinkRate(unsigned char rate) ;

            /**
            * @brief   Get the caret blink rate in frame per second.
            * @return  The blink rate of the caret.
            */
            unsigned char getBlinkRate() const ;


            /**
            * @brief   Show or hide the GUICaret.
            * @param   visible If TRUE the caret is visible, it is hidden if FALSE.
            */
            void setVisible(bool visible) ;

            /**
            * @brief   To know if the GUICaret is visible.
            * @return  TRUE if the caret is visible, FALSE it is hidden.
            */
            bool isVisible() const ;
    } ;

} ;

#endif
