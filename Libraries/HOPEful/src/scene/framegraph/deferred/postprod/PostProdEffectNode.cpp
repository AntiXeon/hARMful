#include <scene/framegraph/deferred/postprod/PostProdEffectNode.hpp>
#include <scene/ogl/rendering/framebuffers/FramebufferBlitter.hpp>
#include <cassert>
#include <utility>

using namespace Hope ;

PostProdEffectNode::PostProdEffectNode(
    MaterialComponent* material,
    FramebufferRenderNode* input
) : OffscreenRenderingNode(material, nullptr),
    m_input(input -> framebuffer()) {}

void PostProdEffectNode::postAccept() {
    API::FramebufferBlitter()
        .setSourceFBO(m_input)
        .setSourceColor(0)      // To be defined!
        .setSourceArea(
            Mind::Rectangle2Df(
                0,
                0,
                m_input -> width(),
                m_input -> height()
            )
        )
        .setDestinationFBO(m_output)
        .setDestinationColor(0) // To be defined!
        .setDestinationArea(
            Mind::Rectangle2Df(
                0,
                0,
                m_output -> width(),
                m_output -> height()
            )
        )
        .setMask(API::FramebufferBlitter::Mask::ColorBuffer)
        .setFilter(API::FramebufferBlitter::Filter::Nearest)
        .doBlit() ;
}
