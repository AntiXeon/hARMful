#ifndef __HOPE__GL_TEXTURE_LOADER__
#define __HOPE__GL_TEXTURE_LOADER__

#include <utils/Platform.hpp>

#include <files/images/data/RawImage.hpp>
#include <GL/glew.h>
#include <string>

namespace Hope::GL {
    /**
     * Load a texture.
     */
    class TextureLoader final {
        private:
            /**
             * Supported image file types.
             */
            enum ImageFileType {
                JPEG,
                PNG,
                Unknown
            } ;

        public:
            /**
             * Load the texture from the provided file.
             * @param   path    Path to the texture file.
             */
            exported static void LoadFromFile(
                const GLenum target,
                const std::string& path,
                const bool flipVertically
            ) ;

        private:
            /**
             * Load a JPEG file.
             * Pixel data are stored in the raw image data.
             */
            exported static void LoadJPEG(
                const std::string& path,
                Spite::RawImage& rawData,
                const bool flipVertically
            ) ;

            /**
             * Load a PNG file.
             * Pixel data are stored in the raw image data.
             */
            exported static void LoadPNG(
                const std::string& path,
                Spite::RawImage& rawData,
                const bool flipVertically
            ) ;

            /**
             * Get the type of file.
             */
            exported static ImageFileType Type(const std::string& path) ;

            /**
             * Convert the SPITE color format to OpenGL one.
             */
            exported static GLenum ConvertColorFormat(const Spite::ColorFormat::ID format) ;
    } ;
}

#endif
