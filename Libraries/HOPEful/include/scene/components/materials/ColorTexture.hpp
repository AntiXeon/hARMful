#ifndef __HOPE__COLOR_TEXTURE_STRUCT__
#define __HOPE__COLOR_TEXTURE_STRUCT__

#include <utils/Platform.hpp>
#include <scene/common/Color.hpp>

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/textures/TextureImage2D.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * Aggregate color, texture and the possibility to mix both of them in a
	 * shader.
     */
    class ColorTexture {
        private:
			/**
			 * Use texture percentage. Must be set between 0 (only color) and 1
			 * (only texture).
			 */
			float m_texturePercentage = 0.f ;

			/**
			 * Color to use.
			 */
			Color m_color = Color(0.f, 0.f, 0.f, 0.f) ;

			/**
             * Texture to use.
             */
            std::unique_ptr<API::TextureImage2D> m_texture = nullptr ;

		public:
			/**
			 * Bind the content to the shader.
			 * @param colorBinding		Binding of the color in the shader.
			 * @param textureBinding	Binding of the texture in the shader.
			 * @param percentageBinding	Binding of the texture percentage in the
			 *							shader.
			 */
			exported void bind(
				unsigned short colorBinding,
				unsigned short textureBinding,
				unsigned short percentageBinding
			) ;

			/**
			 * Set the texture percentage of use.
			 * @param percentage	Percentage of the texture value to use over
			 *						color. Must be set between 0 (only color)
			 *						and 1 (only texture).
			 */
			exported void setTexturePercentage(const float percentage) {
				m_texturePercentage = std::clamp(percentage, 0.f, 1.f) ;
			}

			/**
			 * Set the color.
			 * @param color		Color to use.
			 */
			exported void setColor(const Color& color) {
				m_color = color ;
			}

			/**
			 * Set the texture.
			 * @param texture	Texture to use.
			 */
			exported void setTexture(std::unique_ptr<API::TextureImage2D> texture) {
				m_texture = std::move(texture) ;
			}

			/**
			 * Get the texture percentage of use.
			 * @return 	Percentage value (between 0 - only color - and 1 - only
			 *			texture).
			 */
			exported float texturePercentage() const {
				return m_texturePercentage ;
			}

			/**
			 * Get the color.
			 * @return Color to use.
			 */
			exported const Color& color() const {
				return m_color ;
			}

			/**
			 * Get the texture.
			 * @return Texture to use.
			 */
			exported const API::TextureImage2D* texture() const {
                return m_texture.get() ;
            }
	} ;
}

#endif
