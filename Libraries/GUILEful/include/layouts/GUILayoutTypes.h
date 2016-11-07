#ifndef __GUILE_LAYOUT_TYPES__
#define __GUILE_LAYOUT_TYPES__


namespace Guile {

    /** @brief  GUI Layouts available types. */
    typedef enum GUILayoutType {
        Layout_VerticalList,    // Vertical list of elements (single column style).
        Layout_HorizontalList,  // Horizontal list of elements (multi-rows style).
        Layout_Grid             // Matrix style
    } GUILayoutType ;

} ;

#endif
