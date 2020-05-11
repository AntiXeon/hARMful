#ifndef __HOPE__GL_TEXTURE_READER__
#define __HOPE__GL_TEXTURE_READER__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>

#include <scene/ogl/textures/TextureImage2D.hpp>
#include <scene/ogl/textures/TextureImage2DArray.hpp>
#include <scene/ogl/textures/formats/PixelFormats.hpp>
#include <string>
#include <vector>

namespace Hope::GL {
    /**
     * Read the content of a texture from GPU to be available on CPU side.
     */
    class TextureReader final {
        public:
            /**
             * Read the content of a TextureImage2D.
             * @warning The PixelType must fit the data type of the texture.
             */
            template<typename PixelType>
            exported static std::vector<PixelType> Read(
                TextureImage2D* texture,
                const unsigned int mipmapLevel = 0
            ) ;

            /**
             * Read the content of a TextureImage2D.
             * @warning The PixelType must fit the data type of the texture.
             */
            template<typename PixelType>
            exported static std::vector<PixelType> Read(TextureImage2DArray* texture) ;

        private:
            /**
             * Get the size of a single pixel.
             */
            exported static size_t GetPixelSize(const PixelFormat pixelFormat) ;
    } ;


    template<typename PixelType>
    std::vector<PixelType> TextureReader::Read(
        TextureImage2D* texture,
        const unsigned int mipmapLevel
    ) {
        std::vector<PixelType> pixels ;

        uint32_t textureWidth = texture -> width() ;
        uint32_t textureHeight = texture -> height() ;
        size_t pixelSize = GetPixelSize(texture -> pixelFormat()) ;

        pixels.resize(textureWidth * textureHeight * pixelSize) ;

        glGetTextureImage(
            texture -> id(),
            mipmapLevel,
            static_cast<GLenum>(texture -> pixelFormat()),
            static_cast<GLenum>(texture -> pixelDataType()),
            pixels.size(),
            static_cast<void*>(pixels.data())
        ) ;

        return pixels ;
    }

    template<typename PixelType>
    std::vector<PixelType> TextureReader::Read(TextureImage2DArray* texture) {
        const int DefaultMipMapLevel = 0 ;

        std::vector<PixelType> pixels ;

        uint32_t textureWidth = texture -> width() ;
        uint32_t textureHeight = texture -> height() ;
        uint32_t textureDepth = texture -> depth() ;
        size_t pixelSize = GetPixelSize(texture -> pixelFormat()) ;

        pixels.resize(textureWidth * textureHeight * textureDepth * pixelSize) ;

        glGetTextureImage(
            texture -> id(),
            DefaultMipMapLevel,
            static_cast<GLenum>(texture -> pixelFormat()),
            static_cast<GLenum>(texture -> pixelDataType()),
            pixels.size(),
            static_cast<void*>(pixels.data())
        ) ;

        return pixels ;
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
}

#endif
