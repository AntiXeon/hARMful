#ifndef __SIN_SDL2_WINDOW__
#define __SIN_SDL2_WINDOW__


#include <SDL2/SDL.h>
#include <scene_objects/BaseEntitiesManager.h>
#include <scene_objects/EntityInstanceFactory.h>
#include <main_rendering/AbstractWindow.h>

#include "Viewport.h"


namespace Sin {

    /**
     * @brief   Class for creation of a window containing graphical
     *          content (2D and/or 3D) using the SDL2 library.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/27
     */
    class Window : public AbstractWindow {
        private:
            /**
             * @brief   Inner window data from SDL2.
             */
            SDL_Window* m_window ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of a new Window.
             * @param   title           Title of the Window.
             * @param   width           Width of the Window.
             * @param   height          Height of the Window.
             * @param   entitiesManager Manager of IEntity objects that is used
             *                          in the whole application.
             * @param   instanceFactory Factory to create new instances from the
             *                          entities.
             */
            Window(
                   const char* title,
                   const unsigned int& width,
                   const unsigned int& height,
                   BaseEntitiesManager* entitiesManager,
                   EntityInstanceFactory* instanceFactory
                  ) ;

            /**
             * @brief   Destruction of the Window.
             */
            virtual ~Window() ;


                                                             /*** UTILITIES ***/
        private:
            /**
             * @brief   Perform some stuff before refreshing the Window.
             */
            void preRefresh() ;

            /**
             * @brief   Perform some stuff after refreshing the Window.
             */
            void postRefresh() ;


            /**
             * @brief   Create the window itself.
             * @param   title           Title of the Window.
             */
            void createWindow(
                              const char* title,
                              const unsigned int& width,
                              const unsigned int& height
                             ) ;

            /**
             * @brief   Create the viewport of the window.
             * @param   entitiesManager Manager of IEntity objects that is used
             *                          in the whole application.
             * @param   instanceFactory Factory to create new instances from the
             *                          entities.
             * @return  The created viewport.
             */
            Viewport* createViewport(
                                     BaseEntitiesManager* entitiesManager,
                                     EntityInstanceFactory* instanceFactory
                                    ) ;


                                                     /*** SETTERS / GETTERS ***/
        public:
            /**
             * @brief   Get the width of the window.
             * @return  The width of the window in pixels.
             */
            unsigned int getWidth() ;

            /**
             * @brief   Get the height of the window.
             * @return  The height of the window in pixels.
             */
            unsigned int getHeight() ;

    } ;

} ;


#endif
