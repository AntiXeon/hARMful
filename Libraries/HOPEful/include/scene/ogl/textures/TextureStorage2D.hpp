#ifndef __HOPE__GL_TEXTURE_STORAGE_2D__
#define __HOPE__GL_TEXTURE_STORAGE_2D__

#include <utils/Platform.hpp>

#include <scene/ogl/textures/Texture.hpp>

namespace Hope::GL {
    /**
     * Buffer of a 2D texture. It is compatible with OpenGL4 only.
     * @warning     You cannot load a texture from a file. This texture type is
     *              dedicated for shader writing/editing textures in a proper
     *              and safer manner than framebuffers.
     */
    class TextureStorage2D final : public Texture {
        private:
            /**
             * Size of the texture.
             */
            Mind::Dimension2Di m_size ;

        public:
            /**
             * Amount of coordinates for the TextureImage2D class.
             */
            static const int AmountCoordinates = 2 ;

            /**
             * Create a new TextureStorage2D instance.
             * @param   size            Size of the texture in pixels.
             * @param   internalFormat  Number of color components in the
             *                          texture.
             */
            exported TextureStorage2D(
                const Mind::Dimension2Di& size,
                const InternalFormat internalFormat
            ) ;

            /**
             * Resize the texture.
             * @param   size        The new size to apply.
             * @param   pixelData   Pixel data that fit the new size.
             */
            exported void resize(const Mind::Dimension2Di& size) ;

            /**
             * Set the wrap mode for each dimension of the texture.
             */
            exported void setWrapModes(std::array<WrapMode, AmountCoordinates> modes) ;
    } ;
}

#endif
