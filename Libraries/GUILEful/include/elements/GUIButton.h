#ifndef __GUILE_BUTTON__
#define __GUILE_BUTTON__


#include <elements/GUILabel.h>
#include <GUITypes.h>


namespace Guile {

    /**
    * @brief   A GUIButton has a text and can be activated by user to perform an
    *          action.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/13
    */
    class GUIButton : public GUILabel {
        protected:
            /** @brief  Action the GUIButton triggers on activation. */
            Action m_mainAction ;


        public:
            /**
            * @brief   Create a GUIButton.
            * @param   text        Text written on the GUIButton.
            * @param   mainAction  Action the button triggers on activation.
            */
            GUIButton(
                    const std::string& text = "",
                    Action mainAction = NULL
                    ) ;

            /** @brief  Destruction of the GUIButton. */
            virtual ~GUIButton() ;


            /**
            * @brief   Trigger an action if the coordinates are in the
            *          boundaries of the GUIElement.
            * @param   x               Position of mouse on X axis.
            * @param   y               Position of mouse on Y axis.
            * @param   keyboardKeys    Keyboard keys that have been pressed
            *                          when the action has been triggered. This
            *                          can be a combination of keys and mask
            *                          keys (CTRL, SHIFT, etc).
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
    } ;

} ;

#endif
