#ifndef __HOPE__CAMERA_COMPONENT__
#define __HOPE__CAMERA_COMPONENT__

#include <scene/components/Component.hpp>
#include <geometry/points/Point3Df.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <scene/common/Color.hpp>

namespace Hope {
    class ISceneGraphVisitor ;

    /**
     * Component that represents a camera, a point of view of the 3D world.
     * This is a perspective camera.
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
             * View matrix.
             */
            Mind::Matrix4x4f m_viewMatrix ;

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
            void accept(ISceneGraphVisitor* visitor) override ;

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
             * Get the view matrix.
             */
            Mind::Matrix4x4f viewMatrix() ;

            /**
             * Get the clear color of the camera.
             */
            Color clearColor() ;

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
