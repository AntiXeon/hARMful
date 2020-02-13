#include <scene/framegraph/deferred/subtree/PostProdStepNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <scene/framegraph/deferred/postprod/PostProdEffectNode.hpp>
#include <cassert>

using namespace Hope ;

PostProdStepNode::PostProdStepNode(
    API::Framebuffer* shadingFBO,
    API::Framebuffer* outputFBO,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_shadingFBO(shadingFBO),
    m_outputFBO(outputFBO) {}

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
