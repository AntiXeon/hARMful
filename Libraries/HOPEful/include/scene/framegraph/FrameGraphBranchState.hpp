#ifndef __HOPE__FRAMEGRAPH_BRANCH_STATE__
#define __HOPE__FRAMEGRAPH_BRANCH_STATE__

#include <scene/SceneTypes.hpp>
#include <scene/framegraph/conditions/RenderConditionAggregator.hpp>
#include <scene/framegraph/ActiveCamera.hpp>

namespace Hope {
    /**
     * Render state for a frame graph branch.
     */
    class FrameGraphBranchState final {
        private:
            /**
             * Render pass ID to use for rendering the current branch.
             */
            RenderPassID m_renderPassID = ForwardPassID ;

            /**
             * Active camera for the current branch.
             */
            ActiveCamera* m_activeCamera = nullptr ;

            /**
             * Conditions to render the current branch.
             */
            RenderConditionAggregator m_conditions ;

        public:
            /**
             * Create a new FrameGraphBranchState.
             */
            FrameGraphBranchState() = default ;

            /**
             * Create a new FrameGraphBranchState.
             */
            FrameGraphBranchState(
                ActiveCamera* activeCamera,
                const RenderConditionAggregator& m_conditions
            ) ;

            /**
             * Set the render pass ID to use for rendering the current branch.
             */
            void setRenderPassID(const RenderPassID id) {
                m_renderPassID = id ;
            }

            /**
             * Get the render pass ID to use for rendering the current branch.
             */
            RenderPassID renderPassID() const {
                return m_renderPassID ;
            }

            /**
             * Set the active camera used to render the branch.
             */
            void setActiveCamera(ActiveCamera* camera) {
                m_activeCamera = camera ;
            }

            /**
             * Get the active camera used to render the branch.
             */
            const ActiveCamera* activeCamera() const {
                return m_activeCamera ;
            }

            /**
             * Get the active camera cache.
             */
            std::shared_ptr<FrameRenderCache> activeCameraCache() const {
                return m_activeCamera -> cache() ;
            }

            /**
             * Get the active camera entity.
             */
            const Entity* activeCameraEntity() const {
                return m_activeCamera -> camera() -> firstEntity() ;
            }

            /**
             * Conditions to render the branch.
             */
            const RenderConditionAggregator& conditions() const {
                return m_conditions ;
            }
    } ;
}

#endif
