#ifndef __HOPE__GL_ACTIVE_CAMERA__
#define __HOPE__GL_ACTIVE_CAMERA__

#include <scene/FrameGraphNode.hpp>
#include <scene/components/CameraComponent.hpp>

namespace Hope::GL {
    /**
     * Set the active camera used for rendering the scene.
     */
    class ActiveCamera final : public Hope::FrameGraphNode {
        private:
            /**
             * Camera that is used to render the scene.
             */
            Hope::CameraComponent* m_camera = nullptr ;

        public:
            /**
             * Create a new ActiveCamera node.
             */
            ActiveCamera(Hope::FrameGraphNode* parent = nullptr)
                : Hope::FrameGraphNode(parent) {}

            /**
             * Set the camera that is used to render the scene.
             */
            void setCamera(Hope::CameraComponent* camera) {
                m_camera = camera ;
            }

            /**
             * Get the camera that is used to render the scene.
             */
            Hope::CameraComponent* camera() {
                return m_camera ;
            }
    } ;
}

#endif
