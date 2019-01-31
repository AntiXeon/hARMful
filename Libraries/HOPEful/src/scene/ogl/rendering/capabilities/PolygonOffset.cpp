#include <scene/ogl/rendering/capabilities/PolygonOffset.hpp>

using namespace Hope::GL ;

void PolygonOffset::apply() {
    enable(GL_POLYGON_OFFSET_FILL) ;
    glGetFloatv(GL_POLYGON_OFFSET_FACTOR, &(m_old.scaleFactor)) ;
    glGetFloatv(GL_POLYGON_OFFSET_UNITS, &(m_old.depthOffset)) ;

    if (m_current != m_old) {
        glPolygonOffset(m_current.scaleFactor, m_current.depthOffset) ;
    }
}

void PolygonOffset::remove() {
    if (m_current != m_old) {
        glPolygonOffset(m_old.scaleFactor, m_old.depthOffset) ;
    }

    disable(GL_POLYGON_OFFSET_FILL) ;
}
