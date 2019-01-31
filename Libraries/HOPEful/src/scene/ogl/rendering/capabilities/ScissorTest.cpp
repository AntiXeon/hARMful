#include <scene/ogl/rendering/capabilities/ScissorTest.hpp>

using namespace Hope::GL ;

void ScissorTest::apply() {
    enable(GL_SCISSOR_TEST) ;

    GLint values[4] ;
    glGetIntegerv(GL_SCISSOR_BOX, values) ;
    m_oldRectangle.x = values[0] ;
    m_oldRectangle.y = values[1] ;
    m_oldRectangle.width = values[2] ;
    m_oldRectangle.height = values[3] ;

    if (m_rectangle != m_oldRectangle) {
        glScissor(
            m_rectangle.x,
            m_rectangle.y,
            m_rectangle.width,
            m_rectangle.height
        ) ;
    }
}

void ScissorTest::remove() {
    if (m_rectangle != m_oldRectangle) {
        glScissor(
            m_oldRectangle.x,
            m_oldRectangle.y,
            m_oldRectangle.width,
            m_oldRectangle.height
        ) ;
    }

    disable(GL_SCISSOR_TEST) ;
}
