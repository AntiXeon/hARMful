#include <main_rendering/AbstractWindow.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AbstractWindow::AbstractWindow() : m_viewport(NULL) {}

    AbstractWindow::~AbstractWindow() {}

                                                             /*** UTILITIES ***/
    void AbstractWindow::refresh() {
        preRefresh() ;
            m_viewport -> render() ;
            m_viewport -> display() ;
        postRefresh() ;
    }

    void AbstractWindow::saveScreenshot(const std::string& path) {
        m_viewport -> save(path) ;
    }

                                                     /*** SETTERS / GETTERS ***/
    void AbstractWindow::setViewport(const AbstractViewport* viewport) {
        m_viewport = (AbstractViewport*) viewport ;
        m_viewport -> clear() ;
    }

    AbstractViewport* AbstractWindow::getViewport() const {
        return m_viewport ;
    }

} ;
