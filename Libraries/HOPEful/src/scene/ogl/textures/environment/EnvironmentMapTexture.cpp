#include <scene/ogl/textures/environment/EnvironmentMapTexture.hpp>
#include <scene/ogl/textures/environment/CubeFaces.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/textures/formats/InternalFormats.hpp>
#include <scene/ogl/textures/formats/PixelFormats.hpp>
#include <scene/ogl/textures/formats/PixelDataTypes.hpp>
#include <scene/ogl/textures/formats/FilterModes.hpp>
#include <files/images/readers/ImageMemoryReader.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

const std::string EnvironmentMapTexture::HDRFileExtension = "hdr" ;

EnvironmentMapTexture::EnvironmentMapTexture(
    const unsigned int cubeSize,
    const bool mipmap
) : m_hasMipmap(mipmap),
    m_mipmapLevels(1) {
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

    bind() ;
    setupTexture() ;
}

EnvironmentMapTexture::~EnvironmentMapTexture() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0) ;
    glDeleteTextures(1, &m_textureID) ;
}

void EnvironmentMapTexture::resize(const unsigned int size) {
    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;

    m_faceDimension = Mind::Dimension2Di(size, size) ;
    bind() ;

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

EnvironmentMapTexture::EnvironmentMapTexture(
    Spite::TARData& hemContent,
    const fs::path& path,
    const bool autoMipmap
) : m_hasMipmap(true) {
    const GLint TextureLoD = 0 ;

    generateTextureID() ;
    addMipmap(hemContent, path, TextureLoD) ;

    bind() ;
    setupTexture(autoMipmap) ;
}

void EnvironmentMapTexture::addMipmap(
    Spite::TARData& hemContent,
    const fs::path& path,
    const unsigned int level
) {
    const GLint Border = 0 ;
    bool isSizeInitialized = false ;

    for (GLenum face = CubeFace::First ; face <= CubeFace::Last ; ++face) {
        auto faceName = FaceName(static_cast<CubeFace>(face)) ;
        auto faceFilepath = path / fs::path(faceName + "." + HDRFileExtension) ;

        // Get the compressed HDR data from the HEM archive.
        std::vector<unsigned char> imageBuffer ;
        hemContent.readBinaryFile(faceFilepath, imageBuffer) ;

        // Uncompress the HDR file.
        Spite::ImageMemoryReader reader(imageBuffer, false) ;
        auto image = reader.process() ;
        auto imageBytes = image.data() ;

        if (!isSizeInitialized && (level == 0)) {
            m_faceDimension = Mind::Dimension2Di(
                image.width(),
                image.height()
            ) ;

            isSizeInitialized = true ;
        }

        // Put uncompressed image on GPU side.
        glTexImage2D(
            face,
            level,
            static_cast<GLint>(InternalFormat::RedGreenBlue16f),
            image.width(),
            image.height(),
            Border,
            static_cast<GLint>(PixelFormat::RedGreenBlue),
            static_cast<GLint>(PixelDataType::Float),
            imageBytes.data()
        ) ;
    }

    m_mipmapLevels++ ;
}

void EnvironmentMapTexture::generateTextureID() {
    glGenTextures(1, &m_textureID) ;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID) ;
}

void EnvironmentMapTexture::setupTexture(const bool autoMipmap) {
    FilterMode minFilter = m_hasMipmap ? FilterMode::Linear_MipLinear : FilterMode::Linear ;

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, FilterMode::Linear) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilter) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE) ;

    if (m_hasMipmap && autoMipmap) {
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP) ;
    }
}
