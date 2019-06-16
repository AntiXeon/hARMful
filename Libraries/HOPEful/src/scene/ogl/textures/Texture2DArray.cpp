#include <scene/ogl/textures/Texture2DArray.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

Texture2DArray::Texture2DArray(
    const Mind::Dimension3Di& size,
    const InternalFormat internalFormat,
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

Texture2DArray::~Texture2DArray() {
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0) ;
    glDeleteTextures(1, &m_textureID) ;
}

void Texture2DArray::resize(
    const Mind::Dimension3Di& size,
    const float* pixelData
) {
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureID) ;

    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;
    glTexImage3D(
        GL_TEXTURE_2D_ARRAY,
        TextureLoD,
        static_cast<GLint>(m_internalFormat),
        size.width(),
        size.height(),
        size.depth(),
        Border,
        static_cast<GLenum>(m_pixelFormat),
        static_cast<GLenum>(m_pixelDataType),
        pixelData
    ) ;

    if (m_mipmap) {
        glGenerateMipmap(GL_TEXTURE_2D_ARRAY) ;
    }

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0) ;
}

void Texture2DArray::setWrapModes(std::array<WrapMode, AmountCoordinates> modes) {
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, modes[0]) ;
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, modes[1]) ;
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, modes[2]) ;
}

void Texture2DArray::setBorderColor(const Color& color) {
    glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, color.toRGBA().data()) ;
}

void Texture2DArray::setFiltering(
    GLint downscaling,
    GLint upscaling
) {
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, downscaling) ;
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, upscaling) ;
}
