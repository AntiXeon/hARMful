#ifndef __HOPE__GL_TEXTURE2D__
#define __HOPE__GL_TEXTURE2D__

#include <scene/common/Color.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <GL/glew.h>
#include <array>

namespace Hope::GL {
    /**
     * Buffer of a texture 2D.
     */
    class Texture2D final {
        public:
            /**
             * Amount of coordinates for the Texture2D class.
             */
            static const int AmountCoordinates = 2 ;

        private:
            /**
             * ID of the texture on GPU side.
             */
            GLuint m_textureID = INVALID_VALUE ;

        public:
            /**
             * Create a new Texture2D instance.
             * @param   path    Path to the texture file. The file is internally
             *                  loaded.
             */
            Texture2D(const std::string& path) ;

            /**
             * Create a new Texture2D instance.
             * @param   pixelData       Raw data of the texture.
             * @param   width           Width of the texture in pixels.
             * @param   height          Height of the texture in pixels.
             * @param   internalFormat  Number of color components in the
             *                          texture.
             * @param   pixelFormat     Format of the pixel data.
             * @param   pixelDataType   Data type of the pixel data.
             */
            Texture2D(
                const float* pixelData,
                const uint32_t width,
                const uint32_t height,
                const GLint internalFormat,
                const GLenum pixelFormat,
                const GLenum pixelDataType
            ) ;

            /**
             * Destruction of the Texture2D.
             */
            ~Texture2D() ;

            /**
             * Set the current texture active.
             */
            void activate(const unsigned short unit) const {
                glActiveTexture(GL_TEXTURE0 + unit) ;
            }

            /**
             * Bind the current texture.
             */
            void bind() const {
                glBindTexture(GL_TEXTURE_2D, m_textureID) ;
            }

            /**
             * Unbind the texture.
             */
            void unbind() const {
                glBindTexture(GL_TEXTURE_2D, 0) ;
            }

            /**
             * Set the wrap mode for each dimension of the texture.
             */
            void setWrapModes(std::array<GLint, AmountCoordinates> modes) ;

            /**
             * Set the border color in case the texture does not fit the borders
             * of the polygons.
             */
            void setBorderColor(const Hope::Color& color) ;

            /**
             * Set the texture filtering options.
             * @param   downscaling Filter option when the texture is
             *                      downscaled.
             * @param   upscaling   Filter option when the texture is upscaled.
             */
            void setFiltering(
                GLint downscaling,
                GLint upscaling
            ) ;
    } ;
}

#endif
