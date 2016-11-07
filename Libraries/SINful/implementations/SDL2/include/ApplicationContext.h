#ifndef __SIN_APPLICATION_CONTEXT__
#define __SIN_APPLICATION_CONTEXT__


#include <SDL2/SDL.h>
#include <AbstractApplicationContext.h>
#include <scene_objects/BaseEntitiesManager.h>
#include <scene_objects/EntityInstanceFactory.h>


namespace Sin {

    /**
     * @brief   Context to share data between different layers of the
     *          2D engine API.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/07
     */
    class ApplicationContext : public AbstractApplicationContext {
        private:
            /**
             * @brief   Renderer used to render the Window content and display
             *          it, or save it on disk.
             */
            SDL_Renderer* m_renderer ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new ApplicationContext.
             * @param   entitiesManager Manager of the resources for the
             *                          entities of the application.
             * @param   factory         Factory to generate instances of
             *                          entities.
             * @param   renderer        Renderer used to render the Window
             *                          content and display it, or save it on
             *                          disk.
             */
            ApplicationContext(
                               BaseEntitiesManager* entitiesManager,
                               EntityInstanceFactory* factory,
                               SDL_Renderer* renderer
                              ) ;

            /**
             * @brief   Destruction of the ApplicationContext.
             */
            virtual ~ApplicationContext() ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the renderer of the Window.
             * @return  The renderer used to display scene on screen or save a
             *          screenshot.
             */
            SDL_Renderer* getRenderer() const ;
    } ;

} ;

 #endif
