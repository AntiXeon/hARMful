#ifndef __HOPE__GL_CUBEMAP_TEXTURE__
#define __HOPE__GL_CUBEMAP_TEXTURE__

#include <utils/Platform.hpp>

#include <scene/common/Color.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <files/images/data/RawImage.hpp>
#include <GL/glew.h>
#include <array>

namespace Hope::GL {
    /**
     * A Cubemap texture is generally used to display sky or a big environment
     * as a texture.
     */
    class CubemapTexture final {
        public:
            /**
             * Amount of faces, and so amount of textures for each face.
             */
            static const int AmountFaces = 6 ;

            /**
             * Available faces on the cube.
             */
            enum CubeFaces {
                Right = 0,
                Left,
                Top,
                Bottom,
                Back,
                Front
            } ;

        private:
            /**
             * ID of the texture on GPU side.
             */
            GLuint m_textureID = INVALID_VALUE ;

        public:
            /**
             * Creation of a new CubemapTexture.
             * @param   paths   Path to the texture for each face of the cube.
             *                  The expected order of the maps is as follow:
             *                  right, left, top, bottom, back, front.
             */
            exported CubemapTexture(std::array<std::string, AmountFaces> paths) ;

            /**
             * Destruction of the CubemapTexture.
             */
            exported ~CubemapTexture() ;

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
    } ;
}

#endif
