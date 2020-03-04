#ifndef __HOPE__ORTHOGRAPHIC_CAMERA_COMPONENT__
#define __HOPE__ORTHOGRAPHIC_CAMERA_COMPONENT__

#include <utils/Platform.hpp>

#include <scene/components/cameras/CameraComponent.hpp>
#include <scene/components/cameras/CameraUtils.hpp>
#include <geometry/points/Point3Df.hpp>

namespace Hope {
    /**
     * Component that represents a camera, a point of view of the 3D world.
     * This is a*n orthographic camera.
     */
    class OrthographicCameraComponent final : public CameraComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = CameraComponentType ;

            /**
             * Specify the coordinates for the top horizontal clipping plane.
             */
            float m_top ;

            /**
             * Specify the coordinates for the bottom horizontal clipping plane.
             */
            float m_bottom ;

            /**
             * Specify the coordinates for the left vertical clipping plane.
             */
            float m_left ;

            /**
             * Specify the coordinates for the right vertical clipping plane.
             */
            float m_right ;

        public:
            /**
             * Create a new OrthographicCameraComponent.
             */
            exported OrthographicCameraComponent() ;

            /**
             * Set the coordinates for the top horizontal clipping plane.
             */
            exported void setTopPlane(const float top) {
                m_top = top ;
            }

            /**
             * Set the coordinates for the bottom horizontal clipping plane.
             */
            exported void setBottomPlane(const float bottom) {
                m_bottom = bottom ;
            }

            /**
             * Set the coordinates for the left vertical clipping plane.
             */
            exported void setLeftPlane(const float left) {
                m_left = left ;
            }

            /**
             * Set the coordinates for the right vertical clipping plane.
             */
            exported void setRightPlane(const float right) {
                m_right = right ;
            }

            /**
             * Get the coordinates for the top horizontal clipping plane.
             */
            exported float topPlane() {
                return m_top ;
            }

            /**
             * Get the coordinates for the bottom horizontal clipping plane.
             */
            exported float bottomPlane() {
                return m_bottom ;
            }

            /**
             * Get the coordinates for the left vertical clipping plane.
             */
            exported float leftPlane() {
                return m_left ;
            }

            /**
             * Get the coordinates for the right vertical clipping plane.
             */
            exported float rightPlane() {
                return m_right ;
            }

            /**
             * Get the field of view of the camera.
             * An orthographic camera does not have FOV...
             */
            exported float fov() const override {
                return 0.f ;
            }

        protected:
            /**
             * Compute the projection matrix.
             * @param   projection  Projection matrix to get back.
             * @param   aspectRatio Unused here.
             * @return  The computed projection, same result as the given
             *          parameter value for a convenient use.
             */
            exported void computeProjectionMatrix(
                Mind::Matrix4x4f& projection,
                const float
            ) const {
                Orthographic(
                    projection,
                    m_left,
                    m_right,
                    m_bottom,
                    m_top,
                    nearPlaneDistance(),
                    farPlaneDistance()
                ) ;
            }
    } ;
}

#endif
