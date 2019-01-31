#include <scene/ogl/rendering/capabilities/FrontFace.hpp>

using namespace Hope::GL ;

void FrontFace::apply() {
    glGetIntegerv(GL_FRONT_FACE, reinterpret_cast<GLint*>(&m_oldOrientation)) ;

    if (m_orientation != m_oldOrientation) {
        glFrontFace(m_orientation) ;
    }
}

void FrontFace::remove() {
    if (m_orientation != m_oldOrientation) {
        glFrontFace(m_oldOrientation) ;
    }
}
