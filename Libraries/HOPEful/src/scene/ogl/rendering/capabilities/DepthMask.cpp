#include <scene/ogl/rendering/capabilities/DepthMask.hpp>

using namespace Hope::GL ;

void DepthMask::apply() {
    glGetBooleanv(GL_DEPTH_WRITEMASK, &m_oldIsEnabled) ;

    if (m_isEnabled != m_oldIsEnabled) {
        glDepthMask(m_isEnabled) ;
    }
}

void DepthMask::remove() {
    if (m_isEnabled != m_oldIsEnabled) {
        glDepthMask(m_oldIsEnabled) ;
    }
}
