#include <scene/framegraph/deferred/postprod/PostProdEffectNode.hpp>
#include <scene/framegraph/deferred/subtree/ShadingStepNode.hpp>
#include <scene/framegraph/deferred/subtree/PostProdStepNode.hpp>
#include <scene/ogl/rendering/framebuffers/FramebufferBlitter.hpp>
#include <cassert>
#include <utility>

using namespace Hope ;

PostProdEffectNode::PostProdEffectNode(
    MaterialComponent* material,
    API::Framebuffer* framebuffer
) : OffscreenRenderingNode(material, nullptr),
    m_framebuffer(framebuffer) {}

void PostProdEffectNode::postAccept() {
    // Copy the content of post-prod result into the shading target.
    API::FramebufferBlitter()
        .setSourceFBO(m_framebuffer)
        .setSourceColor(PostProdStepNode::PostProdRenderTarget)
        .setSourceArea(
            Mind::Rectangle2Df(
                0,
                0,
                m_framebuffer -> width(),
                m_framebuffer -> height()
            )
        )
        .setDestinationFBO(m_framebuffer)
        .setDestinationColor(ShadingStepNode::ShadingRenderTarget)
        .setDestinationArea(
            Mind::Rectangle2Df(
                0,
                0,
                m_framebuffer -> width(),
                m_framebuffer -> height()
            )
        )
        .setMask(API::FramebufferBlitter::Mask::ColorBuffer)
        .setFilter(API::FramebufferBlitter::Filter::Nearest)
        .doBlit() ;
}
