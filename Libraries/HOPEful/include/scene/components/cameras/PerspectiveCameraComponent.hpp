#ifndef __HOPE__PERSPECTIVE_CAMERA_COMPONENT__
#define __HOPE__PERSPECTIVE_CAMERA_COMPONENT__

#include <scene/components/cameras/CameraComponent.hpp>
#include <geometry/points/Point3Df.hpp>
#include <scene/components/cameras/CameraUtils.hpp>

namespace Hope {
    /**
     * Component that represents a camera, a point of view of the 3D world.
     * This is a perspective camera.
     */
    class PerspectiveCameraComponent final : public CameraComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = CameraComponentType ;

            /**
             * Field of view of the camera.
             */
            float m_fov ;

        public:
            /**
             * Create a new PerspectiveCameraComponent.
             */
            PerspectiveCameraComponent() ;

            /**
             * Set the field of view of the camera.
             */
            void setFOV(const float fov) {
                if (m_fov != fov) {
                    notifyProjectionChange() ;
                    m_fov = fov ;
                }
            }

            /**
             * Get the field of view of the camera.
             */
            float fov() const override {
                return m_fov ;
            }

        protected:
            /**
             * Compute the projection matrix.
             * @param   projection  Projection matrix to get back.
             * @param   aspectRatio Aspect ratio of the window in which the
             *                      camera is used to render the scene.
             * @return  The computed projection, same result as the given
             *          parameter value for a convenient use.
             */
            void computeProjectionMatrix(
                Mind::Matrix4x4f& projection,
                const float aspectRatio
            ) const {
                Perspective(
                    projection,
                    Mind::Math::toRadians(m_fov),
                    aspectRatio,
                    nearPlaneDistance(),
                    farPlaneDistance()
                ) ;
            }
    } ;
}

#endif
