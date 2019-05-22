#include <scene/ogl/textures/Texture2D.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

Texture2D::Texture2D(
    const std::string& path,
    const bool mipmap
) {
    static const bool FlipVerticalAxis = true ;

    glGenTextures(1, &m_textureID) ;
    glBindTexture(GL_TEXTURE_2D, m_textureID) ;
    TextureLoader::LoadFromFile(GL_TEXTURE_2D, path, FlipVerticalAxis) ;
    setFiltering(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR) ;

    if (mipmap) {
        glGenerateMipmap(GL_TEXTURE_2D) ;
    }

    glBindTexture(GL_TEXTURE_2D, 0) ;
}

Texture2D::Texture2D(
    const Mind::Dimension2Di& size,
    const PixelFormat internalFormat,
    const PixelFormat pixelFormat,
    const PixelDataType pixelDataType,
    const float* pixelData,
    const bool mipmap
) {
    // Store data.
    m_internalFormat = internalFormat ;
    m_pixelFormat = pixelFormat ;
    m_pixelDataType = pixelDataType ;
    m_mipmap = mipmap ;

    glGenTextures(1, &m_textureID) ;
    resize(size, pixelData) ;
}

Texture2D::~Texture2D() {
    glBindTexture(GL_TEXTURE_2D, 0) ;
    glDeleteTextures(1, &m_textureID) ;
}

void Texture2D::resize(
    const Mind::Dimension2Di& size,
    const float* pixelData
) {
    glBindTexture(GL_TEXTURE_2D, m_textureID) ;

    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;
    glTexImage2D(
        GL_TEXTURE_2D,
        TextureLoD,
        m_internalFormat,
        size.width(),
        size.height(),
        Border,
        m_pixelFormat,
        m_pixelDataType,
        pixelData
    ) ;

    if (m_mipmap) {
        glGenerateMipmap(GL_TEXTURE_2D) ;
    }

    glBindTexture(GL_TEXTURE_2D, 0) ;
}

void Texture2D::setWrapModes(std::array<GLint, AmountCoordinates> modes) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, modes[0]) ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, modes[1]) ;
}

void Texture2D::setBorderColor(const Color& color) {
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color.toRGBA().data()) ;
}

void Texture2D::setFiltering(
    GLint downscaling,
    GLint upscaling
) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, downscaling) ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, upscaling) ;
}
