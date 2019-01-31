#include <scene/ogl/rendering/capabilities/PointSize.hpp>

using namespace Hope::GL ;

void PointSize::apply() {
    if (m_current.isProgrammable) {
        enable(GL_PROGRAM_POINT_SIZE) ;
    }

    glGetFloatv(GL_POINT_SIZE, &(m_old.size)) ;

    if (m_current.size != m_old.size) {
        glPointSize(m_current.size) ;
    }
}

void PointSize::remove() {
    if (m_current.size != m_old.size) {
        glPointSize(m_old.size) ;
    }

    disable(GL_PROGRAM_POINT_SIZE) ;
}
