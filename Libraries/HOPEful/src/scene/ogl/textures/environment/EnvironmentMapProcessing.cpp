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

void EnvironmentMapProcessing::Load(const std::string& path) {
    Spite::RawImage rawData ;
	LoadRawPicture(path, rawData) ;

    // Compute the ratio to determine the type of picture.
    unsigned int imageWidth = rawData.width() ;
    unsigned int imageHeight = rawData.height() ;
    float ratio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight) ;

    // Write the error in the log.
    auto logWeakPtr = Doom::LogSystem::GetInstance() ;
    auto logSharedPtr = logWeakPtr.lock() ;

    if (Mind::Math::equal(ratio, EquirectangularMapWHRatio)) {
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Info ;
            logSharedPtr -> writeLine(level, Texts::EnvironmentMap_Load21 + path) ;
        }

        LoadEquirectangular21(rawData) ;
    }
    else if (Mind::Math::equal(ratio, CubeMapWHRatio)) {
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Info ;
            logSharedPtr -> writeLine(level, Texts::EnvironmentMap_LoadCubemap + path) ;
        }

        LoadCubemap(rawData, EnvironmentMap::Cube_FrontAligned) ;
    }
    else {
        throw std::runtime_error(Texts::EnvironmentMap_UnknownAspectRatio + path) ;
    }
}

void EnvironmentMapProcessing::LoadEquirectangular21(Spite::RawImage& rawData) {
    EquirectangularToCubemap converter(rawData) ;
    converter.convert() ;

    for (int face = EnvironmentMap::First ; face <= EnvironmentMap::Last ; ++face) {
        auto faceID = static_cast<EnvironmentMap::CubeFaces>(face) ;

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
    const EnvironmentMap::CubemapType type
) {
	// Amount of data to get per line.
	auto faceWidth = Mind::Math::closestPower2(rawData.width() / EnvironmentMap::AmountCubeFacesX) ;

	for (int face = EnvironmentMap::First ; face <= EnvironmentMap::Last ; ++face) {
		std::vector<unsigned char> pixelData ;
        auto faceID = static_cast<EnvironmentMap::CubeFaces>(face) ;

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
    const EnvironmentMap::CubeFaces face
) {
    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;
    const bool StandardColors = false ;

    glTexImage2D(
        EnvironmentMap::GLCoordinates(face),
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

void EnvironmentMapProcessing::LoadRawPicture(
	const std::string& path,
	Spite::RawImage& rawData
) {
	Spite::ImageFile file(path, EnvironmentMap::FlipVerticalAxis) ;

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

void EnvironmentMapProcessing::ReadCubeFace(
    const EnvironmentMap::CubemapType type,
	const EnvironmentMap::CubeFaces face,
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

    auto&& coordinates = EnvironmentMap::CoordinatesFaces(type) ;
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
