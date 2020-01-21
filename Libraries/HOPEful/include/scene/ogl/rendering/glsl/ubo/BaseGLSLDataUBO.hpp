#ifndef __HOPE__GL_BASE_DATA_UNIFORM_BUFFER_OBJECT__
#define __HOPE__GL_BASE_DATA_UNIFORM_BUFFER_OBJECT__

#include <scene/ogl/rendering/glsl/ubo/UniformBufferObject.hpp>
#include <geometry/points/Point4Df.hpp>
#include <geometry/points/Point3Df.hpp>
#include <matrices/Matrix3x3f.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <array>
#include <algorithm>

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
                std::array<float, Mind::Vector4f::AmountCoords * 3> viewportMatrix ;
                std::array<float, Mind::Vector4f::AmountCoords * 3> inverseViewportMatrix ;
                std::array<float, Mind::Vector4f::AmountCoords> eye_fov ;
                std::array<float, Mind::Vector4f::AmountCoords> near_far_aspect_time ;
                std::array<float, Mind::Vector2f::AmountCoords> viewportSize ;
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
                static const uint32_t EndOffset = Mind::Matrix3x3f::MatrixSize - 1 ;
                std::copy(
                    m_data.viewportMatrix.begin(),
                    m_data.viewportMatrix.begin() + EndOffset,
                    mat.toArray().begin()
                ) ;
                askForAnUpdate() ;
            }

            /**
             * Set the inverse viewport matrix value.
             */
            void setInverseViewportMatrix(const Mind::Matrix3x3f& mat) {
                static const uint32_t EndOffset = Mind::Matrix3x3f::MatrixSize - 1 ;
                std::copy(
                    m_data.inverseViewportMatrix.begin(),
                    m_data.inverseViewportMatrix.begin() + EndOffset,
                    mat.toArray().begin()
                ) ;
                askForAnUpdate() ;
            }

            /**
             * Set the eye position value.
             */
            void setEyePosition(const Mind::Vector3f& vec) {
                static const uint32_t EndOffset = Mind::Vector3f::AmountCoords - 1 ;
                std::copy(
                    m_data.eye_fov.begin(),
                    m_data.eye_fov.begin() + EndOffset,
                    vec.toArray().begin()
                ) ;
                askForAnUpdate() ;
            }

            /**
             * Set the camera field of view value.
             */
            void setFieldOfView(const float value) {
                static const uint32_t Offset = 3 ;
                m_data.eye_fov[Offset] = value ;
                askForAnUpdate() ;
            }

            /**
             * Set the near plane distance value.
             */
            void setNearPlaneDistance(const float value) {
                static const uint32_t Offset = 0 ;
                m_data.near_far_aspect_time[Offset] = value ;
                askForAnUpdate() ;
            }

            /**
             * Set the far plane distance value.
             */
            void setFarPlaneDistance(const float value) {
                static const uint32_t Offset = 1 ;
                m_data.near_far_aspect_time[Offset] = value ;
                askForAnUpdate() ;
            }

            /**
             * Set the aspect ratio value.
             */
            void setAspectRatio(const float value) {
                static const uint32_t Offset = 2 ;
                m_data.near_far_aspect_time[Offset] = value ;
                askForAnUpdate() ;
            }

            /**
             * Set the time value.
             */
            void setTime(const float value) {
                static const uint32_t Offset = 3 ;
                m_data.near_far_aspect_time[Offset] = value ;
                askForAnUpdate() ;
            }

            /**
             * Set the viewport size.
             */
            void setViewportSize(const Mind::Vector2f& vec) {
                m_data.viewportSize = vec.toArray();
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
