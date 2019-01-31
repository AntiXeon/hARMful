#include <scene/ogl/rendering/capabilities/BlendEquationAdvanced.hpp>

using namespace Hope::GL ;

void BlendEquationAdvanced::apply() {
    enable(GL_BLEND) ;

    storeOldSourceParameters() ;
    storeOldDestinationParameters() ;

    for (
        char channel = RGBIndex;
        channel < AmountColorIndices;
        channel++
    ) {
        glBlendFunci(
            m_bufferIndex,
            m_current.source[channel],
            m_current.destination[channel]
        ) ;
    }
}

void BlendEquationAdvanced::remove() {
    for (
        char channel = RGBIndex;
        channel < AmountColorIndices;
        ++channel
    ) {
        glBlendFunci(
            m_bufferIndex,
            m_old.source[channel],
            m_old.destination[channel]
        ) ;
    }

    disable(GL_BLEND) ;
}

void BlendEquationAdvanced::storeOldSourceParameters() {
    GLint srcRGB ;
    GLint srcAlpha ;
    glGetIntegerv(GL_BLEND_SRC_RGB, &srcRGB) ;
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &srcAlpha) ;

    m_old.source[RGBIndex] = static_cast<BlendParameter>(srcRGB) ;
    m_old.source[AlphaIndex] = static_cast<BlendParameter>(srcAlpha) ;
}

void BlendEquationAdvanced::storeOldDestinationParameters() {
    GLint dstRGB ;
    GLint dstAlpha ;
    glGetIntegerv(GL_BLEND_DST_RGB, &dstRGB) ;
    glGetIntegerv(GL_BLEND_DST_ALPHA, &dstAlpha) ;

    m_old.destination[RGBIndex] = static_cast<BlendParameter>(dstRGB) ;
    m_old.destination[AlphaIndex] = static_cast<BlendParameter>(dstAlpha) ;
}
