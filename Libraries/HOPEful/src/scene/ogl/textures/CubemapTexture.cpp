#include <scene/ogl/textures/CubemapTexture.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/textures/formats/FilterModes.hpp>
#include <utils/LogSystem.hpp>
#include <utils/StringExt.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

CubemapTexture::CubemapTexture(std::array<std::string, AmountFaces> paths) {
    glGenTextures(1, &m_textureID) ;

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID) ;

    // Load all the faces.
    for (int face = CubemapTexture::Right ; face < AmountFaces ; ++face) {
        // Because OpenGL uses top left point as (0,0) for cube maps, instead of the
        // lower left point as for TextureImage2Ds...
        static const bool FlipVerticalAxis = false ;

        TextureLoader::LoadFromFile(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
            paths[face],
            FlipVerticalAxis
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

CubemapTexture::~CubemapTexture() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0) ;
    glDeleteTextures(1, &m_textureID) ;
}
