#ifndef __HOPE__GL_COMPUTESHADER__
#define __HOPE__GL_COMPUTESHADER__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/glsl/shaders/Shader.hpp>

namespace Hope::GL {
    /**
     * Represent a compute shader.
     * A compute shader is not directly included in a shader pipeline but can be
     * used to perform some computations on a GPU. For example: generate a
     * texture from a procedural method, run some algorithms that require a lot
     * of parallel computations, etc.
     */
    class ComputeShader final : public Shader {
        public:
            /**
             * Create a new ComputeShader.
             */
            exported ComputeShader() : Shader(GL_COMPUTE_SHADER) {}
    } ;
}

#endif
