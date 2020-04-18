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
		private:
			/** Because OpenGL uses top left point as (0,0) for cube maps, instead of the
	         * lower left point as for TextureImage2Ds...
			 */
	        static const bool FlipVerticalAxis = false ;

			static const int AmountCubeFacesX = 4 ;
			static const int AmountCubeFacesY = 3 ;

			struct CoordsCubeFaces {
				float startX = 0.f ;
				float startY = 0.f ;

				float stopX = 0.f ;
				float stopY = 0.f ;
			} ;

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

			/**
			 * Texture type to be loaded.
			 */
			enum TextureType {
				Equirectangular,
				Cubemap
			} ;

        private:
			static const std::array<CoordsCubeFaces, AmountFaces> CoordinatesFaces ;

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
            exported CubemapTexture(const std::array<std::string, AmountFaces>& paths) ;

			/**
			 * Creation of a new CubemapTexture.
			 * @param 	path	Path to the environment map.
			 * @param 	type 	Type of the environment map.
			 */
			exported CubemapTexture(
				const std::string& path,
				const TextureType type
			) ;

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

		private:
			/**
			 * Load a raw picture from a file.
			 * @param 	path	Path to the environment map.
			 * @param 	rawData Structure containing the raw bytes of the
			 *					picture file.
			 */
			exported void loadRawPicture(
				const std::string& path,
				Spite::RawImage& rawData
			) ;

			/**
			 * Load a cubemap contained in a single image file.
			 * @param 	path	Path to the environment map.
			 */
			exported void loadCubemap(const std::string& path) ;

			/**
			 * Get the pixels corresponding to a single cube face.
			 * @param 	face 		Face of the cubemap to get.
			 * @param 	pictureData	Data of the whole picture to split.
			 * @param 	outPixels	Output pixels data of the face.
			 */
			exported void readCubeFace(
				const CubeFaces face,
				Spite::RawImage& pictureData,
				std::vector<unsigned char>& outPixels
			) ;
    } ;
}

#endif
