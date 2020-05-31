#include <scene/ogl/textures/environment/EnvironmentMapTexture.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/textures/formats/InternalFormats.hpp>
#include <scene/ogl/textures/formats/PixelFormats.hpp>
#include <scene/ogl/textures/formats/PixelDataTypes.hpp>
#include <scene/ogl/textures/formats/FilterModes.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

EnvironmentMapTexture::EnvironmentMapTexture(
    const unsigned int cubeSize,
    const bool mipmap
) : m_hasMipmap(mipmap) {
    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;

    generateTextureID() ;
    m_faceDimension = Mind::Dimension2Di(cubeSize, cubeSize) ;

    for (GLenum face = CubeFace::First ; face <= CubeFace::Last ; ++face) {
        glTexImage2D(
            face,
            TextureLoD,
            static_cast<GLint>(InternalFormat::RedGreenBlue16f),
            cubeSize,
            cubeSize,
            Border,
            static_cast<GLint>(PixelFormat::RedGreenBlue),
            static_cast<GLint>(PixelDataType::Float),
            nullptr
        ) ;
    }

    setupTexture() ;
}

EnvironmentMapTexture::~EnvironmentMapTexture() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0) ;
    glDeleteTextures(1, &m_textureID) ;
}

void EnvironmentMapTexture::setupTexture() {
    FilterMode minFilter = m_hasMipmap ? FilterMode::Linear_MipLinear : FilterMode::Linear ;

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, FilterMode::Linear) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilter) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE) ;

    if (m_hasMipmap) {
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP) ;
    }
}

void EnvironmentMapTexture::resize(const unsigned int size) {
    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;

    m_faceDimension = Mind::Dimension2Di(size, size) ;

    glBindTexture(GL_TEXTURE_CUBE_MAP, id()) ;

    for (GLenum face = CubeFace::First ; face <= CubeFace::Last ; ++face) {
        glTexImage2D(
            face,
            TextureLoD,
            static_cast<GLint>(InternalFormat::RedGreenBlue16f),
            size,
            size,
            Border,
            static_cast<GLint>(PixelFormat::RedGreenBlue),
            static_cast<GLint>(PixelDataType::Float),
            nullptr
        ) ;
    }

    setupTexture() ;
}

void EnvironmentMapTexture::generateMipmap() {
    m_hasMipmap = true ;

    bind() ;
    setupTexture() ;
}

void EnvironmentMapTexture::generateTextureID() {
    glGenTextures(1, &m_textureID) ;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID) ;
}
