#include <ApplicationContext.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ApplicationContext::ApplicationContext(
                                           BaseEntitiesManager* entitiesManager,
                                           EntityInstanceFactory* factory,
                                           SDL_Renderer* renderer
                                          ) : AbstractApplicationContext(
                                                                         entitiesManager,
                                                                         factory
                                                                        ),
                                              m_renderer(renderer) {}

    ApplicationContext::~ApplicationContext() {}


                                                     /*** SETTERS / GETTERS ***/
    SDL_Renderer* ApplicationContext::getRenderer() const {
        return m_renderer ;
    }

} ;
