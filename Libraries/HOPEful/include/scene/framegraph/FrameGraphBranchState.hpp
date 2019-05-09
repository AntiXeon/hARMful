#ifndef __HOPE__FRAMEGRAPH_BRANCH_STATE__
#define __HOPE__FRAMEGRAPH_BRANCH_STATE__

#include <scene/framegraph/conditions/RenderConditionAggregator.hpp>
#include <scene/framegraph/ActiveCamera.hpp>

namespace Hope {
    /**
     * Render state for a frame graph branch.
     */
    class FrameGraphBranchState final {
        private:
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
             * Conditions to render the branch.
             */
            const RenderConditionAggregator& conditions() const {
                return m_conditions ;
            }
    } ;
}

#endif
