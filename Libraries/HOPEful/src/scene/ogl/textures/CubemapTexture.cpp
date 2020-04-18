#include <scene/ogl/textures/CubemapTexture.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/textures/formats/FilterModes.hpp>
#include <files/images/ImageFile.hpp>
#include <utils/LogSystem.hpp>
#include <utils/StringExt.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

const std::array<CubemapTexture::CoordsCubeFaces, CubemapTexture::AmountFaces> CubemapTexture::CoordinatesFaces =
{{
	{ .startX = 0.50f, .startY = 1.f/3.f, .stopX = 0.75f, .stopY = 2.f/3.f, },	// Right
	{ .startX = 0.f,   .startY = 1.f/3.f, .stopX = 0.25f, .stopY = 2.f/3.f, },	// Left
	{ .startX = 0.25f, .startY = 0.f,     .stopX = 0.5f, .stopY = 1.f/3.f, },	// Top
	{ .startX = 0.25f, .startY = 2.f/3.f, .stopX = 0.5f, .stopY = 1.f, },		// Bottom
	{ .startX = 0.25f, .startY = 1.f/3.f, .stopX = 0.5f, .stopY = 2.f/3.f, },	// Back
	{ .startX = 0.75f, .startY = 1.f/3.f, .stopX = 1.f,  .stopY = 2.f/3.f, }	// Front
}} ;

CubemapTexture::CubemapTexture(const std::array<std::string, AmountFaces>& paths) {
    glGenTextures(1, &m_textureID) ;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID) ;

    // Load all the faces.
    for (int face = CubemapTexture::Right ; face < AmountFaces ; ++face) {
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

CubemapTexture::CubemapTexture(const std::string& path, const CubemapTexture::TextureType type) {
	glGenTextures(1, &m_textureID) ;
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID) ;

	switch(type) {
		case TextureType::Equirectangular :
			break ;

		case TextureType::Cubemap :
			loadCubemap(path) ;
			break ;
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

void CubemapTexture::loadRawPicture(
	const std::string& path,
	Spite::RawImage& rawData
) {
	Spite::ImageFile file(path, FlipVerticalAxis) ;

    if (!file.load(&rawData)) {
        // Write the error in the log.
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
            logSharedPtr -> writeLine(level, Texts::Texture_UnknownFormat + path) ;
        }
    }
}

void CubemapTexture::loadCubemap(const std::string& path) {
	const GLint TextureLoD = 0 ;
	const GLint Border = 0 ;
	const bool StandardColors = false ;

	Spite::RawImage rawData ;
	loadRawPicture(path, rawData) ;
	const auto& colorFormat = rawData.format() ;

	// Amount of data to get per line.
	unsigned int faceWidth = rawData.width() / 4 ;
	unsigned int faceHeight = rawData.height() / 3 ;

	for (int face = CubemapTexture::Right ; face < AmountFaces ; ++face) {
		std::vector<unsigned char> pixelData ;
		readCubeFace(
			static_cast<CubemapTexture::CubeFaces>(face),
			rawData,
			pixelData
		) ;

		glTexImage2D(
	        GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
	        TextureLoD,
	        static_cast<GLint>(TextureLoader::ConvertInternalColorFormat(colorFormat, StandardColors)),
	        faceWidth,
	        faceHeight,
	        Border,
	        TextureLoader::ConvertColorFormat(colorFormat),
	        TextureLoader::ConvertDataType(colorFormat),
	        pixelData.data()
	    ) ;
	}
}

void CubemapTexture::readCubeFace(
	const CubemapTexture::CubeFaces face,
	Spite::RawImage& pictureData,
	std::vector<unsigned char>& outPixels
) {
	const auto& colorFormat = pictureData.format() ;
	unsigned char pixelSizeBytes = colorFormat.pixelSizeInBytes() ;
	unsigned int pictureWidth = pictureData.width() ;
	unsigned int pictureHeight = pictureData.height() ;

	// Amount of data to get per line.
	unsigned int amountPixelsDataX = (pictureWidth / 4) * pixelSizeBytes ;
	unsigned int amountPixelsY = (pictureHeight / 3) ;

	unsigned int bytePictureWidth = pictureWidth * pixelSizeBytes ;
	unsigned int startX = bytePictureWidth * CoordinatesFaces[face].startX ;
	unsigned int stopX = bytePictureWidth * CoordinatesFaces[face].stopX ;
	unsigned int startY = pictureHeight * CoordinatesFaces[face].startY ;
	unsigned int stopY = pictureHeight * CoordinatesFaces[face].stopY ;

	outPixels.reserve(amountPixelsDataX * amountPixelsY) ;

	for (unsigned int y = startY ; y < stopY ; ++y) {
		unsigned int rowOffset = bytePictureWidth * y ;

		outPixels.insert(
			outPixels.end(),
			pictureData.data().begin() + (startX + rowOffset),
			pictureData.data().begin() + (stopX + rowOffset)
		) ;
	}
}
