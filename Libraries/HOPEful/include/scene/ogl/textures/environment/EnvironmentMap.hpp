#ifndef __HOPE__GL_ENVIRONMENTMAP__
#define __HOPE__GL_ENVIRONMENTMAP__

namespace Hope::GL {
    namespace EnvironmentMap {
        /**
         * Available faces on the cube.
         */
        enum CubeFaces {
            Right = 0,
            Left,
            Top,
            Bottom,
            Front,
            Back
        } ;

        /**
         * Texture type to be loaded.
         */
        enum TextureType {
            Equirectangular,
            Cubemap
        } ;

        /**
         * Amount of faces, and so amount of textures for each face.
         */
        static const int AmountFaces = 6 ;

        /** Because OpenGL uses top left point as (0,0) for cube maps, instead of the
         * lower left point as for TextureImage2Ds...
         */
        static const bool FlipVerticalAxis = false ;
    }
}

#endif
