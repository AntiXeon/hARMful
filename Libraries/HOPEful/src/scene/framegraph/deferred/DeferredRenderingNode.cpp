#include <scene/framegraph/deferred/DeferredRenderingNode.hpp>

using namespace Hope ;

DeferredRenderingNode::DeferredRenderingNode(
    GBufferRenderNode* gBuffer,
    const Mind::Dimension2Di& size,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_gBuffer(gBuffer) {
    m_framebufferNode = new FramebufferRenderNode(size, FollowWindowSize, nullptr) ;
    setupFramebuffer() ;

    auto outputFBO = m_framebufferNode -> framebuffer() ;
    m_computeSSAONode = new SSAORenderNode(m_gBuffer, outputFBO, this) ;

    // To put m_framebufferNode after m_computeSSAONode in graph.
    m_framebufferNode -> setParent(this) ;
    m_shadingNode = new ShadingStepNode(m_gBuffer, outputFBO, m_framebufferNode) ;
    m_postProdNode = new PostProdStepNode(outputFBO, m_framebufferNode) ;
}

DeferredRenderingNode::~DeferredRenderingNode() {
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
