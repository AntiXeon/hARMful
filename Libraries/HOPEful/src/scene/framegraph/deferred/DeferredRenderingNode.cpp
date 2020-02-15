#include <scene/framegraph/deferred/DeferredRenderingNode.hpp>

#include <scene/framegraph/deferred/postprod/AOApplyEffectNode.hpp>

using namespace Hope ;

DeferredRenderingNode::DeferredRenderingNode(
    GBufferRenderNode* gBuffer,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_gBuffer(gBuffer) {
    m_framebufferNode = new FramebufferRenderNode(
        Mind::Dimension2Di(
            gBuffer -> framebuffer() -> width(),
            gBuffer -> framebuffer() -> height()
        ),
        FollowWindowSize,
        nullptr
    ) ;

    setupFramebuffer() ;

    auto outputFBO = m_framebufferNode -> framebuffer() ;
    m_computeSSAONode = new SSAORenderNode(m_gBuffer, m_framebufferNode, this) ;

    // To put m_framebufferNode after m_computeSSAONode in graph.
    m_framebufferNode -> setParent(this) ;
    m_shadingNode = new ShadingStepNode(m_gBuffer, outputFBO, m_framebufferNode) ;
    m_postProdNode = new PostProdStepNode(outputFBO, m_framebufferNode) ;

    AOApplyEffectNode* aoApplyNode = new AOApplyEffectNode(m_framebufferNode) ;
    aoApplyNode -> setParent(m_postProdNode) ;

    m_displayStepNode = new DisplayStepNode(m_framebufferNode, this) ;
}

DeferredRenderingNode::~DeferredRenderingNode() {
    delete m_displayStepNode ;
    delete m_postProdNode ;
    delete m_shadingNode ;
    delete m_computeSSAONode ;
    delete m_framebufferNode ;
}

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
