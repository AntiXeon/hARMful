#include <scene/ogl/rendering/capabilities/BlendEquation.hpp>

using namespace Hope::GL ;

void BlendEquation::apply() {
    enable(GL_BLEND) ;
    glGetIntegerv(GL_BLEND_EQUATION_RGB, reinterpret_cast<GLint*>(&m_oldMode)) ;

    if (m_mode != m_oldMode) {
        glBlendEquation(m_mode) ;
    }
}

void BlendEquation::remove() {
    if (m_mode != m_oldMode) {
        glBlendEquation(m_oldMode) ;
    }

    disable(GL_BLEND) ;
}
