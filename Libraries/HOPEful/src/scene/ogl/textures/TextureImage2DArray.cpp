#include <scene/ogl/textures/TextureImage2DArray.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

TextureImage2DArray::TextureImage2DArray(
    const Mind::Dimension3Di& size,
    const InternalFormat internalFormat,
    const PixelFormat pixelFormat,
    const PixelDataType pixelDataType,
    const float* pixelData,
    const bool mipmap
) : Texture(
        GL_TEXTURE_2D_ARRAY,
        internalFormat
    ),
    m_size(size),
    m_pixelFormat(pixelFormat),
    m_pixelDataType(pixelDataType),
    m_mipmap(mipmap) {
    resize(size, pixelData) ;
}

void TextureImage2DArray::resize(
    const Mind::Dimension3Di& size,
    const float* pixelData
) {
    glBindTexture(GL_TEXTURE_2D_ARRAY, id()) ;

    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;
    glTexImage3D(
        GL_TEXTURE_2D_ARRAY,
        TextureLoD,
        static_cast<GLint>(internalFormat()),
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

void TextureImage2DArray::setWrapModes(std::array<WrapMode, AmountCoordinates> modes) {
    glTexParameteri(target(), GL_TEXTURE_WRAP_S, modes[0]) ;
    glTexParameteri(target(), GL_TEXTURE_WRAP_T, modes[1]) ;
    glTexParameteri(target(), GL_TEXTURE_WRAP_R, modes[2]) ;
}
