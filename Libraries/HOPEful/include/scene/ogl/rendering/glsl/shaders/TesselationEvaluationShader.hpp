#ifndef __HOPE__GL_TESSELATIONEVALUATIONSHADER__
#define __HOPE__GL_TESSELATIONEVALUATIONSHADER__

#include <scene/ogl/rendering/glsl/shaders/Shader.hpp>

namespace Hope::GL {
    /**
     * Represent a tesselation evaluation shader, that can be combined with
     * other shader types into a shader program. It is reusable for other
     * programs as well.
     */
    class TesselationEvaluationShader final : public Shader {
        public:
            /**
             * Create a new TesselationEvaluationShader.
             */
            TesselationEvaluationShader() : Shader( GL_TESS_EVALUATION_SHADER) {}
    } ;
}

#endif
