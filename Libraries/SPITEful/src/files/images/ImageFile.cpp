#include <files/images/ImageFile.hpp>
#include <files/images/ImageWriter.hpp>
#include <debug/ErrorsManagement.hpp>
#include <utils/StringExt.hpp>
#include <SPITEStrings.hpp>
#include <filesystem>
#include <string>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <third_party/stb_image.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <third_party/stb_image_resize.h>

using namespace Spite ;
namespace fs = std::filesystem ;

const float ImageFile::GammaCorrection = 2.2f ;
const float ImageFile::HDRScale = 1.f ;

ImageFile::ImageFile(const std::string& path, const bool flip)
    : File(path),
      m_flip(flip) {}

bool ImageFile::load(IFileData* filedata) {
    stbi_set_flip_vertically_on_load(m_flip) ;
    std::string filepath = path().string() ;

    int width = 0 ;
    int height = 0 ;
    int amountComponents = 0 ;
    stbi_info(filepath.c_str(), &width, &height, &amountComponents) ;

    RawImage* rawImage = dynamic_cast<RawImage*>(filedata) ;
    unsigned char* imageData = nullptr ;
    bool isHDR = stbi_is_hdr(filepath.c_str()) ;

    if (isHDR) {
        // HDR pictures store data as floating point values.
        rawImage -> setFormat(
            static_cast<ColorFormat::ID>(amountComponents),
            ColorFormat::ComponentType::FloatingPoint
        ) ;

        stbi_ldr_to_hdr_scale(HDRScale);
        stbi_ldr_to_hdr_gamma(GammaCorrection);
        float* hdrData = stbi_loadf(filepath.c_str(), &width, &height, &amountComponents, 0) ;
        imageData = reinterpret_cast<unsigned char*>(hdrData) ;
    }
    else {
        // Usual pictures store color values in integer values, usually one byte
        // per component color.
        rawImage -> setFormat(
            static_cast<ColorFormat::ID>(amountComponents),
            ColorFormat::ComponentType::Byte
        ) ;

        stbi_hdr_to_ldr_gamma(GammaCorrection) ;
        stbi_hdr_to_ldr_scale(HDRScale) ;
        imageData = stbi_load(filepath.c_str(), &width, &height, &amountComponents, 0) ;
    }

    rawImage -> setDimensions(width, height) ;
    auto& rawPixelData = rawImage -> data() ;
    const auto& imageFormat = rawImage -> format() ;

    size_t width_64 = width ;
    size_t height_64 = height ;
    size_t pixelSize_64 = imageFormat.pixelSizeInBytes() ;
    size_t imageDataSize = width_64 * height_64 * pixelSize_64 ;
    rawPixelData.insert(rawPixelData.begin(), imageData, imageData + imageDataSize) ;
    stbi_image_free(imageData) ;

    return (rawPixelData.size()) > 0 ;
}

bool ImageFile::save(
    IFileData* output,
    const std::string& path
) {
    auto* imageData = static_cast<RawImage*>(output) ;
    fs::path filepath(path) ;

    ImageWriter writer(*imageData, filepath) ;
    return writer.process() ;
}

RawImage ImageFile::Resize(
    RawImage& original,
    const unsigned int width,
    const unsigned int height
) {
    auto& format = original.format() ;
    unsigned int amountChannels = format.amountOfComponents() ;
    const unsigned int StrideInBytes = 0 ;

    unsigned int originalWidth = original.width() ;
    unsigned int originalHeight = original.height() ;
    auto& originalBytes = original.data() ;

    RawImage resized ;
    resized.setFormat(format.id(), format.type()) ;
    resized.setDimensions(width, height) ;

    switch (format.type()) {
        case ColorFormat::Byte:
        {
            auto& resizedBytes = resized.data() ;

            stbir_resize_uint8_generic(
                originalBytes.data(),
                originalWidth,
                originalHeight,
                StrideInBytes,
                resizedBytes.data(),
                width,
                height,
                StrideInBytes,
                amountChannels,
                STBIR_ALPHA_CHANNEL_NONE,
                0,
                STBIR_EDGE_CLAMP,
                STBIR_FILTER_CUBICBSPLINE,
                STBIR_COLORSPACE_LINEAR,
                nullptr
            ) ;
        }
        break ;

        case ColorFormat::FloatingPoint:
        {
            std::vector<float> resizedPixels(width * height * amountChannels) ;
            auto* originalPixels = reinterpret_cast<float*>(originalBytes.data()) ;

            stbir_resize_float_generic(
                originalPixels,
                originalWidth,
                originalHeight,
                StrideInBytes,
                resizedPixels.data(),
                width,
                height,
                StrideInBytes,
                amountChannels,
                STBIR_ALPHA_CHANNEL_NONE,
                0,
                STBIR_EDGE_CLAMP,
                STBIR_FILTER_CUBICBSPLINE,
                STBIR_COLORSPACE_SRGB,
                nullptr
            ) ;

            auto* resizedPixelBytes = reinterpret_cast<unsigned char*>(resizedPixels.data()) ;
            resized.data().insert(
                resized.data().begin(),
                resizedPixelBytes,
                resizedPixelBytes + (resizedPixels.size() * sizeof(float))
            ) ;
        }
        break ;

        default:
            throw std::runtime_error(ColorFormatMsg::Error::UnknownFormat) ;
    }

    return resized ;
}
