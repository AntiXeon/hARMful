#ifndef __GUILE_LABEL__
#define __GUILE_LABEL__


#include <elements/GUIElement.h>
#include <string>


namespace Guile {

    /**
    * @brief   A GUILabel contains a text that is displayed.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/13
    */
    class GUILabel : public GUIElement {
        public:
            /** @brief  Available text alignment on horizontal axis. */
            enum TextAlignment {
                                ALIGN_LEFT,
                                ALIGN_RIGHT,
                                ALIGN_CENTER,
                                ALIGN_JUSTIFY
                            } ;

        private:
            /** @brief  Text of the label. */
            std::string m_text ;


        public:
            /**
            * @brief   Create a GUILabel.
            * @param   text    Text to put in the label.
            */
            GUILabel(const std::string& text = "") ;

            /** @brief  Destruction of the GUILabel. */
            virtual ~GUILabel() ;


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
                                void* data = NULL
                                ) ;



            /**
            * @brief   Get the text of the label.
            * @return  The text of the label.
            */
            const std::string& getText() const ;

            /**
            * @brief   Set the text of the label.
            * @param   text    Text to put in the label.
            */
            void setText(const std::string& text) ;


        private:
            /**
            * @brief   Adjust the given text to the width of the label.
            * @param   text    Text to adjust and put as current label text.
            */
            virtual void adjustText(const std::string& text) ;
    } ;

} ;

#endif
