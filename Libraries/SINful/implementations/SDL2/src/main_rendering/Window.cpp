#include <stdlib.h>
#include <debug/Test.h>
#include <ApplicationContext.h>
#include <main_rendering/Window.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
        Window::Window(
                       const char* title,
                       const unsigned int& width,
                       const unsigned int& height,
                       BaseEntitiesManager* entitiesManager,
                       EntityInstanceFactory* instanceFactory
                      ) : AbstractWindow() {
            SDL_Init(SDL_INIT_VIDEO) ;
	        atexit(SDL_Quit) ;

            createWindow(title, width, height) ;
            Viewport* viewport = createViewport(entitiesManager, instanceFactory) ;
            setViewport(viewport) ;
        }

        Window::~Window() {
            if (m_window != NULL) {
                SDL_DestroyWindow(m_window) ;
            }
        }


                                                             /*** UTILITIES ***/
        void Window::preRefresh() {}

        void Window::postRefresh() {}


        void Window::createWindow(
                                  const char* title,
                                  const unsigned int& width,
                                  const unsigned int& height
                                 ) {
            m_window = SDL_CreateWindow(
                                        title,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        width,
                                        height,
                                        SDL_WINDOW_HIDDEN
                                       ) ;
            // Check if the window is created.
            ABORT_CONDITION((m_window != NULL), SDL_GetError()) ;
        }

        Viewport* Window::createViewport(
                                         BaseEntitiesManager* entitiesManager,
                                         EntityInstanceFactory* instanceFactory
                                        ) {
            // Create the SDL renderer.
            // It is destroyed by the viewport.
            SDL_Renderer* renderer = SDL_CreateRenderer(
                                                        m_window,
                                                        -1,
                                                        SDL_RENDERER_ACCELERATED
                                                       ) ;
            // Check if the renderer is created.
            ABORT_CONDITION((renderer != NULL), SDL_GetError()) ;

            // Create the app context.
            // It is destroyed by the viewport.
            ApplicationContext* context = new ApplicationContext(
                                                                 entitiesManager,
                                                                 instanceFactory,
                                                                 renderer
                                                                ) ;
            // Create the view manager.
            // It is destroyed by the viewport.
            DisplayViewManager* viewManager = new DisplayViewManager(context) ;

            // From each of these objects, a Viewport can be created.
            return new Viewport(renderer, context, viewManager) ;
        }

                                                     /*** SETTERS / GETTERS ***/
        unsigned int Window::getWidth() {
            int width ;
            SDL_GetWindowSize(m_window, &width, NULL) ;
            return width ;
        }

        unsigned int Window::getHeight() {
            int height ;
            SDL_GetWindowSize(m_window, NULL, &height) ;
            return height ;
        }

} ;
