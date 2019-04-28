#ifndef __HOPE__GL_MODEL_DATA_UNIFORM_BUFFER_OBJECT__
#define __HOPE__GL_MODEL_DATA_UNIFORM_BUFFER_OBJECT__

#include <scene/ogl/rendering/glsl/ubo/UniformBufferObject.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <array>

namespace Hope::GL {
    /**
     * UBO containing all the base data that are sent to every shader (model,
     * view, projection matrices, etc).
     */
    class ModelGLSLDataUBO final : public UniformBufferObject {
        private:
            /**
             * The structure of the data that are set in the UBO.
             */
            struct ShaderData {
                std::array<float, Mind::Matrix4x4f::MatrixSize> modelMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> modelViewMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> mvpMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> inverseModelMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> inverseModelViewMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> inverseMVPMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> normalMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> modelNormalMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> modelViewNormalMatrix ;
            } m_data ;

        public:
            /**
             * Create a new ModelGLSLDataUBO instance.
             */
            ModelGLSLDataUBO() ;

            /**
             * Fill the matrices of the UBO.
             */
            void setMatrices(
                const Mind::Matrix4x4f& modelMatrix,
                const Mind::Matrix4x4f& viewMatrix,
                const Mind::Matrix4x4f& projectionMatrix
            ) ;

        protected:
            /**
             * Get the data of the UBO.
             */
            const void* data() const override {
                return static_cast<const void*>(&m_data) ;
            }

            /**
             * Size of the data.
             */
            size_t size() const override {
                return sizeof(m_data) ;
            }
    } ;
}

#endif
