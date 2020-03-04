#ifndef __HOPE__DIRECTIONAL_LIGHT_CAMERA_COMPONENT__
#define __HOPE__DIRECTIONAL_LIGHT_CAMERA_COMPONENT__

#include <utils/Platform.hpp>
#include <scene/components/cameras/CameraComponent.hpp>

namespace Hope {
    /**
     * A camera used to render shadow depth map of a directional light.
     * It is not intended to be used from an application. This kind of camera is
     * created by the DirectionalLightShadowNode from the frame graph.
     */
    class DirectionalLightCameraComponent final : public CameraComponent {
        friend class ShadowCascade ;

        private:
            /**
             * Projection matrix of the camera.
             */
            Mind::Matrix4x4f m_projectionMatrix ;

        public:
            /**
             * To know if the camera data must be fully updated or if a limited
             * amount of data are to update for shaders.
             * @return  true if the camera data have to be fully sent to shaders
             *          (and so computed on CPU side); false to limit the amount
             *          of data to compute and to send to shaders.
             */
            exported bool requireFullDataUpdate() const override {
                return false ;
            }

            /**
             * Update the camera.
             */
            exported void update() override {
                // Do nothing.
            }

            /**
             * Get the field of view of the camera.
             */
            exported float fov() const override {
                return 0.f ;
            }

        protected:
            /**
             * Compute the projection matrix.
             * @param   projection  Projection matrix to get back.
             * @param   aspectRatio Unused.
             * @return  The computed projection, same result as the given
             *          parameter value for a convenient use.
             */
            exported void computeProjectionMatrix(
                Mind::Matrix4x4f& projection,
                const float
            ) const {
                projection = m_projectionMatrix ;
            }

        private:
            /**
             * Set the projection matrix.
             */
            exported void setProjectionMatrix(const Mind::Matrix4x4f& projection) {
                m_projectionMatrix = projection ;
                notifyProjectionChange() ;
            }
    } ;
}

#endif
