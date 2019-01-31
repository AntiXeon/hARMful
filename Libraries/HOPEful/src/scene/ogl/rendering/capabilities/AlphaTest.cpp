#include <scene/ogl/rendering/capabilities/AlphaTest.hpp>

using namespace Hope::GL ;

void AlphaTest::apply() {
    enable(GL_ALPHA_TEST) ;
    glGetIntegerv(GL_ALPHA_TEST_FUNC, reinterpret_cast<GLint*>(&m_old.function)) ;
    glGetFloatv(GL_ALPHA_TEST_REF, &m_old.reference) ;

    if (m_current != m_old) {
        glAlphaFunc(m_current.function, m_current.reference) ;
    }
}

void AlphaTest::remove() {
    if (m_current != m_old) {
        glAlphaFunc(m_old.function, m_old.reference) ;
    }

    disable(GL_ALPHA_TEST) ;
}
