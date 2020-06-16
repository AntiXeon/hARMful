#ifndef __DEMOHOPE__FRAMEGRAPH__
#define __DEMOHOPE__FRAMEGRAPH__

#include <scene/framegraph/ActiveCameraNode.hpp>
#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <scene/framegraph/ViewportNode.hpp>
#include <scene/framegraph/ClearBuffersNode.hpp>
#include <scene/framegraph/RenderCapabilityNode.hpp>
#include <scene/framegraph/deferred/effects/shadows/DirectionalLightShadowNode.hpp>
#include <scene/framegraph/deferred/effects/fog/FogRenderNode.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/framegraph/deferred/offscreen/GBufferRenderNode.hpp>
#include <scene/framegraph/deferred/DeferredRenderingNode.hpp>
#include <scene/ogl/rendering/capabilities/SeamlessCubemap.hpp>
#include <memory>

#include "SceneGraph.hpp"

/**
 * Frame graph elements.
 */
struct FrameGraph {
    /**
     * Root node.
     */
    std::unique_ptr<Hope::FrameGraphNode> root = nullptr ;

    /**
     * Node to define the active camera for rendering.
     */
    std::unique_ptr<Hope::ActiveCameraNode> activeCameraNode = nullptr ;

    /**
     * Node to compute shadows of a directional light.
     */
    std::unique_ptr<Hope::DirectionalLightShadowNode> dirLightShadowNode = nullptr ;

    /**
     * Node to define the viewport size.
     */
    std::unique_ptr<Hope::ViewportNode> viewportNode = nullptr ;

    /**
     * Node to define the capabilities of the cubemap.
     */
    std::unique_ptr<Hope::RenderCapabilityNode> cubemapCapabilitiesNode = nullptr ;

    /**
     * Seamless cubemap capability.
     */
    std::unique_ptr<Hope::GL::SeamlessCubemap> seamlessCubemapCapability = nullptr ;

    /**
     * GBuffer node.
     */
    std::unique_ptr<Hope::GBufferRenderNode> gBufferNode = nullptr ;

    /**
     * Clear buffer node.
     */
    std::unique_ptr<Hope::ClearBuffersNode> clearBuffersNode = nullptr ;

    /**
     * Selection of the render pass.
     */
    std::unique_ptr<Hope::RenderPassSelectorNode> renderPassNode = nullptr ;

    /**
     * Deferred rendering node.
     */
    std::unique_ptr<Hope::DeferredRenderingNode> deferredRenderingNode = nullptr ;

    /**
     * Create a FrameGraph.
     */
    FrameGraph(
        const Mind::Dimension2Di& windowSize,
        const SceneGraph* scenegraph
    ) ;
} ;

#endif
