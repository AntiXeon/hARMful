#include <scene/ogl/rendering/capabilities/StencilMask.hpp>

using namespace Hope::GL ;

void StencilMask::apply() {
    enable(GL_STENCIL_TEST) ;

    glGetIntegerv(GL_STENCIL_WRITEMASK, reinterpret_cast<GLint*>(&m_old.front)) ;
    glGetIntegerv(GL_STENCIL_BACK_WRITEMASK, reinterpret_cast<GLint*>(&m_old.back)) ;

    if (m_current.front != m_old.front) {
        glStencilMaskSeparate(GL_FRONT, m_current.front) ;
    }

    if (m_current.back != m_old.back) {
        glStencilMaskSeparate(GL_BACK, m_current.back) ;
    }
}

void StencilMask::remove() {
    if (m_current.front != m_old.front) {
        glStencilMaskSeparate(GL_FRONT, m_old.front) ;
    }

    if (m_current.back != m_old.back) {
        glStencilMaskSeparate(GL_BACK, m_old.back) ;
    }

    disable(GL_STENCIL_TEST) ;
}
