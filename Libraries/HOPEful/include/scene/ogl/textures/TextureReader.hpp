#ifndef __HOPE__GL_TEXTURE_READER__
#define __HOPE__GL_TEXTURE_READER__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>

#include <scene/ogl/textures/TextureImage2D.hpp>
#include <scene/ogl/textures/TextureImage2DArray.hpp>
#include <scene/ogl/textures/environment/EnvironmentMapTexture.hpp>
#include <scene/ogl/textures/formats/PixelFormats.hpp>
#include <files/images/data/RawImage.hpp>
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
             */
            exported static Spite::RawImage Read(
                TextureImage2D* texture,
                const unsigned int mipmapLevel = 0
            ) ;

            /**
             * Read the content of a EnvironmentMapTexture.
             */
            exported static Spite::RawImage Read(
                EnvironmentMapTexture* texture,
                CubeFace face,
                const unsigned int mipmapLevel = 0
            ) ;

        private:
            /**
             * Get the size of a single pixel.
             */
            exported static size_t GetPixelSize(const PixelFormat pixelFormat) ;

            /**
             * Get the size of a single pixel.
             */
            exported static Spite::ColorFormat::ID GetColorFormatID(const PixelFormat pixelFormat) ;
    } ;
}

#endif
