#include <files/images/writers/ImageMemoryWriter.hpp>
#include <files/images/ImageUtils.hpp>
#include <debug/ErrorsManagement.hpp>
#include <utils/StringExt.hpp>
#include <SPITEStrings.hpp>
#include <utils/LogSystem.hpp>
#include <third_party/stb_image_write.h>

using namespace Spite ;
namespace fs = std::filesystem ;

const std::map<std::string, ImageMemoryWriter::Functor> ImageMemoryWriter::ExtensionMemorySave = {
    { ImageUtils::PNGFileExtension, ImageMemoryWriter::SavePNG },
    { ImageUtils::JPGFileExtension, ImageMemoryWriter::SaveJPEG },
    { ImageUtils::JPEGFileExtension, ImageMemoryWriter::SaveJPEG },
    { ImageUtils::BMPFileExtension, ImageMemoryWriter::SaveBMP },
    { ImageUtils::RLEFileExtension, ImageMemoryWriter::SaveBMP },
    { ImageUtils::DIBFileExtension, ImageMemoryWriter::SaveBMP },
    { ImageUtils::TGAFileExtension, ImageMemoryWriter::SaveTGA },
    { ImageUtils::TPICFileExtension, ImageMemoryWriter::SaveTGA },
    { ImageUtils::HDRFileExtension, ImageMemoryWriter::SaveHDR }
} ;

ImageMemoryWriter::ImageMemoryWriter(
    RawImage& data,
    const bool verticalFlip
) : ImageWriter(data, verticalFlip)
{}

bool ImageMemoryWriter::processSpecific() {
    bool success = false ;
    std::string fileExtension ;

    if (data().format().type() == ColorFormat::FloatingPoint) {
        fileExtension = ImageUtils::HDRFileExtension ;
    }
    else {
        fileExtension = ImageUtils::PNGFileExtension ;
    }

    if (ExtensionMemorySave.count(fileExtension)) {
        auto save = ExtensionMemorySave.at(fileExtension) ;
        success = save(
            data(),
            buffer()
        ) ;
    }

    return success ;
}

std::vector<unsigned char>& ImageMemoryWriter::buffer() {
    return m_buffer ;
}

void ImageMemoryWriter::WriteBytesFunc(void* context, void* data, int size) {
    auto* contextBuffer = reinterpret_cast<std::vector<unsigned char>*>(context) ;
    auto* byteData = reinterpret_cast<unsigned char*>(data) ;
    (*contextBuffer).insert((*contextBuffer).end(), byteData, byteData + size) ;
}

bool ImageMemoryWriter::SavePNG(
    RawImage& image,
    std::vector<unsigned char>& buffer
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto pixelSize = image.format().pixelSizeInBytes() ;
    auto& imageBytes = image.data() ;

    return stbi_write_png_to_func(
        &ImageMemoryWriter::WriteBytesFunc,
        reinterpret_cast<void*>(&buffer),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data(),
        pixelSize * image.width()
    ) ;
}

bool ImageMemoryWriter::SaveJPEG(
    RawImage& image,
    std::vector<unsigned char>& buffer
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_jpg_to_func(
        &ImageMemoryWriter::WriteBytesFunc,
        reinterpret_cast<void*>(&buffer),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data(),
        ImageWriter::JPEGQuality
    ) ;
}

bool ImageMemoryWriter::SaveTGA(
    RawImage& image,
    std::vector<unsigned char>& buffer
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_tga_to_func(
        &ImageMemoryWriter::WriteBytesFunc,
        reinterpret_cast<void*>(&buffer),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data()
    ) ;
}

bool ImageMemoryWriter::SaveBMP(
    RawImage& image,
    std::vector<unsigned char>& buffer
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_bmp_to_func(
        &ImageMemoryWriter::WriteBytesFunc,
        reinterpret_cast<void*>(&buffer),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data()
    ) ;
}

bool ImageMemoryWriter::SaveHDR(
    RawImage& image,
    std::vector<unsigned char>& buffer
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;
    auto* imageFloat = reinterpret_cast<float*>(imageBytes.data()) ;

    return stbi_write_hdr_to_func(
        &ImageMemoryWriter::WriteBytesFunc,
        reinterpret_cast<void*>(&buffer),
        image.width(),
        image.height(),
        amountComponents,
        imageFloat
    ) ;
}
