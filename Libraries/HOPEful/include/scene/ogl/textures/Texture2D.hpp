#ifndef __HOPE__GL_TEXTURE2D__
#define __HOPE__GL_TEXTURE2D__

#include <scene/ogl/textures/formats/InternalFormats.hpp>
#include <scene/ogl/textures/formats/PixelFormats.hpp>
#include <scene/ogl/textures/formats/PixelDataTypes.hpp>
#include <scene/ogl/textures/formats/ComparisonOperators.hpp>
#include <scene/ogl/textures/formats/WrapModes.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>
#include <scene/common/Color.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <GL/glew.h>
#include <array>

namespace Hope::GL {
    /**
     * Buffer of a 2D texture.
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

            /**
             * Internal format of the texture.
             */
            InternalFormat m_internalFormat ;

            /**
             * Pixel format of the input data.
             */
            PixelFormat m_pixelFormat ;

            /**
             * The way colors are encoded in memory the texture.
             */
            PixelDataType m_pixelDataType ;

            /**
             * Automatic mipmap generation if true.
             */
            bool m_mipmap ;

        public:
            /**
             * Create a new Texture2D instance.
             * @param   path    Path to the texture file. The file is internally
             *                  loaded.
             * @param   mipmap  Generate the mipmaps if true.
             */
            Texture2D(
                const std::string& path,
                const bool mipmap = true
            ) ;

            /**
             * Create a new Texture2D instance.
             * @param   size            Size of the texture in pixels.
             * @param   internalFormat  Number of color components in the
             *                          texture.
             * @param   pixelFormat     Format of the pixel data.
             * @param   pixelDataType   Data type of the pixel data.
             * @param   pixelData       Raw data of the texture.
             *                          nullptr is a valid value, for example to
             *                          use the texture as a framebuffer texture
             *                          attachments.
             * @param   mipmap          Generate the mipmaps if true.
             */
            Texture2D(
                const Mind::Dimension2Di& size,
                const InternalFormat internalFormat,
                const PixelFormat pixelFormat,
                const PixelDataType pixelDataType,
                const float* pixelData = nullptr,
                const bool mipmap = true
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
             * Bind texture unit.
             */
            void bindUnit(const unsigned int unit) const {
                glBindTextureUnit(unit, m_textureID) ;
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
             * Unbind texture unit.
             */
            void unbindUnit(const unsigned int unit) const {
                glBindTextureUnit(unit, 0) ;
            }

            /**
             * Resize the texture.
             * @param   size        The new size to apply.
             * @param   pixelData   Pixel data that fit the new size.
             */
            void resize(
                const Mind::Dimension2Di& size,
                const float* pixelData = nullptr
            ) ;

            /**
             * Set the wrap mode for each dimension of the texture.
             */
            void setWrapModes(std::array<WrapMode, AmountCoordinates> modes) ;

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

            /**
             * Set the comparison mode.
             * @param   compare     If true, specifies that the interpolated and
             *                      clamped r texture coordinate should be
             *                      compared to the value in the currently bound
             *                      depth texture.
             *                      If false, specifies that the luminance,
             *                      intensity, or alpha (as specified by
             *                      GL_DEPTH_TEXTURE_MODE) should be assigned
             *                      the appropriate value from the currently
             *                      bound depth texture.
             */
            void setCompareRedToTexture(const bool compare) {
                GLint comparison = GL_NONE ;

                if (compare) {
                    comparison = GL_COMPARE_R_TO_TEXTURE ;
                }

                glTexParameteri(
                    GL_TEXTURE_2D,
                    GL_TEXTURE_COMPARE_MODE,
                    comparison
                ) ;
            }

            /**
             * Set the comparison operator.
             */
            void setComparisonOperator(const ComparisonOperator op) {
                glTexParameteri(
                    GL_TEXTURE_2D,
                    GL_TEXTURE_COMPARE_FUNC,
                    op
                ) ;
            }

            /**
             * Get the texture ID.
             */
            GLuint id() const {
                return m_textureID ;
            }
    } ;
}

#endif
