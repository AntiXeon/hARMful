#include <scene/ogl/textures/Texture.hpp>

using namespace Hope::GL ;

Texture::Texture(const GLenum target)
    : m_target(target) {
    glGenTextures(1, &m_textureID) ;
}

Texture::Texture(
    const GLenum target,
    const InternalFormat internalFormat
) : m_target(target),
    m_internalFormat(internalFormat) {
    glGenTextures(1, &m_textureID) ;
}

Texture::~Texture() {
    glBindTexture(m_target, 0) ;
    glDeleteTextures(1, &m_textureID) ;
}

void Texture::setBorderColor(const Color& color) {
    glTexParameterfv(m_target, GL_TEXTURE_BORDER_COLOR, color.toRGBA().data()) ;
}

void Texture::setFiltering(
    GLint downscaling,
    GLint upscaling
) {
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, downscaling) ;
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, upscaling) ;
}

void Texture::setCompareRefToTexture(const bool compare) {
    GLint comparison = GL_NONE ;

    if (compare) {
        comparison = GL_COMPARE_REF_TO_TEXTURE ;
    }

    glTexParameteri(
        m_target,
        GL_TEXTURE_COMPARE_MODE,
        comparison
    ) ;
}

void Texture::setComparisonOperator(const ComparisonOperator op) {
    glTexParameteri(
        m_target,
        GL_TEXTURE_COMPARE_FUNC,
        op
    ) ;
}
