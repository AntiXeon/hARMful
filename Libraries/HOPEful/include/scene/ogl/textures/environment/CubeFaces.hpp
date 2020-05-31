#ifndef __HOPE__GL_CUBE_FACES__
#define __HOPE__GL_CUBE_FACES__

#include <HopeAPI.hpp>
#include <string>

namespace Hope::GL {
    enum CubeFace : GLenum {
        Right = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        Left = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        Top = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        Bottom = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        Back = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        Front = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,

        First = Right,
        Last = Front
    } ;

    /**
     * Amount of faces in a cubemap.
     */
    extern const unsigned int AmountFaces ;

    /**
     * Get the name of a face.
     */
    const std::string& FaceName(const Hope::GL::CubeFace face) ;
}

#endif
