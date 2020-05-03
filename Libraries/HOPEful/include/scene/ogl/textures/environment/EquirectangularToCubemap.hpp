#ifndef __HOPE__GL_EQUIRECTANGULAR_TO_CUBEMAP__
#define __HOPE__GL_EQUIRECTANGULAR_TO_CUBEMAP__

#include <utils/Platform.hpp>

#include <scene/ogl/textures/environment/Cubemapping.hpp>
#include <scene/ogl/GLDefines.hpp>
#include <files/images/data/RawImage.hpp>
#include <geometry/points/Point2Df.hpp>
#include <geometry/points/Point3Df.hpp>
#include <GL/glew.h>
#include <array>
#include <functional>

namespace Hope::GL {
    /**
     * Class used to convert a 2:1 equirectangular HDR map to a HDR cubemap.
     */
    class EquirectangularToCubemap final {
        private:
            /**
             * Data type for HDR maps.
             */
            using HDRDataType = float ;

            /**
             * Type of the generated cubemap.
             */
            static const Cubemapping::CubemapType ResultMapType = Cubemapping::Cube_LeftAligned ;

            /**
             * Amount of channels in the HDR maps.
             */
            static const int AmountRGBChannels = 3 ;

            /**
             * Union to easily convert bytes to floats and vice versa.
             * Easier management of channels for looping on them (through array)
             * while processing the map.
             */
            union RGB {
               HDRDataType red ;
               HDRDataType green ;
               HDRDataType blue ;

               HDRDataType array[AmountRGBChannels] ;
               unsigned char bytes[AmountRGBChannels * sizeof(HDRDataType)] ;
            } ;

            /**
             * Pixel values of the loaded map.
             */
            std::vector<RGB> m_equirectPixelChannels ;

            /**
             * Width of the loaded map.
             */
            unsigned int m_equirectWidth ;

            /**
             * Height of the loaded map.
             */
            unsigned int m_equirectHeight ;

            /**
             * Format of the loaded map.
             */
            Spite::ColorFormat m_format ;

            /**
             * Length of an edge of a cube face (width = height).
             */
            unsigned int m_faceEdgeLength = 0 ;

            /**
             * Bytes of the different faces.
             */
            std::array<std::vector<unsigned char>, Cubemapping::AmountFaces> m_faceBytes ;

        public:
            /**
             * Create a new EquirectangularToCubemap instance.
             * @param   equirectData    Data of the loaded map.
             */
            exported EquirectangularToCubemap(Spite::RawImage& equirectData) ;

            /**
             * Run the conversion from equirectangular to cubemap.
             */
            exported void convert() ;

            /**
             * Get the length of a single face in pixels.
             * @return  Length of a single face in pixels.
             */
            exported unsigned int faceSize() const {
                return m_faceEdgeLength ;
            }

            /**
             * Get the bytes of a specific face.
             * @return Bytes of a specific face.
             */
            exported const std::vector<unsigned char>& getFaceBytes(const Cubemapping::CubeFaces face) {
                return m_faceBytes[face] ;
            }

        private:
            /**
             * Get the pixel from the equirectangular map and use bilinear
             * interpolation to fill unmatched pixels on conversion.
             * The values are stored in the cube face pixels.
             * @param   xFrom       U coordinate from the loaded map.
             * @param   yFrom       V coordinate from the loaded map.
             * @param   to          1D coordinates of the pixel to be written.
             * @param   facePixels  Face pixel to write to.
             */
            exported void writeBilinearInterpolation(
                const float xFrom,
                const float yFrom,
                const unsigned int to,
                std::vector<RGB>& facePixels
            ) ;

            /**
             * Cartesian to spherical conversion.
             * @param   u       U coordinate on the loaded map.
             * @param   v       V coordinate on the loaded map.
             * @param   face    Face for which conversion is done.
             */
            exported Mind::Vector3f orientation(
                const float u,
                const float v,
                const Cubemapping::CubeFaces face
            ) ;

            /**
             * Convert 2D coordinates into 1D index in an array.
             * @param   x       X coordinate.
             * @param   y       Y coordinate.
             * @param   width   Array width.
             */
            static exported unsigned int From2DTo1D(
                const unsigned int x,
                const unsigned int y,
                const unsigned int width
            ) {
                return (x + (y * width)) ;
            }
    } ;
}

#endif
