#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <files/images/JPEGTurboFile.hpp>
#include <files/images/PNGFile.hpp>
#include <utils/LogSystem.hpp>
#include <utils/StringExt.hpp>
#include <HOPEStrings.hpp>

using namespace Hope::GL ;

void TextureLoader::LoadFromFile(
    const GLenum target,
    const std::string& path,
    const bool flipVertically
) {
    Spite::RawImage rawData ;

    // Test extension to load the right format.
    ImageFileType fileType = Type(path) ;
    switch(fileType) {
        case ImageFileType::JPEG:
            LoadJPEG(path, rawData, flipVertically) ;
            break ;

        case ImageFileType::PNG:
            LoadPNG(path, rawData, flipVertically) ;
            break ;

        default:
            {
                // Write the error in the log.
                auto logWeakPtr = Doom::LogSystem::GetInstance() ;
                auto logSharedPtr = logWeakPtr.lock() ;
                if (logSharedPtr) {
                    Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
                    logSharedPtr -> writeLine(level, Texts::Texture_UnknownFormat + path) ;
                }
            }
            return ;
    }

    // Convert pictures to OpenGL structures.
    unsigned char* pixelData = nullptr ;
    unsigned int pixelDataSize = 0 ;
    rawData.data(pixelData, pixelDataSize) ;

    // Store the texture on GPU.
    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;

    GLenum colorFormat = ConvertColorFormat(rawData.format()) ;
    glTexImage2D(
        target,
      	TextureLoD,
      	colorFormat,
      	rawData.width(),
      	rawData.height(),
      	Border,
      	colorFormat,
      	GL_UNSIGNED_BYTE,
      	pixelData
    ) ;
}

void TextureLoader::LoadJPEG(
    const std::string& path,
    Spite::RawImage& rawData,
    const bool flipVertically
) {
    rawData.setFormat(Spite::ColorFormat::RGB) ;
    Spite::JPEGTurboFile pic(path, flipVertically) ;
    pic.open(Spite::File::Open_ReadOnly) ;
    pic.load(&rawData) ;
}

void TextureLoader::LoadPNG(
    const std::string& path,
    Spite::RawImage& rawData,
    const bool flipVertically
) {
    rawData.setFormat(Spite::ColorFormat::RGBA) ;
    Spite::PNGFile pic(path) ;
    pic.open(Spite::File::Open_ReadOnly) ;

    if (flipVertically) {
        pic.loadInBottomUpOrder(&rawData) ;
    }
    else {
        pic.loadInUpBottomOrder(&rawData) ;
    }
}

TextureLoader::ImageFileType TextureLoader::Type(const std::string& path) {
    std::vector<std::string> results = Doom::StringExt::Split(path, ".") ;

    if (results.back() == "jpeg" || results.back() == "jpg") {
        return ImageFileType::JPEG ;
    }
    else if (results.back() == "png") {
        return ImageFileType::PNG ;
    }
    else {
        return ImageFileType::Unknown ;
    }
}

GLenum TextureLoader::ConvertColorFormat(const Spite::ColorFormat::ID format) {
    switch(format) {
        case Spite::ColorFormat::RGB:
            return GL_RGB ;
        case Spite::ColorFormat::BGR:
            return GL_BGR ;
        case Spite::ColorFormat::RGBA:
            return GL_RGBA ;
        case Spite::ColorFormat::BGRA:
            return GL_BGRA ;
        default:
            return INVALID_VALUE ;
    }
}
