#include <scene/ogl/textures/environment/EnvironmentMapTexture.hpp>
#include <scene/ogl/textures/environment/EnvironmentMapProcessing.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/textures/formats/FilterModes.hpp>
#include <files/images/ImageFile.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

EnvironmentMapTexture::EnvironmentMapTexture(const std::array<std::string, EnvironmentMap::AmountFaces>& paths) {
    glGenTextures(1, &m_textureID) ;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID) ;

    // Load all the faces.
    for (int face = EnvironmentMap::First ; face <= EnvironmentMap::Last ; ++face) {
        TextureLoader::LoadFromFile(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
            paths[face],
            EnvironmentMap::FlipVerticalAxis
        ) ;
    }

    // Setup wrapping and filtering.
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, FilterMode::Linear) ;
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, FilterMode::Linear) ;
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) ;
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) ;
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE) ;

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

EnvironmentMapTexture::EnvironmentMapTexture(const std::string& path) {
	glGenTextures(1, &m_textureID) ;
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID) ;

	EnvironmentMapProcessing::Load(path) ;

	// Setup wrapping and filtering.
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, FilterMode::Linear) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, FilterMode::Linear) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) ;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE) ;

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

EnvironmentMapTexture::~EnvironmentMapTexture() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0) ;
    glDeleteTextures(1, &m_textureID) ;
}
