#ifndef __HOPE__GL_FILTER_MODES__
#define __HOPE__GL_FILTER_MODES__

#include <HopeAPI.hpp>

namespace Hope::GL {
    /**
     * Filter modes operators.
     */
    enum FilterMode : GLint {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
        Nearest_MipNearest = GL_NEAREST_MIPMAP_NEAREST,
        Linear_MipNearest = GL_LINEAR_MIPMAP_NEAREST,
        Nearest_MipLinear = GL_NEAREST_MIPMAP_LINEAR,
        Linear_MipLinear = GL_LINEAR_MIPMAP_LINEAR
    } ;
}

#endif
