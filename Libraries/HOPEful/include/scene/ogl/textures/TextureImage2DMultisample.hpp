#ifndef __HOPE__GL_TEXTURE_IMAGE_2D_MULTISAMPLE__
#define __HOPE__GL_TEXTURE_IMAGE_2D_MULTISAMPLE__

#include <utils/Platform.hpp>

#include <scene/ogl/textures/Texture.hpp>
#include <array>

namespace Hope::GL {
    /**
     * Buffer of a 2D texture with multisample support. It is compatible with
     * modern OpenGL versions only.
     * @warning:    This texture cannot be used in GLSL with texture
     *              load/store functions! Use TextureStorage2D instead for a
     *              such need.
     */
    class TextureImage2DMultisample final : public Texture {
        public:
            /**
             * Amount of coordinates for the TextureImage2DMultisample class.
             */
            static const int AmountCoordinates = 2 ;

        private:
            /**
             * Size of the texture.
             */
            Mind::Dimension2Di m_size ;

            /**
             * Automatic mipmap generation if true.
             */
            bool m_mipmap ;

            /**
             *Number of samples in the multisample texture's image.
             */
            int m_samples ;

            /**
             * Specifies whether the image will use identical sample locations
             * and the same number of samples for all texels in the image, and
             * the sample locations will not depend on the internal format or
             * size of the image.
             */
            bool m_fixedSampleLocation = true ;

        public:
            /**
             * Create a new TextureImage2D instance.
             * @param   size            Size of the texture in pixels.
             * @param   internalFormat  Number of color components in the
             *                          texture.
             * @param   samples         Number of samples in the multisample
             *                          texture's image.
             * @param   fixedSampleLocation     Specifies whether the image will
             *                                  use identical sample locations
             *                                  and the same number of samples
             *                                  for all texels in the image,
             *                                  and the sample locations will
             *                                  not depend on the internal
             *                                  format or size of the image.
             */
            exported TextureImage2DMultisample(
                const Mind::Dimension2Di& size,
                const InternalFormat internalFormat,
                const int samples = 4,
                const bool fixedSampleLocation = true
            ) ;

            /**
             * Resize the texture.
             * @param   size        The new size to apply.
             */
            exported void resize(const Mind::Dimension2Di& size) ;

            /**
             * Set the wrap mode for each dimension of the texture.
             */
            exported void setWrapModes(std::array<WrapMode, AmountCoordinates> modes) ;
    } ;
}

#endif
