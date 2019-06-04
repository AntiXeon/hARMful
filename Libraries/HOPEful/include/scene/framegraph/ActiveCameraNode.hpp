#ifndef __HOPE__ACTIVE_CAMERA__
#define __HOPE__ACTIVE_CAMERA__

#include <scene/FrameGraphNode.hpp>
#include <scene/framegraph/cache/FrameRenderCache.hpp>
#include <scene/components/cameras/CameraComponent.hpp>
#include <memory>

namespace Hope {
    class IFrameGraphVisitor ;

    /**
     * Set the active camera used for rendering the scene.
     */
    class ActiveCameraNode final : public FrameGraphNode {
        friend class FrameGraphBranchState ;

        private:
            /**
             * Camera that is used to render the scene.
             */
            Hope::CameraComponent* m_camera = nullptr ;

            /**
             * Cache of the scene to render objects.
             */
            std::shared_ptr<FrameRenderCache> m_cache = nullptr ;

            /**
             * To know if the render cache is owned by the current ActiveCameraNode
             * or not.
             */
            bool m_isCacheOwner = true ;

        public:
            /**
             * Create a new ActiveCameraNode node.
             * @param   parent      Parent of the node.
             * @param   cacheOwner  Provide the owner of a cache to be shared
             *                      with the current ActiveCameraNode node.
             *                      nullptr is a valid value, creating a new
             *                      render cache instead of using one from
             *                      another ActiveCameraNode.
             * @note    Sharing a render cache allows a camera to render exactly
             *          the same objects as another one. That is useful, for
             *          example, for VR applications where two cameras must
             *          render exactly the same objects.
             * @warning Only the owner of the cache render can clear its
             *          content. Be aware to do things in the right order!
             */
            ActiveCameraNode(
                FrameGraphNode* parent = nullptr,
                ActiveCameraNode* cacheOwner = nullptr
            ) ;

            /**
             * Set the camera that is used to render the scene.
             */
            void setCamera(CameraComponent* camera) {
                m_camera = camera ;
            }

            /**
             * Get the camera that is used to render the scene.
             */
            Hope::CameraComponent* camera() const {
                return m_camera ;
            }

            /**
             * Check if the cache is empty.
             */
            bool cacheEmpty() const {
                return m_cache -> empty() ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) override ;

        private:
            /**
             * Get the cache of the scene to render objects.
             */
            std::shared_ptr<FrameRenderCache> cache() const {
                return m_cache ;
            } ;
    } ;
}

#endif
