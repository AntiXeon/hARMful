#include <scene/ogl/rendering/capabilities/ClipPlane.hpp>

using namespace Hope::GL ;

void ClipPlane::setPlaneIndex(const uint8_t index) {
    if (index > 7) {
        m_index = GL_CLIP_PLANE0 + 7 ;
    }
    else {
        m_index = GL_CLIP_PLANE0 + m_index ;
    }
}

void ClipPlane::setDistance(const float distance) {
    m_equation[3] = -distance ;
}

void ClipPlane::setNormal(const Mind::Vector3f& normal) {
    m_equation[0] = normal.get(Mind::Vector3f::X) ;
    m_equation[1] = normal.get(Mind::Vector3f::Y) ;
    m_equation[2] = normal.get(Mind::Vector3f::Z) ;
}

void ClipPlane::setNormal(const float x, const float y, const float z) {
    m_equation[0] = x ;
    m_equation[1] = y ;
    m_equation[2] = z ;
}

void ClipPlane::apply() {
    enable(m_index) ;
    glGetClipPlane(m_index, m_oldEquation) ;
    glClipPlane(m_index, m_equation) ;
}

void ClipPlane::remove() {
    if (m_equation != m_oldEquation) {
        glClipPlane(m_index, m_oldEquation) ;
    }
    
    disable(m_index) ;
}
