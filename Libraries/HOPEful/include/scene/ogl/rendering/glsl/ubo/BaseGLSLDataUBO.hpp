#ifndef __HOPE__GL_BASE_DATA_UNIFORM_BUFFER_OBJECT__
#define __HOPE__GL_BASE_DATA_UNIFORM_BUFFER_OBJECT__

#include <scene/ogl/rendering/glsl/ubo/UniformBufferObject.hpp>
#include <geometry/points/Point3Df.hpp>
#include <matrices/Matrix3x3f.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <array>

namespace Hope::GL {
    /**
     * UBO containing all the base data that are sent to every shader (model,
     * view, projection matrices, etc).
     */
    class BaseGLSLDataUBO final : public UniformBufferObject {
        private:
            /**
             * The structure of the data that are set in the UBO.
             */
            struct ShaderData {
                std::array<float, 16> viewMatrix ;
                std::array<float, 16> projectionMatrix ;
                std::array<float, 16> viewProjectionMatrix ;
                std::array<float, 16> inverseViewMatrix ;
                std::array<float, 16> inverseProjectionMatrix ;
                std::array<float, 16> inverseViewProjectionMatrix ;
                std::array<float, 9> viewportMatrix ;
                std::array<float, 9> inverseViewportMatrix ;
                float aspectRatio ;
                float time ;
                std::array<float, 3> eyePosition ;
            } m_data ;

        public:
            /**
             * Create a new BaseGLSLDataUBO instance.
             */
            BaseGLSLDataUBO(const GLuint bindingPointIndex) ;

            /**
             * Set the view matrix value.
             */
            void setViewMatrix(const Mind::Matrix4x4f& mat) {
                m_data.viewMatrix = mat.toArray() ;
            }

            /**
             * Set the projection matrix value.
             */
            void setProjectionMatrix(const Mind::Matrix4x4f& mat) {
                m_data.projectionMatrix = mat.toArray() ;
            }

            /**
             * Set the view projection matrix value.
             */
            void setViewProjectionMatrix(const Mind::Matrix4x4f& mat) {
                m_data.viewProjectionMatrix = mat.toArray() ;
            }

            /**
             * Set the inverse view matrix value.
             */
            void setInverseViewMatrix(const Mind::Matrix4x4f& mat) {
                m_data.inverseViewMatrix = mat.toArray() ;
            }

            /**
             * Set the inverse projection matrix value.
             */
            void setInverseProjectionMatrix(const Mind::Matrix4x4f& mat) {
                m_data.inverseProjectionMatrix = mat.toArray() ;
            }

            /**
             * Set the inverse view projection matrix value.
             */
            void setInverseViewProjectionMatrix(const Mind::Matrix4x4f& mat) {
                m_data.inverseViewProjectionMatrix = mat.toArray() ;
            }

            /**
             * Set the viewport matrix value.
             */
            void setViewportMatrix(const Mind::Matrix3x3f& mat) {
                m_data.viewportMatrix = mat.toArray() ;
            }

            /**
             * Set the inverse viewport matrix value.
             */
            void setInverseViewportMatrix(const Mind::Matrix3x3f& mat) {
                m_data.inverseViewportMatrix = mat.toArray() ;
            }

            /**
             * Set the aspect ratio value.
             */
            void setAspectRatio(const float value) {
                m_data.aspectRatio = value ;
            }

            /**
             * Set the time value.
             */
            void setTime(const float value) {
                m_data.time = value ;
            }

            /**
             * Set the eye position value.
             */
            void setEyePosition(const Mind::Vector3f& vec) {
                m_data.eyePosition = vec.toArray() ;
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

            /**
             * Name of the block in the GLSL shader.
             */
            const char* name() const override {
                return BASE_DATA_UBO_BLOCK_NAME ;
            }
    } ;
}

#endif
