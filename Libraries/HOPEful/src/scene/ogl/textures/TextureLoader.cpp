#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <files/images/ImageFile.hpp>
#include <utils/LogSystem.hpp>
#include <utils/StringExt.hpp>
#include <HOPEStrings.hpp>

using namespace Hope::GL ;

void TextureLoader::LoadFromFile(
    const GLenum target,
    const std::string& path,
    const bool flipVertically
) {
    Spite::ImageFile file(path, flipVertically) ;
    Spite::RawImage rawData ;

    if (!file.load(&rawData)) {
        // Write the error in the log.
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
            logSharedPtr -> writeLine(level, Texts::Texture_UnknownFormat + path) ;
        }
    }

    // Convert pictures to OpenGL structures.
    std::vector<unsigned char>& pixelData = rawData.data() ;

    // Store the texture on GPU.
    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;

	InternalFormat internalFormat = ConvertInternalColorFormat(rawData.format()) ;
    GLenum colorFormat = ConvertColorFormat(rawData.format()) ;
    glTexImage2D(
        target,
        TextureLoD,
        static_cast<GLint>(internalFormat),
        rawData.width(),
        rawData.height(),
        Border,
        colorFormat,
        GL_UNSIGNED_BYTE,
        pixelData.data()
    ) ;
}

InternalFormat TextureLoader::ConvertInternalColorFormat(const Spite::ColorFormat::ID format) {
    switch(format) {
        case Spite::ColorFormat::Gray:
            return InternalFormat::Red ;
        case Spite::ColorFormat::GrayAlpha:
            return InternalFormat::RedGreen ;
        case Spite::ColorFormat::RGB:
            return InternalFormat::StdRedGreenBlue8 ;
        case Spite::ColorFormat::RGBA:
            return InternalFormat::StdRedGreenBlueAlpha8 ;
        default:
            return InternalFormat::RedGreenBlue ;
    }
}

GLenum TextureLoader::ConvertColorFormat(const Spite::ColorFormat::ID format) {
    switch(format) {
        case Spite::ColorFormat::Gray:
            return GL_RED;
        case Spite::ColorFormat::GrayAlpha:
            return GL_RG;
        case Spite::ColorFormat::RGB:
            return GL_RGB ;
        case Spite::ColorFormat::RGBA:
            return GL_RGBA ;
        default:
            return INVALID_VALUE ;
    }
}
