#include <scene/ogl/textures/Texture2D.hpp>
#include <files/images/JPEGTurboFile.hpp>
#include <files/images/PNGFile.hpp>
#include <utils/LogSystem.hpp>
#include <utils/StringExt.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

Texture2D::Texture2D(const std::string& path) {
    glGenTextures(1, &m_textureID) ;
    glBindTexture(GL_TEXTURE_2D, m_textureID) ;
    loadFromFile(path) ;
    setFiltering(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR) ;
    glGenerateMipmap(GL_TEXTURE_2D) ;
}

Texture2D::Texture2D(
    const float* pixelData,
    const uint32_t width,
    const uint32_t height,
    const GLint internalFormat,
    const GLenum pixelFormat,
    const GLenum pixelDataType
) {
    glGenTextures(1, &m_textureID) ;
    glBindTexture(GL_TEXTURE_2D, m_textureID) ;

    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;
    glTexImage2D(
        GL_TEXTURE_2D,
      	TextureLoD,
      	internalFormat,
      	width,
      	height,
      	Border,
      	pixelFormat,
      	pixelDataType,
      	pixelData
    ) ;

    glGenerateMipmap(GL_TEXTURE_2D) ;
}

Texture2D::~Texture2D() {
    glBindTexture(GL_TEXTURE_2D, 0) ;
    glDeleteTextures(1, &m_textureID) ;
}

void Texture2D::setWrapModes(std::array<GLint, AmountCoordinates> modes) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, modes[0]) ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, modes[1]) ;
}

void Texture2D::setBorderColor(const Color& color) {
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color.toRGBA().data()) ;
}

void Texture2D::setFiltering(
    GLint downscaling,
    GLint upscaling
) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, downscaling) ;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, upscaling) ;
}

void Texture2D::loadFromFile(const std::string& path) {
    Spite::RawImage rawData ;

    // Test extension to load the right format.
    ImageFileType fileType = type(path) ;
    switch(fileType) {
        case ImageFileType::JPEG:
            loadJPEG(path, rawData) ;
            break ;

        case ImageFileType::PNG:
            loadPNG(path, rawData) ;
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

    GLenum colorFormat = convertColorFormat(rawData.format()) ;
    glTexImage2D(
        GL_TEXTURE_2D,
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

void Texture2D::loadJPEG(
    const std::string& path,
    Spite::RawImage& rawData
) {
    const bool LoadInBottomUpOrder = true ;
    rawData.setFormat(Spite::ColorFormat::RGB) ;
    Spite::JPEGTurboFile pic(path, LoadInBottomUpOrder) ;
    pic.open(Spite::File::Open_ReadOnly) ;
    pic.load(&rawData) ;
}

void Texture2D::loadPNG(
    const std::string& path,
    Spite::RawImage& rawData
) {
    rawData.setFormat(Spite::ColorFormat::RGBA) ;
    Spite::PNGFile pic(path) ;
    pic.open(Spite::File::Open_ReadOnly) ;
    pic.loadInBottomUpOrder(&rawData) ;
}

Texture2D::ImageFileType Texture2D::type(const std::string& path) {
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

GLenum Texture2D::convertColorFormat(const Spite::ColorFormat::ID format) {
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
