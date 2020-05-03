#ifndef __HOPE__GL_CUBEMAPPING__
#define __HOPE__GL_CUBEMAPPING__

#include <array>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Common stuff for environment map textures as cubemaps.
     */
    class Cubemapping final {
        public:
            /**
             * Amount of faces on X axis on a cubemap texture.
             */
            static const int AmountCubeFacesX = 4 ;

            /**
             * Amount of faces on Y axis on a cubemap texture.
             */
            static const int AmountCubeFacesY = 3 ;

            /**
             * Relative coordinates in a whole cubemap texture.
             */
            struct CoordsCubeFaces {
                float startX = 0.f ;
                float stopX = 0.f ;
                float startY = 0.f ;
                float stopY = 0.f ;
            } ;

            /**
             * Type of cubemap.
             * Corresponds to the position of the +Y/-Y column alignment.
             */
            enum CubemapType {
                Cube_LeftAligned,
                Cube_FrontAligned,
                Cube_RightAligned,
                Cube_BackAligned
            } ;

            /**
             * Available faces on the cube.
             */
            enum CubeFaces {
                Back = 0,
                Left,
                Front,
                Right,
                Top,
                Bottom,

                First = Back,
                Last = Bottom
            } ;

            /**
             * Amount of faces, and so amount of textures for each face.
             */
            static const int AmountFaces = CubeFaces::Last + 1 ;

            /** Because OpenGL uses top left point as (0,0) for cube maps, instead of the
             * lower left point as for TextureImage2Ds...
             */
            static const bool FlipVerticalAxis = false ;

            /**
             * Get the coordinates to the faces on the cubemap texture.
             * @param type  Type of the loaded cubemap.
             */
            static std::array<CoordsCubeFaces, Cubemapping::AmountFaces> CoordinatesFaces(const CubemapType type) ;

            /**
             * Match between OpenGL coordinates for cube faces and Hope enum.
             * @param face  Face to get OpenGL coordinates of.
             */
            static GLenum GLCoordinates(const CubeFaces face) ;
    } ;
}

#endif
