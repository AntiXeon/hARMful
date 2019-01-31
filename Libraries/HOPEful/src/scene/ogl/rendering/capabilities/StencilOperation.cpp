#include <scene/ogl/rendering/capabilities/StencilOperation.hpp>

using namespace Hope::GL ;

void StencilOperation::apply() {
    enable(GL_STENCIL_TEST) ;

    glGetIntegerv(GL_STENCIL_FAIL, reinterpret_cast<GLint*>(&(m_oldFrontFaces.stencilFail))) ;
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, reinterpret_cast<GLint*>(&(m_oldFrontFaces.depthFail))) ;
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, reinterpret_cast<GLint*>(&(m_oldFrontFaces.success))) ;

    glGetIntegerv(GL_STENCIL_BACK_FAIL, reinterpret_cast<GLint*>(&(m_oldBackFaces.stencilFail))) ;
    glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_FAIL, reinterpret_cast<GLint*>(&(m_oldBackFaces.depthFail))) ;
    glGetIntegerv( GL_STENCIL_BACK_PASS_DEPTH_PASS, reinterpret_cast<GLint*>(&(m_oldBackFaces.success))) ;

    glStencilOpSeparate(
        m_frontFaces.face,
        m_frontFaces.stencilFail,
        m_frontFaces.depthFail,
        m_frontFaces.success
    ) ;

    glStencilOpSeparate(
        m_backFaces.face,
        m_backFaces.stencilFail,
        m_backFaces.depthFail,
        m_backFaces.success
    ) ;
}

void StencilOperation::remove() {
    glStencilOpSeparate(
        m_oldFrontFaces.face,
        m_oldFrontFaces.stencilFail,
        m_oldFrontFaces.depthFail,
        m_oldFrontFaces.success
    ) ;

    glStencilOpSeparate(
        m_oldBackFaces.face,
        m_oldBackFaces.stencilFail,
        m_oldBackFaces.depthFail,
        m_oldBackFaces.success
    ) ;

    disable(GL_STENCIL_TEST) ;
}
