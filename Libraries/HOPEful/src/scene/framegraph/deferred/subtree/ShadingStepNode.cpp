#include <scene/framegraph/deferred/subtree/ShadingStepNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <scene/components/materials/deferred/ShadingDeferredRenderMaterialComponent.hpp>

using namespace Hope ;

ShadingStepNode::ShadingStepNode(
    GBufferRenderNode* gBuffer,
    API::Framebuffer* shadingFBO,
    const API::EnvironmentMap* envMap,
    FrameGraphNode* parent
) : OffscreenRenderingNode(
        std::make_unique<ShadingDeferredRenderMaterialComponent>(gBuffer, envMap),
        parent
    ),
    m_shadingFBO(shadingFBO) {
    auto* shadingMaterial = static_cast<ShadingDeferredRenderMaterialComponent*>(material()) ;
    shadingMaterial -> setExposure(5.f) ;
}

void ShadingStepNode::specificAccept(IFrameGraphVisitor* visitor) {
    m_shadingFBO -> setDrawBuffers({ ShadingRenderTarget }) ;
    visitor -> visit(this) ;
}
