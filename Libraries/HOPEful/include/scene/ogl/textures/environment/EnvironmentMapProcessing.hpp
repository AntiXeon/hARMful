#ifndef __HOPE__GL_ENVIRONMENTMAP_PROCESSING__
#define __HOPE__GL_ENVIRONMENTMAP_PROCESSING__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>

#include <scene/ogl/textures/environment/Cubemapping.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <files/images/data/RawImage.hpp>
#include <geometry/points/Point2Df.hpp>
#include <array>

namespace Hope::GL {
    /**
     * Process the loading of environment maps.
     */
    class EnvironmentMapProcessing final {
        private:
            static const float EquirectangularMapWHRatio ;
            static const float CubeMapWHRatio ;

        public:
            /**
             * Load a raw picture from a file.
             * @param 	path	Path to the environment map.
             * @return Structure containing the raw bytes of the picture file.
             */
            exported static Spite::RawImage LoadRawPicture(const std::string& path) ;

            /**
             * Load an environment map.
             * Its type is found from its aspect ratio.
             * @param input     Image to load.
             */
            exported static void Load(Spite::RawImage& input) ;

        private:
            /**
             * Load an equirectangular (ratio w=2:h=1) and convert it to a
             * cubemap that is then loaded.
             * @param 	rawData  Raw bytes of the uncompressed picture file.
             */
            exported static void LoadEquirectangular21(Spite::RawImage& rawData) ;

            /**
             * Load a cubemap contained in a single image file.
             * @param 	rawData Raw bytes of the uncompressed picture file.
             * @param   type    Type of the cubemap (ie. how are set top and
             *                  bottom tiles).
             */
            exported static void LoadCubemap(
                Spite::RawImage& rawData,
                const Cubemapping::CubemapType type
            ) ;

            /**
             * Load the bytes from a single cube face in GPU memory.
             * @param faceBytes     Raw bytes of the texture.
             * @param format        Format of the texture.
             * @param faceSize      Size of the texture edge (square).
             * @param face          ID of the face on the cube.
             */
            exported static void LoadFace(
                const std::vector<unsigned char>& faceBytes,
                const Spite::ColorFormat& format,
                const unsigned int faceSize,
                const Cubemapping::CubeFaces face
            ) ;

            /**
             * Get the pixels corresponding to a single cube face.
             * @param 	face 		Face of the cubemap to get.
             * @param 	pictureData	Data of the whole picture to split.
             * @param 	outPixels	Output pixels data of the face.
             */
            exported static void ReadCubeFace(
                const Cubemapping::CubemapType type,
                const Cubemapping::CubeFaces face,
                Spite::RawImage& pictureData,
                std::vector<unsigned char>& outPixels
            ) ;
    } ;
}

#endif
