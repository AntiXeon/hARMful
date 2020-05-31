#include <files/images/writers/ImageFileWriter.hpp>
#include <debug/ErrorsManagement.hpp>
#include <utils/StringExt.hpp>
#include <SPITEStrings.hpp>
#include <utils/LogSystem.hpp>
#include <third_party/stb_image_write.h>

using namespace Spite ;

const std::map<std::string, ImageFileWriter::Functor> ImageFileWriter::ExtensionFileSave = {
    { ImageWriter::PNGFileExtension,  ImageFileWriter::SavePNG },
    { ImageWriter::JPGFileExtension,  ImageFileWriter::SaveJPEG },
    { ImageWriter::JPEGFileExtension, ImageFileWriter::SaveJPEG },
    { ImageWriter::BMPFileExtension,  ImageFileWriter::SaveBMP },
    { ImageWriter::RLEFileExtension,  ImageFileWriter::SaveBMP },
    { ImageWriter::DIBFileExtension,  ImageFileWriter::SaveBMP },
    { ImageWriter::TGAFileExtension,  ImageFileWriter::SaveTGA },
    { ImageWriter::TPICFileExtension, ImageFileWriter::SaveTGA },
    { ImageWriter::HDRFileExtension,  ImageFileWriter::SaveHDR }
} ;

ImageFileWriter::ImageFileWriter(
    RawImage& data,
    const fs::path& path,
    const bool verticalFlip
) : ImageWriter(data, verticalFlip),
    m_path(path)
{}

bool ImageFileWriter::processSpecific() {
    bool success = false ;
    std::string fileExtension ;

    fileExtension = m_path.extension().string() ;
    Doom::StringExt::TextCase(
        fileExtension,
        Doom::StringExt::CharacterCase::Lower
    ) ;

    if ((data().format().type() == ColorFormat::FloatingPoint)
            && (fileExtension != HDRFileExtension)) {
        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Info,
            WriterMsg::Info::HDRExtensionNotMatching,
            m_path.string()
        ) ;

        // It is not possible to convert HDR to another format here!
        m_path.replace_extension(HDRFileExtension) ;
        fileExtension = HDRFileExtension ;
    }

    if (ExtensionFileSave.count(fileExtension)) {
        auto save = ExtensionFileSave.at(fileExtension) ;
        success = save(
            data(),
            m_path.string()
        ) ;

        Doom::LogSystem::WriteLine(
            Doom::LogSystem::Gravity::Info,
            WriterMsg::Info::ImageWrittenOK,
            m_path.string()
        ) ;
    }

    return success ;
}

bool ImageFileWriter::SavePNG(
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

bool ImageFileWriter::SaveJPEG(
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
        ImageWriter::JPEGQuality
    ) ;
}

bool ImageFileWriter::SaveTGA(
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

bool ImageFileWriter::SaveBMP(
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

bool ImageFileWriter::SaveHDR(
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
