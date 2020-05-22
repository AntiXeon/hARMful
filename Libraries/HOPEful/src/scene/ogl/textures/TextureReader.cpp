#include <scene/ogl/textures/TextureReader.hpp>
#include <scene/ogl/GLDefines.hpp>

using namespace Hope::GL ;

Spite::RawImage TextureReader::Read(
    TextureImage2D* texture,
    const unsigned int mipmapLevel
) {
    Spite::RawImage img(
        GetColorFormatID(texture -> pixelFormat()),
        Spite::ColorFormat::ComponentType::Byte
    ) ;
    img.setDimensions(texture -> width(), texture -> height()) ;

    size_t pixelSize = GetPixelSize(texture -> pixelFormat()) ;
    img.data().resize(img.width() * img.height() * pixelSize) ;

    glGetTextureImage(
        texture -> id(),
        mipmapLevel,
        static_cast<GLenum>(texture -> pixelFormat()),
        static_cast<GLenum>(texture -> pixelDataType()),
        img.data().size(),
        static_cast<void*>(img.data().data())
    ) ;

    return img ;
}

Spite::RawImage TextureReader::Read(
    EnvironmentMapTexture* texture,
    CubeFace face,
    const unsigned int mipmapLevel
) {
    Spite::RawImage img(
        GetColorFormatID(PixelFormat::RedGreenBlue),
        Spite::ColorFormat::ComponentType::FloatingPoint
    ) ;
    img.setDimensions(texture -> faceWidth(), texture -> faceHeight()) ;

    size_t pixelSize = GetPixelSize(PixelFormat::RedGreenBlue) ;
    img.data().resize(img.width() * img.height() * pixelSize * sizeof(float)) ;

    texture -> bind() ;
    glGetTexImage(
        face,
        mipmapLevel,
        static_cast<GLenum>(PixelFormat::RedGreenBlue),
        static_cast<GLenum>(PixelDataType::Float),
        static_cast<void*>(img.data().data())
    ) ;
    texture -> unbind() ;

    return img ;
}

size_t TextureReader::GetPixelSize(const PixelFormat pixelFormat) {
    static const int Unknown = 0 ;
    static const int SingleChannel = 1 ;
    static const int TwoChannels = 2 ;
    static const int ThreeChannels = 3 ;
    static const int FourChannels = 4 ;

    switch (pixelFormat) {
        case PixelFormat::Red:
        case PixelFormat::RedInteger:
        case PixelFormat::StencilIndex:
        case PixelFormat::DepthComponent:
        case PixelFormat::DepthStencil:
        case PixelFormat::Depth24Stencil8:
            return SingleChannel ;

        case PixelFormat::RedGreen:
        case PixelFormat::RedGreenInteger:
            return TwoChannels ;

        case PixelFormat::RedGreenBlue:
        case PixelFormat::BlueGreenRed:
        case PixelFormat::RedGreenBlueInteger:
        case PixelFormat::BlueGreenRedInteger:
            return ThreeChannels ;

        case PixelFormat::RedGreenBlueAlpha:
        case PixelFormat::BlueGreenRedAlpha:
        case PixelFormat::RedGreenBlueAlphaInteger:
        case PixelFormat::BlueGreenRedAlphaInteger:
            return FourChannels ;

        default:
            return Unknown ;
    }
}

Spite::ColorFormat::ID TextureReader::GetColorFormatID(const PixelFormat pixelFormat) {
    switch (pixelFormat) {
        case PixelFormat::Red:
        case PixelFormat::RedInteger:
        case PixelFormat::StencilIndex:
        case PixelFormat::DepthComponent:
        case PixelFormat::DepthStencil:
        case PixelFormat::Depth24Stencil8:
            return Spite::ColorFormat::Gray ;

        case PixelFormat::RedGreen:
        case PixelFormat::RedGreenInteger:
            return Spite::ColorFormat::GrayAlpha ;

        case PixelFormat::RedGreenBlue:
        case PixelFormat::BlueGreenRed:
        case PixelFormat::RedGreenBlueInteger:
        case PixelFormat::BlueGreenRedInteger:
            return Spite::ColorFormat::RGB ;

        case PixelFormat::RedGreenBlueAlpha:
        case PixelFormat::BlueGreenRedAlpha:
        case PixelFormat::RedGreenBlueAlphaInteger:
        case PixelFormat::BlueGreenRedAlphaInteger:
            return Spite::ColorFormat::RGBA ;

        default:
            return Spite::ColorFormat::UnknownID ;
    }
}
