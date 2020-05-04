#include <scene/framegraph/deferred/DeferredRenderingNode.hpp>

using namespace Hope ;

const bool DeferredRenderingNode::FollowWindowSize = true ;

DeferredRenderingNode::DeferredRenderingNode(
    GBufferRenderNode* gBuffer,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_gBuffer(gBuffer) {
    m_framebufferNode = std::make_unique<FramebufferRenderNode>(
        Mind::Dimension2Di(
            gBuffer -> framebuffer() -> width(),
            gBuffer -> framebuffer() -> height()
        ),
        FollowWindowSize,
        nullptr
    ) ;

    setupFramebuffer() ;

    auto outputFBO = m_framebufferNode -> framebuffer() ;
    m_computeSSAONode = std::make_unique<SSAORenderNode>(m_gBuffer, m_framebufferNode.get(), this) ;

    // To put m_framebufferNode after m_computeSSAONode in graph.
    m_framebufferNode -> setParent(this) ;
    m_shadingNode = std::make_unique<ShadingStepNode>(m_gBuffer, outputFBO, m_framebufferNode.get()) ;
    m_postProdNode = std::make_unique<PostProdStepNode>(outputFBO, m_framebufferNode.get()) ;

    m_aoApplyNode = std::make_unique<AOApplyEffectNode>(m_framebufferNode.get()) ;
    m_postProdNode -> addEffect(m_aoApplyNode.get()) ;

    m_displayStepNode = std::make_unique<DisplayStepNode>(m_framebufferNode.get(), this) ;
}

// DeferredRenderingNode(
//     std::unique_ptr<API::EnvironmentMap>& environment,
//     GBufferRenderNode* gBuffer,
//     FrameGraphNode* parent = nullptr
// ) : DeferredRenderingNode(gBuffer, parent) {
//
// }

void DeferredRenderingNode::setupFramebuffer() {
    // Render target to apply shading to.
    m_framebufferNode -> framebuffer() -> attachColor(
        ShadingStepNode::ShadingRenderTarget,
        API::InternalFormat::RedGreenBlueAlpha,
        API::PixelFormat::RedGreenBlueAlpha,
        API::PixelDataType::UnsignedByte
    ) ;

    // Render target to compute ambient occlusion to.
    // Try to use RED channel only.
    m_framebufferNode -> framebuffer() -> attachColor(
       SSAORenderNode::AORenderTarget,
       API::InternalFormat::RedGreenBlueAlpha,
       API::PixelFormat::RedGreenBlueAlpha,
       API::PixelDataType::UnsignedByte
    ) ;

    // Render target to apply post production effects.
    m_framebufferNode -> framebuffer() -> attachColor(
       PostProdStepNode::PostProdRenderTarget,
       API::InternalFormat::RedGreenBlueAlpha,
       API::PixelFormat::RedGreenBlueAlpha,
       API::PixelDataType::UnsignedByte
    ) ;
}
