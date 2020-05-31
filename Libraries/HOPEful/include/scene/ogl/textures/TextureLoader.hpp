#ifndef __HOPE__GL_TEXTURE_LOADER__
#define __HOPE__GL_TEXTURE_LOADER__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>
#include <scene/ogl/textures/formats/InternalFormats.hpp>
#include <files/images/data/RawImage.hpp>
#include <string>

namespace Hope::GL {
    /**
     * Load a texture.
     */
    class TextureLoader final {
        public:
            /**
             * Load the texture from the provided file.
             * @param   path    Path to the texture file.
             */
            exported static Spite::RawImage LoadFromFile(
                const GLenum target,
                const std::string& path,
                const bool flipVertically
            ) ;

			/**
			 * Convert the SPITE color format to OpenGL internal format.
			 * @param 	format 		The SPITE format to convert.
			 */
			InternalFormat static ConvertInternalColorFormat(
                const Spite::ColorFormat& format,
                const bool standard = true
            ) ;

            /**
             * Convert the SPITE color format to OpenGL one.
             */
            exported static GLenum ConvertColorFormat(const Spite::ColorFormat& format) ;

            /**
             * Convert the SPITE color format to OpenGL data type.
             */
            exported static GLenum ConvertDataType(const Spite::ColorFormat& format) ;
    } ;
}

#endif
