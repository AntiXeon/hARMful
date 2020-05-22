#ifndef __HOPE__GL_CUBE_FACES__
#define __HOPE__GL_CUBE_FACES__

#include <HopeAPI.hpp>

namespace Hope::GL {
    /**
     * Comparison operators.
     */
    enum CubeFace : GLint {
        Right = GL_TEXTURE_CUBE_MAP_POSITIVE_X ,
        Left = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        Top = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        Bottom = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        Back = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        Front = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,

        First = Right,
        Last = Front
    } ;
}

#endif
