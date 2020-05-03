#include <scene/ogl/textures/environment/EnvironmentMapProcessing.hpp>
#include <scene/ogl/textures/environment/EquirectangularToCubemap.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <files/images/ImageFile.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>
#include <Math.hpp>
#include <algorithm>

using namespace Hope ;
using namespace Hope::GL ;

const float EnvironmentMapProcessing::EquirectangularMapWHRatio = 2.f / 1.f ;
const float EnvironmentMapProcessing::CubeMapWHRatio = 4.f / 3.f ;

void EnvironmentMapProcessing::Load(Spite::RawImage& input) {
    // Compute the ratio to determine the type of picture.
    unsigned int imageWidth = input.width() ;
    unsigned int imageHeight = input.height() ;
    float ratio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight) ;

    if (Mind::Math::equal(ratio, EquirectangularMapWHRatio)) {
        LoadEquirectangular21(input) ;
    }
    else if (Mind::Math::equal(ratio, CubeMapWHRatio)) {
        LoadCubemap(input, Cubemapping::Cube_FrontAligned) ;
    }
    else {
        throw std::runtime_error(Texts::EnvironmentMap_UnknownAspectRatio) ;
    }
}

void EnvironmentMapProcessing::LoadEquirectangular21(Spite::RawImage& rawData) {
    EquirectangularToCubemap converter(rawData) ;
    converter.convert() ;

    for (int face = Cubemapping::First ; face <= Cubemapping::Last ; ++face) {
        auto faceID = static_cast<Cubemapping::CubeFaces>(face) ;

        LoadFace(
            converter.getFaceBytes(faceID),
            rawData.format(),
            converter.faceSize(),
            faceID
        ) ;
    }
}

void EnvironmentMapProcessing::LoadCubemap(
    Spite::RawImage& rawData,
    const Cubemapping::CubemapType type
) {
	// Amount of data to get per line.
	auto faceWidth = Mind::Math::closestPower2(rawData.width() / Cubemapping::AmountCubeFacesX) ;

	for (int face = Cubemapping::First ; face <= Cubemapping::Last ; ++face) {
		std::vector<unsigned char> pixelData ;
        auto faceID = static_cast<Cubemapping::CubeFaces>(face) ;

		ReadCubeFace(
            type,
			faceID,
			rawData,
			pixelData
		) ;

        LoadFace(
            pixelData,
            rawData.format(),
            faceWidth,
            faceID
        ) ;
	}
}

void EnvironmentMapProcessing::LoadFace(
    const std::vector<unsigned char>& faceBytes,
    const Spite::ColorFormat& format,
    const unsigned int faceSize,
    const Cubemapping::CubeFaces face
) {
    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;
    const bool StandardColors = false ;

    glTexImage2D(
        Cubemapping::GLCoordinates(face),
        TextureLoD,
        static_cast<GLint>(TextureLoader::ConvertInternalColorFormat(format, StandardColors)),
        faceSize,
        faceSize,
        Border,
        TextureLoader::ConvertColorFormat(format),
        TextureLoader::ConvertDataType(format),
        faceBytes.data()
    ) ;
}

Spite::RawImage EnvironmentMapProcessing::LoadRawPicture(const std::string& path) {
    Spite::RawImage output ;
	Spite::ImageFile file(path, Cubemapping::FlipVerticalAxis) ;

    if (!file.load(&output)) {
        // Write the error in the log.
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
            logSharedPtr -> writeLine(level, Texts::Texture_UnknownFormat + path) ;
        }
    }

    return output ;
}

void EnvironmentMapProcessing::ReadCubeFace(
    const Cubemapping::CubemapType type,
	const Cubemapping::CubeFaces face,
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

    auto&& coordinates = Cubemapping::CoordinatesFaces(type) ;
	unsigned int bytePictureWidth = pictureWidth * pixelSizeBytes ;
	unsigned int startX = bytePictureWidth * coordinates[face].startX ;
	unsigned int stopX = bytePictureWidth * coordinates[face].stopX ;
	unsigned int startY = pictureHeight * coordinates[face].startY ;
	unsigned int stopY = pictureHeight * coordinates[face].stopY ;

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
