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
             * Convert the SPITE color format to OpenGL one.
             */
            exported static GLenum ConvertColorFormat(const Spite::ColorFormat::ID format) ;
    } ;
}

#endif
