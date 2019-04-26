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
            ModelGLSLDataUBO(const GLuint bindingPointIndex) ;

            /**
             * Set the model matrix value.
             */
            void setModelMatrix(const Mind::Matrix4x4f& mat) {
                m_data.modelMatrix = mat.toArray() ;
            }

            /**
             * Set the model view matrix value.
             */
            void setModelViewMatrix(const Mind::Matrix4x4f& mat) {
                m_data.modelViewMatrix = mat.toArray() ;
            }

            /**
             * Set the model view projection matrix value.
             */
            void setMVPMatrix(const Mind::Matrix4x4f& mat) {
                m_data.mvpMatrix = mat.toArray() ;
            }

            /**
             * Set the inverse model matrix value.
             */
            void setInverseModelMatrix(const Mind::Matrix4x4f& mat) {
                m_data.inverseModelMatrix = mat.toArray() ;
            }

            /**
             * Set the inverse model view matrix value.
             */
            void setInverseModelViewMatrix(const Mind::Matrix4x4f& mat) {
                m_data.inverseModelViewMatrix = mat.toArray() ;
            }

            /**
             * Set the inverse model view projection matrix value.
             */
            void setInverseMVPMatrix(const Mind::Matrix4x4f& mat) {
                m_data.inverseMVPMatrix = mat.toArray() ;
            }

            /**
             * Set the normal matrix value.
             */
            void setNormalMatrix(const Mind::Matrix4x4f& mat) {
                m_data.normalMatrix = mat.toArray() ;
            }

            /**
             * Set the model normal matrix value.
             */
            void setModelNormalMatrix(const Mind::Matrix4x4f& mat) {
                m_data.modelNormalMatrix = mat.toArray() ;
            }

            /**
             * Set the model view normal matrix value.
             */
            void setModelViewNormalMatrix(const Mind::Matrix4x4f& mat) {
                m_data.modelViewNormalMatrix = mat.toArray() ;
            }

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
