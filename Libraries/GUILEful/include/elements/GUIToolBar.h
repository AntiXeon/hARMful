#ifndef __GUILE_TOOL_BAR__
#define __GUILE_TOOL_BAR__


#include <elements/GUIPanel.h>


namespace Guile {

    /**
    * @brief   A GUIToolBar contains other GUIElements but only as an horizontal
    *          list.
    * @author  CB (c) 2014
    * @version 0.1     2014/07/13
    */
    class GUIToolBar : public GUIPanel {
        public:
            /** @brief  Create a new GUIToolBar. */
            GUIToolBar() ;

            /** @brief  Destruction of the GUIToolBar. */
            ~GUIToolBar() ;


        private:
            /**
            * @brief   Set the GUILayout of the GUIPanel.
            * @param   layoutType  Type of the GUILayout to use in the GUIPanel.
            */
            virtual void setLayout(GUILayoutType layoutType) ;
    } ;

} ;

#endif
