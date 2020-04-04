#include <scene/framegraph/deferred/subtree/PostProdStepNode.hpp>
#include <scene/framegraph/deferred/subtree/ShadingStepNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <scene/framegraph/deferred/postprod/PostProdEffectNode.hpp>
#include <scene/ogl/rendering/framebuffers/FramebufferBlitter.hpp>
#include <cassert>

using namespace Hope ;

PostProdStepNode::PostProdStepNode(
    API::Framebuffer* framebuffer,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_framebuffer(framebuffer) {
    m_effectsRoot = std::make_unique<FrameGraphNode>(this) ;
}

void PostProdStepNode::addEffect(PostProdEffectNode* node) {
    assert(node != nullptr) ;
    [[maybe_unused]] short id = node -> id() ;

    // Be sure the node is not already in this (or another) PostProdStepNode
    // list.
    assert (id == PostProdEffectNode::DefaultID) ;

    node -> setParent(m_effectsRoot.get()) ;
    short nodeID = static_cast<short>(m_effects.size()) ;
    m_effects.insert(node) ;
    node -> setId(nodeID) ;
}

void PostProdStepNode::removeEffect(PostProdEffectNode* node) {
    assert(node != nullptr) ;
    [[maybe_unused]] short id = node -> id() ;

    // Be sure the node is linked to this PostProdStepNode.
    assert(id >= 0) ;
    assert(m_effects.count(node)  == 1) ;

    node -> setParent(nullptr) ;
    m_effects.erase(node) ;
    node -> setId(PostProdEffectNode::DefaultID) ;
}

void PostProdStepNode::specificAccept(IFrameGraphVisitor*) {
    // Copy the content of shading result into the post-prod target.
    API::FramebufferBlitter()
        .setSourceFBO(m_framebuffer)
        .setSourceColor(ShadingStepNode::ShadingRenderTarget)
        .setSourceArea(
            Mind::Rectangle2Df(
                0,
                0,
                static_cast<Mind::Scalar>(m_framebuffer -> width()),
                static_cast<Mind::Scalar>(m_framebuffer -> height())
            )
        )
        .setDestinationFBO(m_framebuffer)
        .setDestinationColor(PostProdRenderTarget)
        .setDestinationArea(
            Mind::Rectangle2Df(
                0,
                0,
                static_cast<Mind::Scalar>(m_framebuffer -> width()),
                static_cast<Mind::Scalar>(m_framebuffer -> height())
            )
        )
        .setMask(API::FramebufferBlitter::Mask::ColorBuffer)
        .setFilter(API::FramebufferBlitter::Filter::Nearest)
        .doBlit() ;
}
