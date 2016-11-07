#include <main_rendering/ParallaxPlane.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ParallaxPlane::ParallaxPlane(const Mind::Scalar& scrollSpeed)
        : m_scrollSpeed(scrollSpeed) {}

    ParallaxPlane::~ParallaxPlane() {}


                                                             /*** UTILITIES ***/
    void ParallaxPlane::update() {
        m_root.update() ;
    }

    void ParallaxPlane::render() {
        m_root.render() ;
    }


                                                     /*** SETTERS / GETTERS ***/
    void ParallaxPlane::setScrollSpeed(const Mind::Scalar& scrollSpeed) {
        m_scrollSpeed = scrollSpeed ;
    }

} ;
