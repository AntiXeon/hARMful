#include <scene/ogl/rendering/capabilities/StencilTest.hpp>

using namespace Hope::GL ;

void StencilTest::apply() {
    enable(GL_STENCIL_TEST) ;

    glGetIntegerv(GL_STENCIL_FUNC, reinterpret_cast<GLint*>(&(m_oldFrontFaces.function))) ;
    glGetIntegerv(GL_STENCIL_REF, reinterpret_cast<GLint*>(&(m_oldFrontFaces.reference))) ;
    glGetIntegerv(GL_STENCIL_VALUE_MASK, reinterpret_cast<GLint*>(&(m_oldFrontFaces.mask))) ;

    glGetIntegerv(GL_STENCIL_BACK_FUNC, reinterpret_cast<GLint*>(&(m_oldBackFaces.function))) ;
    glGetIntegerv(GL_STENCIL_BACK_REF, reinterpret_cast<GLint*>(&(m_oldBackFaces.reference))) ;
    glGetIntegerv(GL_STENCIL_BACK_VALUE_MASK, reinterpret_cast<GLint*>(&(m_oldBackFaces.mask))) ;

    glStencilFuncSeparate(
        m_frontFaces.face,
        m_frontFaces.function,
        m_frontFaces.reference,
        m_frontFaces.mask
    ) ;

    glStencilFuncSeparate(
        m_backFaces.face,
        m_backFaces.function,
        m_backFaces.reference,
        m_backFaces.mask
    ) ;
}

void StencilTest::remove() {
    glStencilFuncSeparate(
        m_oldFrontFaces.face,
        m_oldFrontFaces.function,
        m_oldFrontFaces.reference,
        m_oldFrontFaces.mask
    ) ;

    glStencilFuncSeparate(
        m_oldBackFaces.face,
        m_oldBackFaces.function,
        m_oldBackFaces.reference,
        m_oldBackFaces.mask
    ) ;

    disable(GL_STENCIL_TEST) ;
}
