#ifndef __SIN_SDL2_DISPLAY_VIEW_MANAGER__
#define __SIN_SDL2_DISPLAY_VIEW_MANAGER__


#include <main_rendering/AbstractDisplayViewManager.h>
#include <ApplicationContext.h>
#include <SDL2/SDL.h>

#include "DisplayView.h"


namespace Sin {

    /**
     * @brief   Stack screens to save the previous opened screens, letting
     *          them be in pause without update if they are not active. Only
     *          one screen can be active at a time.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/28
     */
    class DisplayViewManager : public AbstractDisplayViewManager {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of a new DisplayViewManager.
             * @param   context Context of the application.
             */
            DisplayViewManager(ApplicationContext* context) ;

            /**
             * @brief   Destruction of the DisplayViewManager.
             */
            virtual ~DisplayViewManager() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Add a screen from its file path. This loads the
             *          screen configuration and store it in the list of
             *          screens.
             * @param   path    Path to the screen configuration file to
             *                  load.
             * @return  ID of the loaded view, on success. If loading fails,
             *          -1 is then returned.
             */
            unsigned int addView(const std::string& path) ;
    } ;

} ;


#endif
