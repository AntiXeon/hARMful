#ifndef __SIN_SDL2_VIEWPORT__
#define __SIN_SDL2_VIEWPORT__


#include <string>
#include <SDL2/SDL.h>
#include <ApplicationContext.h>
#include <main_rendering/AbstractViewport.h>
#include <main_rendering/DisplayViewManager.h>


namespace Sin {

    /**
     * @brief   A viewport is used to render the content of a window.
     *          This implementation uses the SDL2 graphics library.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/28
     */
    class Viewport : public AbstractViewport {
        private:
            /**
             * @brief   Renderer used to draw elements in the Window.
             */
            SDL_Renderer* m_renderer ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of a Viewport.
             * @param   renderer    The renderer used to draw elements in
             *                      the Window.
             * @param   context     Context of the application.
             * @param   viewManager The view manager used to display the
             *                      different screens of the application.
             */
            Viewport(
                     SDL_Renderer* renderer,
                     ApplicationContext* context,
                     DisplayViewManager* viewManager
                    ) ;

            /**
             * @brief   Destruction of the Viewport.
             */
            virtual ~Viewport() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Display the content of the AbstractViewport.
             */
            void display() ;

            /**
             * @brief   Save a picture of the AbstractViewport on disk.
             * @param   path    Path to the file to save.
             */
            void save(const std::string& path) ;

            /**
             * @brief   Clear the content of the AbstractViewport.
             */
            void clear() ;
    } ;

} ;


#endif
