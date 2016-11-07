#ifndef __GUILE_GUI_TYPES__
#define __GUILE_GUI_TYPES__


namespace Guile {

    /**
    * @brief   Action that can be performed by a GUI element.
    *          The first parameter corresponds to the keyboard keys that are
    *          pressed when the action is performed.
    *          The second parameter representes the mouse buttons pressed when
    *          the action is performed.
    *          The third parameter is an extra element that can be used/modified
    *          by the action.
    */
    typedef void (*Action)(
                           int   /*keyboard keys*/,
                           int   /*mouse buttons*/,
                           void* /*extra element*/
                          ) ;

} ;

#endif
