#include <scene/ogl/rendering/capabilities/FaceCulling.hpp>

using namespace Hope::GL ;

void FaceCulling::apply() {
    if (m_mode == CullMode::None) {
        m_wasEnabled = glIsEnabled(GL_CULL_FACE) ;
        if (m_wasEnabled) {
            glDisable(GL_CULL_FACE) ;
        }
    }
    else {
        enable(GL_CULL_FACE) ;
        glCullFace(m_mode) ;
    }
}

void FaceCulling::remove() {
    if (m_mode == CullMode::None) {
        if (m_wasEnabled) {
            glEnable(GL_CULL_FACE) ;
        }
    }
    else {
        disable(GL_CULL_FACE) ;
    }
}
