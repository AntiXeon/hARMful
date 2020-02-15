#include <scene/framegraph/deferred/subtree/ShadingStepNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <scene/components/materials/deferred/GBufferQuadMaterialComponent.hpp>

using namespace Hope ;

ShadingStepNode::ShadingStepNode(
    GBufferRenderNode* gBuffer,
    API::Framebuffer* shadingFBO,
    FrameGraphNode* parent
) : OffscreenRenderingNode(
        std::make_unique<GBufferQuadMaterialComponent>(gBuffer),
        parent
    ),
    m_shadingFBO(shadingFBO) {}

ShadingStepNode::~ShadingStepNode() {
    // Use smart pointers instead!
    delete material() ;
}

void ShadingStepNode::specificAccept(IFrameGraphVisitor* visitor) {
    m_shadingFBO -> setDrawBuffers({ ShadingRenderTarget }) ;
    visitor -> visit(this) ;
}
