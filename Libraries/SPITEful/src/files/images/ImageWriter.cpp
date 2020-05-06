#include <files/images/ImageWriter.hpp>
#include <debug/ErrorsManagement.hpp>
#include <utils/StringExt.hpp>
#include <SPITEStrings.hpp>
#include <utils/LogSystem.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <third_party/stb_image_write.h>

using namespace Spite ;
namespace fs = std::filesystem ;

const std::string ImageWriter::HDRFileExtension = ".hdr" ;

const std::map<std::string, ImageWriter::SaveFunctor> ImageWriter::ExtensionSave = {
    { ".png", ImageWriter::SavePNG },
    { ".jpg", ImageWriter::SaveJPEG },
    { ".jpeg", ImageWriter::SaveJPEG },
    { ".bmp", ImageWriter::SaveBMP },
    { ".rle", ImageWriter::SaveBMP },
    { ".dib", ImageWriter::SaveBMP },
    { ".tga", ImageWriter::SaveTGA },
    { ".tpic", ImageWriter::SaveTGA },
    { ImageWriter::HDRFileExtension, ImageWriter::SaveHDR }
} ;

int ImageWriter::JPEGQuality = 90 ;

ImageWriter::ImageWriter(
    RawImage& data,
    const std::filesystem::path& path,
    const bool verticalFlip
) : m_data(data),
    m_path(path),
    m_verticalFlip(verticalFlip)
{}

bool ImageWriter::process() {
    bool cachedFlipBefore = stbi__flip_vertically_on_write ;
    stbi_flip_vertically_on_write(m_verticalFlip) ;

    bool success = false ;

    // Log info.
    std::weak_ptr<Doom::LogSystem> logWeakPtr = Doom::LogSystem::GetInstance() ;
    std::shared_ptr<Doom::LogSystem> logSystem = logWeakPtr.lock() ;

    if (!logSystem) {
        return success ;
    }

    auto fileExtension = m_path.extension().string() ;
    Doom::StringExt::TextCase(
        fileExtension,
        Doom::StringExt::CharacterCase::Lower
    ) ;

    if ((m_data.get().format().type() == ColorFormat::FloatingPoint)
            && (fileExtension != HDRFileExtension)) {
        logSystem -> writeLine(
            Doom::LogSystem::Gravity::Info,
            WriterMsg::Info::HDRExtensionNotMatching,
            m_path.string()
        ) ;

        // It is not possible to convert HDR to another format here!
        m_path.replace_extension(HDRFileExtension) ;
        fileExtension = HDRFileExtension ;
    }

    if (ExtensionSave.count(fileExtension)) {
        SaveFunctor save = ExtensionSave.at(fileExtension) ;
        success = save(
            m_data.get(),
            m_path.string()
        ) ;

        logSystem -> writeLine(
            Doom::LogSystem::Gravity::Info,
            WriterMsg::Info::ImageWrittenOK,
            m_path.string()
        ) ;
    }

    stbi_flip_vertically_on_write(cachedFlipBefore) ;

    return success ;
}

void ImageWriter::SetPNGCompressionLevel(const int level) {
    const int MinLevel = 0 ;
    const int MaxLevel = 9 ;
    int clampedLevel = std::clamp(level, MinLevel, MaxLevel) ;
    stbi_write_png_compression_level = clampedLevel ;
}

void ImageWriter::SetPNGFilter(const PNGFilter filter) {
    stbi_write_force_png_filter = filter ;
}

void ImageWriter::SetJPEGQuality(const int quality) {
    const int MinQuality = 1 ;
    const int MaxQuality = 100 ;
    int clampedQuality = std::clamp(quality, MinQuality, MaxQuality) ;
    JPEGQuality = clampedQuality ;
}

void ImageWriter::SetCompressTGAWithRLE(const bool rleEnabled) {
    stbi_write_tga_with_rle = rleEnabled ;
}

bool ImageWriter::SavePNG(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto pixelSize = image.format().pixelSizeInBytes() ;
    auto& imageBytes = image.data() ;

    return stbi_write_png(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data(),
        pixelSize * image.width()
    ) ;
}

bool ImageWriter::SaveJPEG(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_jpg(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data(),
        JPEGQuality
    ) ;
}

bool ImageWriter::SaveTGA(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_tga(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data()
    ) ;
}

bool ImageWriter::SaveBMP(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_bmp(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data()
    ) ;
}

bool ImageWriter::SaveHDR(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;
    auto* imageFloat = reinterpret_cast<float*>(imageBytes.data()) ;

    return stbi_write_hdr(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageFloat
    ) ;
}
