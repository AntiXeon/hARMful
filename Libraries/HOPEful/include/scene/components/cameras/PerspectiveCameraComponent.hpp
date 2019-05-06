#ifndef __HOPE__PERSPECTIVE_CAMERA_COMPONENT__
#define __HOPE__PERSPECTIVE_CAMERA_COMPONENT__

#include <scene/components/cameras/CameraComponent.hpp>
#include <geometry/points/Point3Df.hpp>
#include <scene/common/Color.hpp>

namespace Hope {
    class ISceneGraphVisitor ;

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

        private:
            /**
             * Up vector of the world.
             */
            static const Mind::Vector3f WorldUpVector ;

            /**
             * Point in the 3D space the camera is targetting.
             */
            Mind::Vector3f m_target ;

            /**
             * Direction of the camera view.
             */
            Mind::Vector3f m_viewDirection ;

            /**
             * Right axis of the camera.
             */
            Mind::Vector3f m_rightAxis ;

            /**
             * up vector of the camera.
             */
            Mind::Vector3f m_up ;

        public:
            /**
             * Create a new PerspectiveCameraComponent.
             */
            PerspectiveCameraComponent() ;

            /**
             * Update the camera.
             */
            void update() override {
                lookAt(m_target) ;
            }

            /**
             * Set the up vector of the camera. The up vector is normalized.
             * Default is Y-up.
             */
            void setUpVector(const Mind::Vector3f& up) ;

            /**
             * Generate the view matrix.
             * @param   target      Center of the camera view.
             */
            void lookAt(const Mind::Vector3f& target) ;

            /**
             * Get the target of the camera.
             */
            const Mind::Vector3f& target() const {
                return m_target ;
            }

            /**
             * Get the view direction of the camera.
             */
            const Mind::Vector3f& viewDirection() const {
                return m_viewDirection ;
            }

            /**
             * Get the right axis of the camera.
             */
            const Mind::Vector3f& rightAxis() const {
                return m_rightAxis ;
            }

            /**
             * Get the up vector of the camera.
             */
            const Mind::Vector3f& up() const {
                return m_up ;
            }

        protected:
            /**
             * Action to performed when the component is attached to an
             * entity.
             * @param   entity  Entity to attach the component to.
             */
            void onAttach(Entity* entity) override ;
    } ;
}

#endif
