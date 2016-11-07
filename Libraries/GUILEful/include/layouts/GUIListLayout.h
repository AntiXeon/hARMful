#ifndef __GUILE_LIST_LAYOUT__
#define __GUILE_LIST_LAYOUT__


#include <layouts/GUIBaseLayout.h>


namespace Guile {

    /**
    * @brief   GUIListLayout is an abstract layout that manages GUIElements as a
    *          list. It provides common elements to render a such list.
    * @author  CB (c) 2014
    * @version 0.1     2014/08/02
    */
    class GUIListLayout : public GUIBaseLayout {
        protected:
            /** @brief  Position of the next element on axis of the list. */
            int m_currentPositionOnAxis ;

        public:
            /** @brief  Create a GUIListLayout. */
            GUIListLayout(GUIPanel* panel) ;

            /** @brief  Destruction of the GUIListLayout. */
            virtual ~GUIListLayout() ;


            /** @brief   Update some layout informations. */
            void update() ;
    } ;

} ;

#endif
