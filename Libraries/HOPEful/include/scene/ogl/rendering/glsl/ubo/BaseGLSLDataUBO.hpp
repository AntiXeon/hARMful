#ifndef __HOPE__GL_BASE_DATA_UNIFORM_BUFFER_OBJECT__
#define __HOPE__GL_BASE_DATA_UNIFORM_BUFFER_OBJECT__

#include <scene/ogl/rendering/glsl/ubo/UniformBufferObject.hpp>
#include <geometry/points/Point4Df.hpp>
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
                std::array<float, Mind::Matrix4x4f::MatrixSize> viewMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> projectionMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> viewProjectionMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> inverseViewMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> inverseProjectionMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> inverseViewProjectionMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> viewportMatrix ;
                std::array<float, Mind::Matrix4x4f::MatrixSize> inverseViewportMatrix ;
                float aspectRatio ;
                float time ;
                std::array<float, Mind::Vector3f::AmountCoords> eyePosition ;
            } m_data ;

        public:
            /**
             * Create a new BaseGLSLDataUBO instance.
             */
            BaseGLSLDataUBO() ;

            /**
             * Set the view matrix value.
             */
            void setViewMatrix(const Mind::Matrix4x4f& mat) {
                m_data.viewMatrix = mat.toArray() ;
                askForAnUpdate() ;
            }

            /**
             * Set the projection matrix value.
             */
            void setProjectionMatrix(const Mind::Matrix4x4f& mat) {
                m_data.projectionMatrix = mat.toArray() ;
                askForAnUpdate() ;
            }

            /**
             * Set the view projection matrix value.
             */
            void setViewProjectionMatrix(const Mind::Matrix4x4f& mat) {
                m_data.viewProjectionMatrix = mat.toArray() ;
                askForAnUpdate() ;
            }

            /**
             * Set the inverse view matrix value.
             */
            void setInverseViewMatrix(const Mind::Matrix4x4f& mat) {
                m_data.inverseViewMatrix = mat.toArray() ;
                askForAnUpdate() ;
            }

            /**
             * Set the inverse projection matrix value.
             */
            void setInverseProjectionMatrix(const Mind::Matrix4x4f& mat) {
                m_data.inverseProjectionMatrix = mat.toArray() ;
                askForAnUpdate() ;
            }

            /**
             * Set the inverse view projection matrix value.
             */
            void setInverseViewProjectionMatrix(const Mind::Matrix4x4f& mat) {
                m_data.inverseViewProjectionMatrix = mat.toArray() ;
                askForAnUpdate() ;
            }

            /**
             * Set the viewport matrix value.
             */
            void setViewportMatrix(const Mind::Matrix3x3f& mat) {
                Mind::Matrix4x4f tmp(mat) ;
                m_data.viewportMatrix = tmp.toArray() ;
                askForAnUpdate() ;
            }

            /**
             * Set the inverse viewport matrix value.
             */
            void setInverseViewportMatrix(const Mind::Matrix3x3f& mat) {
                Mind::Matrix4x4f tmp(mat) ;
                m_data.inverseViewportMatrix = tmp.toArray() ;
                askForAnUpdate() ;
            }

            /**
             * Set the aspect ratio value.
             */
            void setAspectRatio(const float value) {
                m_data.aspectRatio = value ;
                askForAnUpdate() ;
            }

            /**
             * Set the time value.
             */
            void setTime(const float value) {
                m_data.time = value ;
                askForAnUpdate() ;
            }

            /**
             * Set the eye position value.
             */
            void setEyePosition(const Mind::Vector3f& vec) {
                m_data.eyePosition = vec.toArray() ;
                askForAnUpdate() ;
            }

            /**
             * To know if an update is required.
             */
            bool needUpdate() const {
                return true ;
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
