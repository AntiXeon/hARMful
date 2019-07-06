#ifndef __HOPE__FRAMEGRAPH_BRANCH_STATE__
#define __HOPE__FRAMEGRAPH_BRANCH_STATE__

#include <scene/SceneTypes.hpp>
#include <scene/framegraph/conditions/RenderConditionAggregator.hpp>
#include <scene/framegraph/ActiveCameraNode.hpp>
#include <scene/framegraph/RenderCapabilityNode.hpp>
#include <vector>
#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/capabilities/Capability.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * Render state for a frame graph branch.
     */
    class FrameGraphBranchState final {
        private:
            /**
             * If true, the rendering step is performed when the current branch
             * of the framegraph ends (the last node is visited).
             * If false, the rendering step is not performed. This may be used
             * in different situations.
             */
            bool m_renderAtEnd = true ;

            /**
             * Memory barrier bits to apply on rendering.
             */
            uint32_t m_memoryBarrierBits = 0 ;

            /**
             * Render pass ID to use for rendering the current branch.
             */
            RenderPassID m_renderPassID = ForwardPassID ;

            /**
             * Active camera for the current branch.
             */
            ActiveCameraNode* m_activeCamera = nullptr ;

            /**
             * Offscreen framebuffer to be used.
             */
            OffScreenRenderNode* m_offscreen = nullptr ;

            /**
             * Conditions to render the current branch.
             */
            RenderConditionAggregator m_conditions ;

            /**
             * Capability to enaéble on rendering of the current framegraph
             * branch.
             */
            std::vector<API::Capability*> m_capabilities ;

        public:
            /**
             * Create a new FrameGraphBranchState.
             */
            FrameGraphBranchState() = default ;

            /**
             * Create a new FrameGraphBranchState.
             */
            FrameGraphBranchState(
                ActiveCameraNode* activeCamera,
                const RenderConditionAggregator& m_conditions
            ) ;

            /**
             * Set the memory barrier to apply when rendering the current
             * branch.
             */
            void setMemoryBarrier(const uint32_t bits) {
                m_memoryBarrierBits = bits ;
            }

            /**
             * Memory barrier to apply on branch rendering.
             */
            uint32_t memoryBarrier() const {
                return m_memoryBarrierBits ;
            }

            /**
             * Add render capabilties.
             */
            void addRenderCapabilities(RenderCapabilityNode* node) {
                m_capabilities.insert(
                    m_capabilities.begin(),
                    (node -> capabilities()).begin(),
                    (node -> capabilities()).end()
                ) ;
            }

            /**
             * Apply render capabilties.
             */
            void applyRenderCapabilities() {
                for (auto* capability : m_capabilities) {
                    capability -> apply() ;
                }
            }

            /**
             * Remove render capabilties.
             */
            void removeRenderCapabilities() {
                for (auto* capability : m_capabilities) {
                    capability -> remove() ;
                }
            }

            /**
             * If true, the rendering step is performed when the current branch
             * of the framegraph ends (the last node is visited).
             * If false, the rendering step is not performed. This may be used
             * in different situations.
             */
            void setRenderAtEnd(const bool renderAtEnd) {
                m_renderAtEnd = renderAtEnd ;
            }

            /**
             * If true, the rendering step is performed when the current branch
             * of the framegraph ends (the last node is visited).
             * If false, the rendering step is not performed. This may be used
             * in different situations.
             */
            bool renderAtEnd() const {
                return m_renderAtEnd ;
            }

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
            void setActiveCameraNode(ActiveCameraNode* camera) {
                m_activeCamera = camera ;
            }

            /**
             * Get the active camera used to render the branch.
             */
            const ActiveCameraNode* activeCamera() const {
                return m_activeCamera ;
            }

            /**
             * Offscreen framebuffer to be used.
             */
            void setOffScreenRenderNode(OffScreenRenderNode* offscreen) {
                m_offscreen = offscreen ;
            }

            /**
             * Get the offscreen framebuffer to be used.
             */
            const OffScreenRenderNode* offScreenRender() const {
                return m_offscreen ;
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
