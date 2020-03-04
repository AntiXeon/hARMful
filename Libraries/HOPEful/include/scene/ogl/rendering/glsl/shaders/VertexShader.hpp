#ifndef __HOPE__GL_VERTEXSHADER__
#define __HOPE__GL_VERTEXSHADER__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/glsl/shaders/Shader.hpp>

namespace Hope::GL {
    /**
     * Represent a vertex shader, that can be combined with other shader types
     * into a shader program. It is reusable for other programs as well.
     */
    class VertexShader final : public Shader {
        public:
            /**
             * Create a new VertexShader.
             */
            exported VertexShader() : Shader(GL_VERTEX_SHADER) {}
    } ;
}

#endif
