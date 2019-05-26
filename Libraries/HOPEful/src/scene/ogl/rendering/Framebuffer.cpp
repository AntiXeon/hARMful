#include <scene/ogl/rendering/Framebuffer.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope::GL ;

const bool Framebuffer::GenerateMipmaps = false ;

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &m_fboID) ;
    m_colorAttachments.resize(GetColorAttachmentCount()) ;
}

Framebuffer::Framebuffer(const Mind::Dimension2Di& size)
    : m_size(size) {
    glGenFramebuffers(1, &m_fboID) ;
    m_colorAttachments.resize(GetColorAttachmentCount()) ;
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_fboID) ;
}

void Framebuffer::setDrawBuffers(const std::list<unsigned char> indices) {
    std::vector<unsigned int> attachments ;
    for (unsigned char index: indices) {
        attachments.push_back(GL_COLOR_ATTACHMENT0 + index) ;
    }

    bind() ;
    glDrawBuffers(attachments.size(), attachments.data()) ;
    unbind() ;
}

void Framebuffer::resize(const Mind::Dimension2Di& size) {
    if (m_size == size) {
        return ;
    }

    m_size = size ;

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

void Framebuffer::attachColor(
    const unsigned char attachmentIndex,
    const InternalFormat internalFormat,
    const PixelFormat pixelDataFormat,
    const PixelDataType pixelDataType
) {
    if (!m_colorAttachments[attachmentIndex]) {
        // Generate the texture.
        m_colorAttachments[attachmentIndex] = std::make_unique<Texture2D>(
            m_size,
            internalFormat,
            pixelDataFormat,
            pixelDataType,
            nullptr,
            GenerateMipmaps
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
        MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer::attachDepth() {
    if (!m_depthAttachment) {
        // Generate the texture.
        m_depthAttachment = std::make_unique<Texture2D>(
            m_size,
            InternalFormat::DepthComponent,
            PixelFormat::DepthComponent,
            PixelDataType::UnsignedByte,
            nullptr,
            GenerateMipmaps
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
        MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer::attachStencil() {
    if (!m_stencilAttachment) {
        // Generate the texture.
        m_stencilAttachment = std::make_unique<Texture2D>(
            m_size,
            InternalFormat::StencilIndex,
            PixelFormat::StencilIndex,
            PixelDataType::UnsignedByte,
            nullptr,
            GenerateMipmaps
        ) ;
    }

    // Attach the texture to the framebuffer.
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        m_stencilAttachment -> id(),
        MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer::attachDepthStencil() {
    if (!m_depthStencilAttachment) {
        // Generate the texture.
        m_depthStencilAttachment = std::make_unique<Texture2D>(
            m_size,
            InternalFormat::Depth24Stencil8,
            PixelFormat::DepthStencil,
            PixelDataType::UnsignedInt248,
            nullptr,
            GenerateMipmaps
        ) ;
    }

    // Attach the texture to the framebuffer.
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        m_depthStencilAttachment -> id(),
        MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer::detachColor(const int attachmentIndex) {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboID) ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0 + attachmentIndex,
        GL_TEXTURE_2D,
        0,
        MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer::detachDepth() {
    // Attach the texture to the framebuffer.
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        0,
        MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer::detachStencil() {
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        0,
        MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer::detachDepthStencil() {
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        0,
        MipmapLevel
    ) ;
    unbind() ;
}

GLint Framebuffer::GetColorAttachmentCount() {
    GLint maxColorAttachments = 0 ;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxColorAttachments) ;
    return maxColorAttachments ;
}

GLint Framebuffer::GetMaxDrawBuffers() {
    GLint maxDrawBuffers = 0 ;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuffers) ;
    return maxDrawBuffers ;
}

bool Framebuffer::isComplete() {
    const GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER) ;
    const bool IsComplete = Status == GL_FRAMEBUFFER_COMPLETE ;

    if (!IsComplete) {
        std::string errorLog ;
        switch (Status) {
            case GL_FRAMEBUFFER_UNDEFINED:
                errorLog = Hope::Texts::FBO_Undefined ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                errorLog = Hope::Texts::FBO_IncompleteAttachment ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                errorLog = Hope::Texts::FBO_IncompleteMissingAttachment ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                errorLog = Hope::Texts::FBO_IncompleteDrawBuffer ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                errorLog = Hope::Texts::FBO_IncompleteReadBuffer ;
                break ;
            case GL_FRAMEBUFFER_UNSUPPORTED:
                errorLog = Hope::Texts::FBO_Unsupported ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                errorLog = Hope::Texts::FBO_IncompleteMultisample ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                errorLog = Hope::Texts::FBO_IncompleteLayerTargets ;
                break ;
            default:
                errorLog = Hope::Texts::FBO_UnknownError ;
                break ;
        }

        // Write the error in the log.
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
            logSharedPtr -> writeLine(level, errorLog) ;
        }
    }

    return IsComplete ;
}
