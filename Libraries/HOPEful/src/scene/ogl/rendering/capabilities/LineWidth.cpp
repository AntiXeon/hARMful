#include <scene/ogl/rendering/capabilities/LineWidth.hpp>

using namespace Hope::GL ;

void LineWidth::apply() {
    if (m_isAntialiased) {
        enable(GL_LINE_SMOOTH) ;
    }

    glGetFloatv(GL_LINE_WIDTH, &m_oldWidth) ;
    glLineWidth(m_width) ;
}

void LineWidth::remove() {
    if (m_isAntialiased) {
        if (m_width != m_oldWidth) {
            glLineWidth(m_oldWidth) ;
        }

        disable(GL_LINE_SMOOTH) ;
    }
}
