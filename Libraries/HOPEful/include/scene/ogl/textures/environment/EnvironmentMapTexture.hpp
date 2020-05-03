#ifndef __HOPE__GL_ENVIRONMENTMAP_TEXTURE__
#define __HOPE__GL_ENVIRONMENTMAP_TEXTURE__

#include <utils/Platform.hpp>

#include <scene/ogl/textures/environment/Cubemapping.hpp>
#include <scene/common/Color.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <files/images/data/RawImage.hpp>
#include <GL/glew.h>
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

        private:
            /**
             * Generate the texture ID on GPU.
             */
            exported void generateTextureID() ;

            /**
             * Set up the texture.
             */
            exported void setupTexture() ;
    } ;
}

#endif
