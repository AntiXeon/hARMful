#ifndef __HOPE__GL_WRAP_MODES__
#define __HOPE__GL_WRAP_MODES__

#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Wrap modes operators.
     */
    enum WrapMode : GLint {
        ClampToBorder = GL_CLAMP_TO_BORDER,
        ClampToEdge = GL_CLAMP_TO_EDGE,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        Repeat = GL_REPEAT
    } ;
}

#endif
