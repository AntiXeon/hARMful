#ifndef __HOPE__FRAMEGRAPH_BRANCH_STATE__
#define __HOPE__FRAMEGRAPH_BRANCH_STATE__

#include <utils/Platform.hpp>

#include <scene/SceneTypes.hpp>
#include <scene/framegraph/deferred/offscreen/base/AbstractFramebufferRenderNode.hpp>
#include <scene/framegraph/deferred/effects/EffectData.hpp>
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
            AbstractFramebufferRenderNode* m_offscreen = nullptr ;

            /**
             * Conditions to render the current branch.
             */
            RenderConditionAggregator m_conditions ;

            /**
             * Capability to enable on rendering of the current framegraph
             * branch.
             */
            std::vector<API::Capability*> m_capabilities ;

            /**
             * List of effects to apply when rendering the current branch.
             */
            std::vector<EffectData*> m_effects ;

        public:
            /**
             * Create a new FrameGraphBranchState.
             */
            exported FrameGraphBranchState() = default ;

            /**
             * Create a new FrameGraphBranchState.
             */
            exported FrameGraphBranchState(
                ActiveCameraNode* activeCamera,
                const RenderConditionAggregator& m_conditions
            ) ;

            /**
             * Set the memory barrier to apply when rendering the current
             * branch.
             */
            exported void setMemoryBarrier(const uint32_t bits) {
                m_memoryBarrierBits = bits ;
            }

            /**
             * Memory barrier to apply on branch rendering.
             */
            exported uint32_t memoryBarrier() const {
                return m_memoryBarrierBits ;
            }

            /**
             * Add render capabilties.
             */
            exported void addRenderCapabilities(RenderCapabilityNode* node) {
                m_capabilities.insert(
                    m_capabilities.begin(),
                    (node -> capabilities()).begin(),
                    (node -> capabilities()).end()
                ) ;
            }

            /**
             * Apply render capabilties.
             */
            exported void applyRenderCapabilities() {
                for (auto* capability : m_capabilities) {
                    capability -> apply() ;
                }
            }

            /**
             * Remove render capabilties.
             */
            exported void removeRenderCapabilities() {
                for (auto* capability : m_capabilities) {
                    capability -> remove() ;
                }
            }

            /**
             * Add effect data to the current branch. They are applied on the
             * deferred rendering steps.
             */
            exported void addEffectData(const std::vector<EffectData*>& data) {
                m_effects.insert(
                    m_effects.begin(),
                    data.begin(),
                    data.end()
                ) ;
            }

            /**
             * Get the effect data to apply on rendering.
             */
            exported std::vector<EffectData*>& effectData() {
                return m_effects ;
            }

            /**
             * If true, the rendering step is performed when the current branch
             * of the framegraph ends (the last node is visited).
             * If false, the rendering step is not performed. This may be used
             * in different situations.
             */
            exported void setRenderAtEnd(const bool renderAtEnd) {
                m_renderAtEnd = renderAtEnd ;
            }

            /**
             * If true, the rendering step is performed when the current branch
             * of the framegraph ends (the last node is visited).
             * If false, the rendering step is not performed. This may be used
             * in different situations.
             */
            exported bool renderAtEnd() const {
                return m_renderAtEnd ;
            }

            /**
             * Set the render pass ID to use for rendering the current branch.
             */
            exported void setRenderPassID(const RenderPassID id) {
                m_renderPassID = id ;
            }

            /**
             * Get the render pass ID to use for rendering the current branch.
             */
            exported RenderPassID renderPassID() const {
                return m_renderPassID ;
            }

            /**
             * Set the active camera used to render the branch.
             */
            exported void setActiveCameraNode(ActiveCameraNode* camera) {
                m_activeCamera = camera ;
            }

            /**
             * Get the active camera used to render the branch.
             */
            exported const ActiveCameraNode* activeCamera() const {
                return m_activeCamera ;
            }

            /**
             * Offscreen framebuffer to be used.
             */
            exported void setFramebufferRenderNode(AbstractFramebufferRenderNode* offscreen) {
                m_offscreen = offscreen ;
            }

            /**
             * Get the offscreen framebuffer to be used.
             */
            exported const AbstractFramebufferRenderNode* offScreenRender() const {
                return m_offscreen ;
            }

            /**
             * Get the active camera cache.
             */
            exported std::shared_ptr<FrameRenderCache> activeCameraCache() const {
                return m_activeCamera -> cache() ;
            }

            /**
             * Get the active camera entity.
             */
            exported const Entity* activeCameraEntity() const {
                return m_activeCamera -> camera() -> firstEntity() ;
            }

            /**
             * Conditions to render the branch.
             */
            exported const RenderConditionAggregator& conditions() const {
                return m_conditions ;
            }
    } ;
}

#endif
