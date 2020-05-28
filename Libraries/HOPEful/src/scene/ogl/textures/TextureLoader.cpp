#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <files/images/ImageFile.hpp>
#include <utils/LogSystem.hpp>
#include <utils/StringExt.hpp>
#include <HOPEStrings.hpp>

using namespace Hope::GL ;

Spite::RawImage TextureLoader::LoadFromFile(
    const GLenum target,
    const std::string& path,
    const bool flipVertically
) {
    Spite::ImageFile file(path, flipVertically) ;
    Spite::RawImage rawData ;

    if (!file.load(&rawData)) {
        auto level = Doom::LogSystem::Gravity::Critical ;
        Doom::LogSystem::WriteLine(level, Texts::Texture_UnknownFormat + path) ;
    }

    // Convert pictures to OpenGL structures.
    std::vector<unsigned char>& pixelData = rawData.data() ;

    // Store the texture on GPU.
    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;

	InternalFormat internalFormat = ConvertInternalColorFormat(rawData.format()) ;
    GLenum colorFormat = ConvertColorFormat(rawData.format()) ;
    GLenum dataType = ConvertDataType(rawData.format()) ;
    glTexImage2D(
        target,
        TextureLoD,
        static_cast<GLint>(internalFormat),
        rawData.width(),
        rawData.height(),
        Border,
        colorFormat,
        dataType,
        pixelData.data()
    ) ;

    return rawData ;
}

InternalFormat TextureLoader::ConvertInternalColorFormat(const Spite::ColorFormat& format, const bool standard) {
    switch (format.id()) {
        case Spite::ColorFormat::Gray:
            return InternalFormat::Red ;
        case Spite::ColorFormat::GrayAlpha:
            return InternalFormat::RedGreen ;
        case Spite::ColorFormat::RGB:
			return (standard) ? InternalFormat::StdRedGreenBlue8 : InternalFormat::RedGreenBlue ;
        case Spite::ColorFormat::RGBA:
			return (standard) ? InternalFormat::StdRedGreenBlueAlpha8 : InternalFormat::RedGreenBlueAlpha ;
        default:
            return InternalFormat::RedGreenBlue ;
    }
}

GLenum TextureLoader::ConvertColorFormat(const Spite::ColorFormat& format) {
    switch (format.id()) {
        case Spite::ColorFormat::Gray:
            return GL_RED ;
        case Spite::ColorFormat::GrayAlpha:
            return GL_RG ;
        case Spite::ColorFormat::RGB:
            return GL_RGB ;
        case Spite::ColorFormat::RGBA:
            return GL_RGBA ;
        default:
            return INVALID_VALUE ;
    }
}

GLenum TextureLoader::ConvertDataType(const Spite::ColorFormat& format) {
    switch (format.type()) {
        case Spite::ColorFormat::Byte:
            return GL_UNSIGNED_BYTE ;
        case Spite::ColorFormat::FloatingPoint:
            return GL_FLOAT ;
        default:
            return INVALID_VALUE ;
    }
}
