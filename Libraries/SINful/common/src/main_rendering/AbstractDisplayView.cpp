#include <main_rendering/AbstractDisplayView.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AbstractDisplayView::AbstractDisplayView(
                                             AbstractApplicationContext* context,
                                             Camera* camera
                                            )
        : m_context(context), m_camera(camera) {}

    AbstractDisplayView::~AbstractDisplayView() {}

                                                             /*** UTILITIES ***/
    void AbstractDisplayView::update() {
        unsigned int AmountPlanes = m_parallax.size() ;
        for (unsigned int planeIndex = 0 ; planeIndex < AmountPlanes ; ++planeIndex) {
            m_parallax[planeIndex].update() ;
        }
    }

    void AbstractDisplayView::render() {
        unsigned int AmountPlanes = m_parallax.size() ;
        for (unsigned int planeIndex = 0 ; planeIndex < AmountPlanes ; ++planeIndex) {
            m_parallax[planeIndex].render() ;
        }
    }

    void AbstractDisplayView::addParallaxPlane(const ParallaxPlane& plane) {
        m_parallax.push_back(plane) ;
    }

                                                     /*** SETTERS / GETTERS ***/
    void AbstractDisplayView::setCamera(Camera* camera) {
        m_camera = camera ;
    }

    Camera* AbstractDisplayView::getCamera() const {
        return m_camera ;
    }

} ;
