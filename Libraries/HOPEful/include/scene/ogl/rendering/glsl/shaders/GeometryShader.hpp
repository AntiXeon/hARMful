#ifndef __HOPE__GL_GEOMETRYSHADER__
#define __HOPE__GL_GEOMETRYSHADER__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/glsl/shaders/Shader.hpp>

namespace Hope::GL {
    /**
     * Represent a geometry shader, that can be combined with other shader types
     * into a shader program. It is reusable for other programs as well.
     */
    class GeometryShader final : public Shader {
        public:
            /**
             * Create a new GeometryShader.
             */
            exported GeometryShader() : Shader(GL_GEOMETRY_SHADER) {}
    } ;
}

#endif
