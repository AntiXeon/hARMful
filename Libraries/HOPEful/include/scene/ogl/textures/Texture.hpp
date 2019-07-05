#ifndef __HOPE__GL_TEXTURE__
#define __HOPE__GL_TEXTURE__

#include <scene/ogl/textures/formats/InternalFormats.hpp>
#include <scene/ogl/textures/formats/PixelFormats.hpp>
#include <scene/ogl/textures/formats/PixelDataTypes.hpp>
#include <scene/ogl/textures/formats/ComparisonOperators.hpp>
#include <scene/ogl/textures/formats/WrapModes.hpp>
#include <geometry/dimensions/Dimension3Di.hpp>
#include <scene/common/Color.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Base class for OpenGL textures.
     */
    class Texture {
        private:
            /**
             * Target to which the texture is bound.
             */
            GLenum m_target ;

            /**
             * ID of the texture on GPU side.
             */
            GLuint m_textureID = INVALID_VALUE ;

            /**
             * Internal format of the texture.
             */
            InternalFormat m_internalFormat ;

        public:
            /**
             * Create a new Texture instance.
             * @param   target  Target to which the texture is bound.
             */
            Texture(const GLenum target) ;

            /**
             * Create a new Texture instance.
             * @param   target          Target to which the texture is bound.
             * @param   internalFormat  Number of color components in the
             *                          texture.
             */
            Texture(
                const GLenum target,
                const InternalFormat internalFormat
            ) ;

            /**
             * Destruction of the Texture.
             */
            ~Texture() ;

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
                glBindTexture(m_target, m_textureID) ;
            }

            /**
             * Unbind the texture.
             */
            void unbind() const {
                glBindTexture(m_target, 0) ;
            }

            /**
             * Unbind texture unit.
             */
            void unbindUnit(const unsigned int unit) const {
                glBindTextureUnit(unit, 0) ;
            }

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
            void setCompareRefToTexture(const bool compare) ;

            /**
             * Set the comparison operator.
             */
            void setComparisonOperator(const ComparisonOperator op) ;

            /**
             * Get the target of the texture.
             */
            GLenum target() const {
                return m_target ;
            }

            /**
             * Get the texture ID.
             */
            GLuint id() const {
                return m_textureID ;
            }

            /**
             * Get the internal format of the texture.
             */
            InternalFormat internalFormat() const {
                return m_internalFormat ;
            }
    } ;
}

#endif
