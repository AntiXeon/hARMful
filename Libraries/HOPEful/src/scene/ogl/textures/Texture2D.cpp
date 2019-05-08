#include <scene/ogl/textures/Texture2D.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

Texture2D::Texture2D(const std::string& path) {
    static const bool FlipVerticalAxis = true ;

    glGenTextures(1, &m_textureID) ;
    glBindTexture(GL_TEXTURE_2D, m_textureID) ;
    TextureLoader::LoadFromFile(GL_TEXTURE_2D, path, FlipVerticalAxis) ;
    setFiltering(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR) ;
    glGenerateMipmap(GL_TEXTURE_2D) ;
}

Texture2D::Texture2D(
    const float* pixelData,
    const uint32_t width,
    const uint32_t height,
    const GLint internalFormat,
    const GLenum pixelFormat,
    const GLenum pixelDataType
) {
    glGenTextures(1, &m_textureID) ;
    glBindTexture(GL_TEXTURE_2D, m_textureID) ;

    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;
    glTexImage2D(
        GL_TEXTURE_2D,
      	TextureLoD,
      	internalFormat,
      	width,
      	height,
      	Border,
      	pixelFormat,
      	pixelDataType,
      	pixelData
    ) ;

    glGenerateMipmap(GL_TEXTURE_2D) ;
}

Texture2D::~Texture2D() {
    glBindTexture(GL_TEXTURE_2D, 0) ;
    glDeleteTextures(1, &m_textureID) ;
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
