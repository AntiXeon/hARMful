#ifndef __HOPE__OPENGL_UBO_SHARED_DATA__
#define __HOPE__OPENGL_UBO_SHARED_DATA__

#include <scene/ogl/rendering/glsl/ubo/BaseGLSLDataUBO.hpp>
#include <scene/ogl/rendering/glsl/ubo/ModelGLSLDataUBO.hpp>
#include <scene/ogl/rendering/glsl/ubo/LightGLSLDataUBO.hpp>
#include <scene/SceneCache.hpp>

namespace Hope::GL {
    class UBOSharedData final {
        private:
            /**
             * UBO containing the base data for GLSL shaders.
             */
            BaseGLSLDataUBO* m_baseUBO = nullptr ;

            /**
             * UBO containing the base data of a model for GLSL shaders.
             */
            ModelGLSLDataUBO* m_modelUBO = nullptr ;

            /**
             * UBO containing data for lighting for GLSL shaders.
             */
            LightGLSLDataUBO* m_lightUBO = nullptr ;

        public:
            /**
             * Create a new UBOSharedData instance.
             */
            UBOSharedData() ;

            /**
             * Destruction of the UBOSharedData.
             */
            ~UBOSharedData() ;

            /**
             * Update the light UBO if needed.
             */
            void updateLightUBO(const SceneCache* cache) ;

            /**
             * Update the model UBO.
             */
            void updateModelUBO(
                Mind::Matrix4x4f& modelMatrix,
                Mind::Matrix4x4f& viewMatrix,
                Mind::Matrix4x4f& projectionMatrix
            ) ;

            /**
             * Get the UBO containing the base data for GLSL shaders.
             */
            BaseGLSLDataUBO* base() const {
                return m_baseUBO ;
            }

            /**
             * Get the UBO containing the base data of a model for GLSL shaders.
             */
            ModelGLSLDataUBO* model() const {
                return m_modelUBO ;
            }

            /**
             * Get the UBO containing data for lighting for GLSL shaders.
             */
            LightGLSLDataUBO* light() const {
                return m_lightUBO ;
            }
    } ;
} ;

#endif
