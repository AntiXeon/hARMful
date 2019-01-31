#include <scene/ogl/rendering/capabilities/ColorMask.hpp>

using namespace Hope::GL ;

void ColorMask::apply() {
    glGetBooleanv(GL_COLOR_WRITEMASK, m_oldChannels) ;

    glColorMask(
        m_channels[Color::Channels::Red],
        m_channels[Color::Channels::Green],
        m_channels[Color::Channels::Blue],
        m_channels[Color::Channels::Alpha]
    ) ;
}

void ColorMask::remove() {
    if (m_channels != m_oldChannels) {
        glColorMask(
            m_oldChannels[Color::Channels::Red],
            m_oldChannels[Color::Channels::Green],
            m_oldChannels[Color::Channels::Blue],
            m_oldChannels[Color::Channels::Alpha]
        ) ;
    }
}
