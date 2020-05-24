#ifndef __HOPE__GL_ENVIRONMENTMAP_TEXTURE__
#define __HOPE__GL_ENVIRONMENTMAP_TEXTURE__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>

#include <scene/ogl/textures/environment/CubeFaces.hpp>
#include <scene/ogl/textures/environment/Cubemapping.hpp>
#include <scene/common/Color.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <files/images/data/RawImage.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>
#include <array>

namespace Hope::GL {
    /**
     * An environment map texture is generally used to display sky or a big
     * environment as a texture and illuminate the scene.
     */
    class EnvironmentMapTexture final {
		private:
            /**
             * ID of the texture on GPU side.
             */
            GLuint m_textureID = INVALID_VALUE ;

            /**
             * Dimension of a single face texture.
             */
            Mind::Dimension2Di m_faceDimension ;

        public:
            /**
             * Creation of a new EnvironmentMapTexture.
             * @param   paths   Path to the texture for each face of the cube.
             *                  The expected order of the maps is as follow:
             *                  right, left, top, bottom, back, front.
             */
            exported EnvironmentMapTexture(const std::array<std::string, Cubemapping::AmountFaces>& paths) ;

			/**
			 * Creation of a new EnvironmentMapTexture.
			 * @param 	path	Path to the environment map.
			 */
			exported EnvironmentMapTexture(const std::string& path) ;

            /**
			 * Creation of a new EnvironmentMapTexture.
			 * @param 	input Blob in memory containing the texture data.
			 */
            exported EnvironmentMapTexture(Spite::RawImage& input) ;

            /**
             * Generate an empty EnvironmentMapTexture with predefined edge
             * length of cube faces.
             */
            exported EnvironmentMapTexture(
                const unsigned int cubeSize,
                const bool mipmap = false
            ) ;

            /**
             * Destruction of the EnvironmentMapTexture.
             */
            exported ~EnvironmentMapTexture() ;

            /**
             * Bind the cubemap texture.
             */
            exported void activate() const {
                glActiveTexture(GL_TEXTURE0) ;
            }

            /**
             * Bind the cubemap texture.
             */
            exported void bind() const {
                glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID) ;
            }

            /**
             * Unbind the cubemap texture.
             */
            exported void unbind() const {
                glBindTexture(GL_TEXTURE_CUBE_MAP, 0) ;
            }

            /**
             * Get the texture ID.
             */
            exported GLuint id() const {
                return m_textureID ;
            }

            /**
             * Get the width of a single face.
             */
            exported unsigned int faceWidth() const {
                return m_faceDimension.width() ;
            }

            /**
             * Get the height of a single face.
             */
            exported unsigned int faceHeight() const {
                return m_faceDimension.height() ;
            }

        private:
            /**
             * Generate the texture ID on GPU.
             */
            exported void generateTextureID() ;

            /**
             * Set up the texture.
             * @param mipmap    true to enable mipmapping; false otherwise.
             */
            exported void setupTexture(const bool mipmap = false) ;
    } ;
}

#endif
