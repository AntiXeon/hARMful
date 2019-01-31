#include <scene/ogl/rendering/capabilities/DepthTest.hpp>

using namespace Hope::GL ;

void DepthTest::apply() {
    enable(GL_DEPTH_TEST) ;
    glGetIntegerv(GL_DEPTH_FUNC, reinterpret_cast<GLint*>(&m_oldFunction)) ;

    if (m_function != m_oldFunction) {
        glDepthFunc(m_function) ;
    }
}

void DepthTest::remove() {
    if (m_function != m_oldFunction) {
        glDepthFunc(m_oldFunction) ;
    }

    disable(GL_DEPTH_TEST) ;
}
