#ifndef __HOPE__GL_TEXTURE2D__
#define __HOPE__GL_TEXTURE2D__

#include <geometry/dimensions/Dimension2Di.hpp>
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

            /**
             * Pixel format of the texture.
             */
            enum PixelFormat {
                Red = GL_RED,
                RedGreen = GL_RG,
                RedGreenBlue = GL_RGB,
                BlueGreenRed = GL_BGR,
                RedGreenBlueAlpha = GL_RGBA,
                BlueGreenRedAlpha = GL_BGRA,
                RedInteger = GL_RED_INTEGER,
                RedGreenInteger = GL_RG_INTEGER,
                RedGreenBlueInteger = GL_RGB_INTEGER,
                BlueGreenRedInteger = GL_BGR_INTEGER,
                RedGreenBlueAlphaInteger = GL_RGBA_INTEGER,
                BlueGreenRedAlphaInteger = GL_BGRA_INTEGER,
                StencilIndex = GL_STENCIL_INDEX,
                DepthComponent = GL_DEPTH_COMPONENT,
                DepthStencil = GL_DEPTH_STENCIL,
                Depth24Stencil8 = GL_DEPTH24_STENCIL8
            } ;

            /**
             * Indication on the way colors are encoded in memory.
             */
            enum PixelDataType {
                UnsignedByte = GL_UNSIGNED_BYTE,
                Byte = GL_BYTE,
                UnsignedShort = GL_UNSIGNED_SHORT,
                Short = GL_SHORT,
                UnsignedInt = GL_UNSIGNED_INT,
                Int = GL_INT,
                HalfFloat = GL_HALF_FLOAT,
                Float = GL_FLOAT,
                UnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2,
                UnsignedByte233 = GL_UNSIGNED_BYTE_2_3_3_REV,
                UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,
                UnsignedShort565Reversed = GL_UNSIGNED_SHORT_5_6_5_REV,
                UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
                UnsignedShort4444Reversed = GL_UNSIGNED_SHORT_4_4_4_4_REV,
                UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,
                UnsignedShort1555 = GL_UNSIGNED_SHORT_1_5_5_5_REV,
                UnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8,
                UnsignedInt8888Reversed = GL_UNSIGNED_INT_8_8_8_8_REV,
                UnsignedInt1010102 = GL_UNSIGNED_INT_10_10_10_2,
                UnsignedInt2101010 = GL_UNSIGNED_INT_2_10_10_10_REV,
                UnsignedInt248 = GL_UNSIGNED_INT_24_8
            } ;

        private:
            /**
             * ID of the texture on GPU side.
             */
            GLuint m_textureID = INVALID_VALUE ;

            /**
             * Internal format of the texture.
             */
            PixelFormat m_internalFormat ;

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
                const PixelFormat internalFormat,
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

            /**
             * Get the texture ID.
             */
            GLuint id() const {
                return m_textureID ;
            }
    } ;
}

#endif
