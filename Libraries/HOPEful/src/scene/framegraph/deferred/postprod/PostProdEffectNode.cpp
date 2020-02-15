#include <scene/framegraph/deferred/postprod/PostProdEffectNode.hpp>
#include <scene/framegraph/deferred/subtree/ShadingStepNode.hpp>
#include <scene/framegraph/deferred/subtree/PostProdStepNode.hpp>
#include <scene/ogl/rendering/framebuffers/FramebufferBlitter.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <cassert>
#include <utility>

using namespace Hope ;

PostProdEffectNode::PostProdEffectNode(
    MaterialComponent* material,
    FramebufferRenderNode* framebufferNode
) : OffscreenRenderingNode(material, nullptr),
    m_framebufferNode(framebufferNode) {}

void PostProdEffectNode::postAccept() {
    API::Framebuffer* framebuffer = m_framebufferNode -> framebuffer() ;

    // Copy the content of post-prod result into the shading target.
    API::FramebufferBlitter()
        .setSourceFBO(framebuffer)
        .setSourceColor(PostProdStepNode::PostProdRenderTarget)
        .setSourceArea(
            Mind::Rectangle2Df(
                0,
                0,
                framebuffer -> width(),
                framebuffer -> height()
            )
        )
        .setDestinationFBO(framebuffer)
        .setDestinationColor(ShadingStepNode::ShadingRenderTarget)
        .setDestinationArea(
            Mind::Rectangle2Df(
                0,
                0,
                framebuffer -> width(),
                framebuffer -> height()
            )
        )
        .setMask(API::FramebufferBlitter::Mask::ColorBuffer)
        .setFilter(API::FramebufferBlitter::Filter::Nearest)
        .doBlit() ;
}
