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
const std::string ImageWriter::PNGFileExtension = ".png" ;

const std::map<std::string, Image::FileSave::Functor> ImageWriter::ExtensionFileSave = {
    { ImageWriter::PNGFileExtension, Image::FileSave::SavePNG },
    { ".jpg", Image::FileSave::SaveJPEG },
    { ".jpeg", Image::FileSave::SaveJPEG },
    { ".bmp", Image::FileSave::SaveBMP },
    { ".rle", Image::FileSave::SaveBMP },
    { ".dib", Image::FileSave::SaveBMP },
    { ".tga", Image::FileSave::SaveTGA },
    { ".tpic", Image::FileSave::SaveTGA },
    { ImageWriter::HDRFileExtension, Image::FileSave::SaveHDR }
} ;

const std::map<std::string, Image::BufferSave::Functor> ImageWriter::ExtensionBufferSave = {
    { ImageWriter::PNGFileExtension, Image::BufferSave::SavePNG },
    { ".jpg", Image::BufferSave::SaveJPEG },
    { ".jpeg", Image::BufferSave::SaveJPEG },
    { ".bmp", Image::BufferSave::SaveBMP },
    { ".rle", Image::BufferSave::SaveBMP },
    { ".dib", Image::BufferSave::SaveBMP },
    { ".tga", Image::BufferSave::SaveTGA },
    { ".tpic", Image::BufferSave::SaveTGA },
    { ImageWriter::HDRFileExtension, Image::BufferSave::SaveHDR }
} ;

ImageWriter::ImageWriter(
    RawImage& data,
    const std::filesystem::path& path,
    const bool verticalFlip
) : m_output(Output::File),
    m_data(data),
    m_path(path),
    m_verticalFlip(verticalFlip)
{}

ImageWriter::ImageWriter(
    RawImage& data,
    std::vector<unsigned char>& buffer,
    const bool verticalFlip
) : m_output(Output::Buffer),
    m_data(data),
    m_buffer(&buffer),
    m_verticalFlip(verticalFlip)
{}

bool ImageWriter::process() {
    bool cachedFlipBefore = stbi__flip_vertically_on_write ;
    stbi_flip_vertically_on_write(m_verticalFlip) ;

    bool success = false ;

    switch (m_output) {
        case Output::File:
            success = processFile() ;
            break ;

        case Output::Buffer:
            success = processBuffer() ;
            break ;
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

void ImageWriter::SetCompressTGAWithRLE(const bool rleEnabled) {
    stbi_write_tga_with_rle = rleEnabled ;
}

bool ImageWriter::processFile() {
    bool success = false ;
    std::string fileExtension ;

    fileExtension = m_path.extension().string() ;
    Doom::StringExt::TextCase(
        fileExtension,
        Doom::StringExt::CharacterCase::Lower
    ) ;

    if ((m_data.get().format().type() == ColorFormat::FloatingPoint)
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
            m_data.get(),
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

bool ImageWriter::processBuffer() {
    bool success = false ;
    std::string fileExtension ;

    if (m_data.get().format().type() == ColorFormat::FloatingPoint) {
        fileExtension = HDRFileExtension ;
    }
    else {
        fileExtension = PNGFileExtension ;
    }

    if (ExtensionBufferSave.count(fileExtension)) {
        auto save = ExtensionBufferSave.at(fileExtension) ;
        success = save(
            m_data.get(),
            *m_buffer
        ) ;
    }

    return success ;
}
