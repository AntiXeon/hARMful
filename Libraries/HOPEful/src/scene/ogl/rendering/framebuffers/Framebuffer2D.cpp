#include <scene/ogl/rendering/framebuffers/Framebuffer2D.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope::GL ;

Framebuffer2D::Framebuffer2D()
    : Framebuffer() {
    m_colorAttachments.resize(GetColorAttachmentCount()) ;
}

Framebuffer2D::Framebuffer2D(const Mind::Dimension2Di& size)
    : Framebuffer(),
      m_size(size) {
    m_colorAttachments.resize(GetColorAttachmentCount()) ;
}

void Framebuffer2D::resize(const Mind::Dimension2Di& newSize) {
    if (m_size == newSize) {
        return ;
    }

    m_size = newSize ;

    const size_t MaxColorAttachments = m_colorAttachments.size() ;
    for (size_t colorIndex = 0; colorIndex < MaxColorAttachments; ++colorIndex) {
        if (m_colorAttachments[colorIndex]) {
            m_colorAttachments[colorIndex] -> resize(m_size) ;
        }
    }

    if (m_depthAttachment) {
        m_depthAttachment -> resize(m_size) ;
    }

    if (m_stencilAttachment) {
        m_stencilAttachment -> resize(m_size) ;
    }

    if (m_depthStencilAttachment) {
        m_depthStencilAttachment -> resize(m_size) ;
    }
}

void Framebuffer2D::attachColor(
    const unsigned char attachmentIndex,
    const InternalFormat internalFormat,
    const PixelFormat pixelDataFormat,
    const PixelDataType pixelDataType
) {
    if (!m_colorAttachments[attachmentIndex]) {
        // Generate the texture.
        m_colorAttachments[attachmentIndex] = std::make_unique<TextureImage2D>(
            m_size,
            internalFormat,
            pixelDataFormat,
            pixelDataType,
            nullptr,
            Framebuffer::GenerateMipmaps
        ) ;

        // Set the filtering modes.
        m_colorAttachments[attachmentIndex] -> bind() ;
        m_colorAttachments[attachmentIndex] -> setFiltering(GL_LINEAR, GL_LINEAR) ;
        m_colorAttachments[attachmentIndex] -> unbind() ;
    }

    // Attach the texture to the framebuffer.
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0 + attachmentIndex,
        GL_TEXTURE_2D,
        m_colorAttachments[attachmentIndex] -> id(),
        Framebuffer::MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer2D::attachDepth() {
    if (!m_depthAttachment) {
        // Generate the texture.
        m_depthAttachment = std::make_unique<TextureImage2D>(
            m_size,
            InternalFormat::DepthComponent,
            PixelFormat::DepthComponent,
            PixelDataType::UnsignedByte,
            nullptr,
            Framebuffer::GenerateMipmaps
        ) ;
    }

    // Set the filtering modes.
    m_depthAttachment -> bind() ;
    m_depthAttachment -> setFiltering(GL_NEAREST, GL_NEAREST) ;
    m_depthAttachment -> unbind() ;

    // Attach the texture to the framebuffer.
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        m_depthAttachment -> id(),
        Framebuffer::MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer2D::attachStencil() {
    if (!m_stencilAttachment) {
        // Generate the texture.
        m_stencilAttachment = std::make_unique<TextureImage2D>(
            m_size,
            InternalFormat::StencilIndex,
            PixelFormat::StencilIndex,
            PixelDataType::UnsignedByte,
            nullptr,
            Framebuffer::GenerateMipmaps
        ) ;
    }

    // Set the filtering modes.
    m_stencilAttachment -> bind() ;
    m_stencilAttachment -> setFiltering(GL_NEAREST, GL_NEAREST) ;
    m_stencilAttachment -> unbind() ;

    // Attach the texture to the framebuffer.
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        m_stencilAttachment -> id(),
        Framebuffer::MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer2D::attachDepthStencil() {
    if (!m_depthStencilAttachment) {
        // Generate the texture.
        m_depthStencilAttachment = std::make_unique<TextureImage2D>(
            m_size,
            InternalFormat::Depth24Stencil8,
            PixelFormat::DepthStencil,
            PixelDataType::UnsignedInt248,
            nullptr,
            Framebuffer::GenerateMipmaps
        ) ;
    }

    // Set the filtering modes.
    m_depthStencilAttachment -> bind() ;
    m_depthStencilAttachment -> setFiltering(GL_NEAREST, GL_NEAREST) ;
    m_depthStencilAttachment -> unbind() ;

    // Attach the texture to the framebuffer.
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        m_depthStencilAttachment -> id(),
        Framebuffer::MipmapLevel
    ) ;
    unbind() ;
}
