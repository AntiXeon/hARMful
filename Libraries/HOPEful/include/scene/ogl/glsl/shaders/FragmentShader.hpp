#ifndef __HOPE__GL_FRAGMENTSHADER__
#define __HOPE__GL_FRAGMENTSHADER__

#include <scene/ogl/glsl/shaders/Shader.hpp>

namespace Hope::GL {
    /**
     * Represent a fragment shader, that can be combined with other shader types
     * into a shader program. It is reusable for other programs as well.
     */
    class FragmentShader final : public Shader {
        public:
            /**
             * Create a new FragmentShader.
             */
            FragmentShader() : Shader(GL_FRAGMENT_SHADER) {}
    } ;
}

#endif
