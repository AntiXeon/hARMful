#ifndef __HOPE__GL_CAMERA_COMPONENT__
#define __HOPE__GL_CAMERA_COMPONENT__

#include <scene/components/Component.hpp>
#include <geometry/points/Point3Df.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <scene/common/Color.hpp>

namespace Hope {
    class IVisitor ;

    /**
     * Component that represents a camera, a point of view of the 3D world.
     */
    class CameraComponent final : public Component {
        private:
            /**
             * Up vector of the world.
             */
            static const Mind::Vector3f WorldUpVector ;

            /**
             * Default clear color.
             */
            static const Color DefaultClearColor ;

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

            /**
             * Projection matrix.
             */
            Mind::Matrix4x4f m_projectionMatrix ;

            /**
             * Clear color when using the current camera.
             */
            Color m_clearColor ;

        public:
            /**
             * Create a new CameraComponent.
             */
            CameraComponent() ;

            /**
             * Accept the visitor.
             */
            void accept(IVisitor* visitor) override ;

            /**
             * To know if the component can be shared by several entities.
             * @return  false, the CameraComponent cannot be shared.
             */
            bool isShareable() const override ;

            /**
             * Set the clear color of the camera.
             */
            void setClearColor(const Color& color) ;

            /**
             * Generate the projection matrix.
             * @param   projection  Output the projection matrix.
             * @param   position    Position of the camera.
             * @param   target      Center of the camera view.
             * @param   worldUp     Up vector of the world.
             * @return  The projection matrix, the same as the projection
             *          parameter.
             */
            Mind::Matrix4x4f& lookAt(
                Mind::Matrix4x4f& projection,
                const Mind::Vector3f& position,
                const Mind::Vector3f& target,
                const Mind::Vector3f& worldUp = CameraComponent::WorldUpVector
            ) ;

            /**
             * Get the target of the camera.
             */
            Mind::Vector3f target() ;

            /**
             * Get the view direction of the camera.
             */
            Mind::Vector3f viewDirection() ;

            /**
             * Get the right axis of the camera.
             */
            Mind::Vector3f rightAxis() ;

            /**
             * Get the up vector of the camera.
             */
            Mind::Vector3f up() ;

            /**
             * Get the clear color of the camera.
             */
            Color clearColor() ;
    } ;
}

#endif
