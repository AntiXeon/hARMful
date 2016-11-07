#include <main_rendering/Viewport.h>
#include <exceptions/NotImplementedException.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    Viewport::Viewport(
                       SDL_Renderer* renderer,
                       ApplicationContext* context,
                       DisplayViewManager* viewManager
                   ) : AbstractViewport(context, viewManager),
                       m_renderer(renderer) {}

    Viewport::~Viewport() {
        if (m_renderer != NULL) {
            SDL_DestroyRenderer(m_renderer) ;
        }
    }


                                                             /*** UTILITIES ***/
    void Viewport::display() {
        SDL_RenderPresent(m_renderer) ;
    }

    void Viewport::save(const std::string&) {

    }

    void Viewport::clear() {
        SDL_RenderClear(m_renderer) ;
    }

} ;
