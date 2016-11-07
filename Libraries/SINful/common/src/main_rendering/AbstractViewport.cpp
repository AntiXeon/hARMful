#include <main_rendering/AbstractViewport.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AbstractViewport::AbstractViewport(
                                       AbstractApplicationContext* context,
                                       AbstractDisplayViewManager* viewManager
                                      )
        : m_context(context),
          m_viewManager(viewManager) {}

    AbstractViewport::~AbstractViewport() {
        if (m_context != NULL) {
            delete m_context ;
        }

        if (m_viewManager != NULL) {
            delete m_viewManager ;
        }
    }

                                                             /*** UTILITIES ***/
    void AbstractViewport::render() {
        AbstractDisplayView* currentView = m_viewManager -> getCurrentView() ;
        // Update loop.
        currentView -> update() ;
        // Render loop.
        currentView -> render() ;
    }

                                                     /*** SETTERS / GETTERS ***/
    AbstractDisplayViewManager* AbstractViewport::getDisplayViewManager() const {
        return m_viewManager ;
    }

} ;
