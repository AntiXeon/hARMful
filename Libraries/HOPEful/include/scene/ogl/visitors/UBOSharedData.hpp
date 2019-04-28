#ifndef __HOPE__OPENGL_UBO_SHARED_DATA__
#define __HOPE__OPENGL_UBO_SHARED_DATA__

#include <scene/ogl/rendering/glsl/ubo/BaseGLSLDataUBO.hpp>
#include <scene/ogl/rendering/glsl/ubo/ModelGLSLDataUBO.hpp>
#include <scene/ogl/rendering/glsl/ubo/LightGLSLDataUBO.hpp>

namespace Hope::GL {
    class FrameRenderCache ;

    class UBOSharedData final {
        private:
            /**
             * UBO containing the base data for GLSL shaders.
             */
            BaseGLSLDataUBO m_baseUBO ;

            /**
             * UBO containing data for lighting for GLSL shaders.
             */
            LightGLSLDataUBO m_lightUBO ;

        public:
            /**
             * Update the light UBO if needed.
             */
            void updateLightUBO(const FrameRenderCache& cache) ;

            /**
             * Get the UBO containing the base data for GLSL shaders.
             */
            BaseGLSLDataUBO& base() {
                return m_baseUBO ;
            }

            /**
             * Get the UBO containing data for lighting for GLSL shaders.
             */
            LightGLSLDataUBO& light() {
                return m_lightUBO ;
            }
    } ;
} ;

#endif
