#include <scene/ogl/rendering/capabilities/DepthTest.hpp>
#include <iostream>

using namespace Hope::GL ;

void DepthTest::apply() {
    m_depthTestEnabled = glIsEnabled(GL_DEPTH_TEST) ;

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

    if (m_depthTestEnabled == GL_FALSE) {
        disable(GL_DEPTH_TEST) ;
    }
}
