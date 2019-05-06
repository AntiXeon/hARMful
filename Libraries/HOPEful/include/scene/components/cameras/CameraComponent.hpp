#ifndef __HOPE__CAMERA_COMPONENT__
#define __HOPE__CAMERA_COMPONENT__

#include <scene/components/Component.hpp>
#include <geometry/points/Point3Df.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <scene/common/Color.hpp>

namespace Hope {
    class ISceneGraphVisitor ;

    /**
     * Component that represents a camera.
     * Useless as is, use a PerspectiveCameraComponent or an
     * OrthographicCameraComponent.
     */
    class CameraComponent : public Component {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = CameraComponentType ;

        private:
            /**
             * Default clear color.
             */
            static const Color DefaultClearColor ;

            /**
             * Clear color when using the current camera.
             */
            Color m_clearColor ;

            /**
             * View matrix.
             */
            Mind::Matrix4x4f m_viewMatrix ;

        public:
            /**
             * Create a new CameraComponent.
             */
            CameraComponent() ;

            /**
             * Update the camera.
             */
            virtual void update() = 0 ;

            /**
             * To know if the component can be shared by several entities.
             * @return  false, the CameraComponent cannot be shared.
             */
            bool isShareable() const override {
                return false ;
            }

            /**
             * To know if the component can be removed from its entity(-ies).
             * @return  true, the component can be removed.
             */
            bool isRemovable() const override {
                return true ;
            }

            /**
             * To know if several components of the current type can be beared
             * by a single entity.
             * @return  false, an entity can only bear one CameraComponent.
             */
            bool isStackable() const override {
                return false ;
            }

            /**
             * Set the clear color of the camera.
             */
            void setClearColor(const Color& color) {
                m_clearColor = color ;
            }

            /**
             * Get the clear color of the camera.
             */
            const Color& clearColor() const {
                return m_clearColor ;
            }

            /**
             * Get the view matrix.
             */
            const Mind::Matrix4x4f& viewMatrix() const {
                return m_viewMatrix ;
            }

        protected:
            /**
             * Set the view matrix.
             */
            void setViewMatrix(const Mind::Matrix4x4f& matrix) {
                m_viewMatrix = matrix ;
            }
    } ;
}

#endif
