#include <scene/framegraph/deferred/subtree/ShadingStepNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <scene/components/materials/deferred/GBufferQuadMaterialComponent.hpp>

using namespace Hope ;

ShadingStepNode::ShadingStepNode(
    GBufferRenderNode* gBuffer,
    API::Framebuffer* shadingFBO,
    const API::EnvironmentMap* envMap,
    FrameGraphNode* parent
) : OffscreenRenderingNode(
        std::make_unique<GBufferQuadMaterialComponent>(gBuffer, envMap),
        parent
    ),
    m_shadingFBO(shadingFBO) {
    auto* shadingMaterial = static_cast<GBufferQuadMaterialComponent*>(material()) ;
    shadingMaterial -> setExposure(10.f) ;
}

void ShadingStepNode::specificAccept(IFrameGraphVisitor* visitor) {
    m_shadingFBO -> setDrawBuffers({ ShadingRenderTarget }) ;
    visitor -> visit(this) ;
}
