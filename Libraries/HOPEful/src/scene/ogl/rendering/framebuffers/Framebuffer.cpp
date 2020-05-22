#include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope::GL ;

const bool Framebuffer::GenerateMipmaps = false ;

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &m_fboID) ;
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_fboID) ;
}

void Framebuffer::setReadBuffer(const unsigned char index) {
    glNamedFramebufferReadBuffer(m_fboID, GL_COLOR_ATTACHMENT0 + index) ;
}

void Framebuffer::unsetReadBuffer() {
    glNamedFramebufferReadBuffer(m_fboID, GL_NONE) ;
}

void Framebuffer::setDrawBuffers(const std::list<unsigned char>& indices) {
    if (indices.size() > 0) {
        std::vector<unsigned int> attachments ;
        for (unsigned int index: indices) {
            attachments.push_back(GL_COLOR_ATTACHMENT0 + index) ;
        }

        glNamedFramebufferDrawBuffers(
            m_fboID,
            static_cast<int>(attachments.size()),
            attachments.data()
        ) ;
    }
    else {
        useNoColorBuffers() ;
    }
}

void Framebuffer::useNoColorBuffers() {
    const static GLsizei Size = 1 ;
    const static GLenum None[Size] = { GL_NONE } ;
    glNamedFramebufferDrawBuffers(m_fboID, Size, None) ;
}

void Framebuffer::attachCubeColor(
    const unsigned char attachmentIndex,
    const EnvironmentMapTexture* texture,
    const CubeFace faceIndex
) {
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0 + attachmentIndex,
        faceIndex,
        texture -> id(),
        Framebuffer::MipmapLevel
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

bool Framebuffer::isComplete() const {
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
