#include <scene/ogl/textures/environment/EnvironmentMapTexture.hpp>
#include <scene/ogl/textures/environment/EnvironmentMapProcessing.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/textures/formats/InternalFormats.hpp>
#include <scene/ogl/textures/formats/PixelFormats.hpp>
#include <scene/ogl/textures/formats/PixelDataTypes.hpp>
#include <scene/ogl/textures/formats/FilterModes.hpp>
#include <files/images/ImageFile.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

EnvironmentMapTexture::EnvironmentMapTexture(const std::array<std::string, Cubemapping::AmountFaces>& paths) {
    generateTextureID() ;

    bool initialized = false ;

    // Load all the faces.
    for (int face = Cubemapping::First ; face <= Cubemapping::Last ; ++face) {
        auto image = TextureLoader::LoadFromFile(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
            paths[face],
            Cubemapping::FlipVerticalAxis
        ) ;

        if (!initialized) {
            m_faceDimension = Mind::Dimension2Di(image.width(), image.height()) ;
        }
        else {
            bool differentWidths = m_faceDimension.width() != image.width() ;
            bool differentHeights = m_faceDimension.height() != image.height() ;

            if (differentWidths || differentHeights) {
                // Write the error in the log.
                auto logWeakPtr = Doom::LogSystem::GetInstance() ;
                auto logSharedPtr = logWeakPtr.lock() ;
                if (logSharedPtr) {
                    Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
                    logSharedPtr -> writeLine(level, Texts::EnvironmentMap_InconsistentSize + paths[face]) ;
                    return ;
                }
            }
        }
    }

    setupTexture() ;
}

EnvironmentMapTexture::EnvironmentMapTexture(const std::string& path) {
    generateTextureID() ;
	Spite::RawImage texture = EnvironmentMapProcessing::LoadRawPicture(path) ;
    EnvironmentMapProcessing::Load(texture) ;
    setupTexture() ;
}

EnvironmentMapTexture::EnvironmentMapTexture(Spite::RawImage& input) {
    generateTextureID() ;
	EnvironmentMapProcessing::Load(input) ;
    setupTexture() ;
}

EnvironmentMapTexture::EnvironmentMapTexture(
    const unsigned int cubeSize,
    const bool mipmap
) : m_hasMipmap(mipmap) {
    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;

    generateTextureID() ;
    m_faceDimension = Mind::Dimension2Di(cubeSize, cubeSize) ;

    for (int face = Cubemapping::First ; face <= Cubemapping::Last ; ++face) {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
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

    for (int face = Cubemapping::First ; face <= Cubemapping::Last ; ++face) {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
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
    bind() ;
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP) ;
}

void EnvironmentMapTexture::generateTextureID() {
    glGenTextures(1, &m_textureID) ;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID) ;
}
