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
    m_framebuffer(framebuffer) {}

void PostProdStepNode::addEffect(PostProdEffectNode* node) {
    assert(node != nullptr) ;
    short id = node -> id() ;

    // Be sure the node is not already in this (or another) PostProdStepNode
    // list.
    assert(id == PostProdEffectNode::DefaultID) ;

    node -> setParent(m_effectsRoot) ;
    short nodeID = static_cast<short>(m_effects.size()) ;
    m_effects.push_back(node) ;
    node -> setId(nodeID) ;
}

void PostProdStepNode::removeEffect(PostProdEffectNode* node) {
    assert(node != nullptr) ;
    short id = node -> id() ;

    // Be sure the node is linked to this PostProdStepNode.
    assert(id >= 0) ;
    assert(m_effects[id] == node) ;

    node -> setParent(nullptr) ;
    m_effects.erase(m_effects.begin() + id) ;
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
                m_framebuffer -> width(),
                m_framebuffer -> height()
            )
        )
        .setDestinationFBO(m_framebuffer)
        .setDestinationColor(PostProdRenderTarget)
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
