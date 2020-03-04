#include <scene/ogl/rendering/framebuffers/FramebufferBlitter.hpp>

using namespace Hope::GL ;

void FramebufferBlitter::doBlit() {
    // Configure source.
    m_source.fbo -> bind(Framebuffer::ReadOnly) ;
    m_source.fbo -> setReadBuffer(m_source.colorBuffer) ;
    // Configure destination.
    m_destination.fbo -> bind(Framebuffer::WriteOnly) ;
    m_source.fbo -> setDrawBuffers({ m_destination.colorBuffer }) ;

    // Blit.
    glBlitFramebuffer(
        static_cast<int>(m_source.area.upLeftCornerX()),
        static_cast<int>(m_source.area.upLeftCornerY()),
        static_cast<int>(m_source.area.bottomRightCornerX()),
        static_cast<int>(m_source.area.bottomRightCornerY()),
        static_cast<int>(m_destination.area.upLeftCornerX()),
        static_cast<int>(m_destination.area.upLeftCornerY()),
        static_cast<int>(m_destination.area.bottomRightCornerX()),
        static_cast<int>(m_destination.area.bottomRightCornerY()),
        static_cast<int>(m_mask),
        static_cast<int>(m_filter)
    ) ;

    // Unbind source.
    m_source.fbo -> unsetReadBuffer() ;
    m_source.fbo -> unbind(Framebuffer::ReadOnly) ;
    // Unbind destination.
    m_source.fbo -> useNoColorBuffers() ;
    m_destination.fbo -> unbind(Framebuffer::WriteOnly) ;
}
