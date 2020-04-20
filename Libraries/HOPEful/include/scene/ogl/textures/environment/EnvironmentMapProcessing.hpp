#ifndef __HOPE__GL_ENVIRONMENTMAP_PROCESSING__
#define __HOPE__GL_ENVIRONMENTMAP_PROCESSING__

#include <utils/Platform.hpp>

#include <scene/ogl/textures/environment/EnvironmentMap.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <files/images/data/RawImage.hpp>
#include <GL/glew.h>
#include <array>

namespace Hope::GL {
    class EnvironmentMapProcessing final {
        private:
            static const int AmountCubeFacesX = 4 ;
			static const int AmountCubeFacesY = 3 ;

            struct RGB {
                float r ;
                float g ;
                float b ;
            } ;

			struct CoordsCubeFaces {
				float startX = 0.f ;
				float startY = 0.f ;

				float stopX = 0.f ;
				float stopY = 0.f ;
			} ;

            static const std::array<CoordsCubeFaces, EnvironmentMap::AmountFaces> CoordinatesFaces ;

            static const int AmountInterpolationCorners = 4 ;

        public:
            /**
             * Load a cubemap contained in a single image file.
             * @param 	path	Path to the environment map.
             */
            exported static void LoadCubemap(const std::string& path) ;

        private:
            /**
             * Load a raw picture from a file.
             * @param 	path	Path to the environment map.
             * @param 	rawData Structure containing the raw bytes of the
             *					picture file.
             */
            exported static void LoadRawPicture(
                const std::string& path,
                Spite::RawImage& rawData
            ) ;

            /**
             * Get the pixels corresponding to a single cube face.
             * @param 	face 		Face of the cubemap to get.
             * @param 	pictureData	Data of the whole picture to split.
             * @param 	outPixels	Output pixels data of the face.
             */
            exported static void ReadCubeFace(
                const EnvironmentMap::CubeFaces face,
                Spite::RawImage& pictureData,
                std::vector<unsigned char>& outPixels
            ) ;
    } ;
}

#endif
