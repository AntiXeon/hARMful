#include <scene/framegraph/deferred/postprod/PostProdEffectNode.hpp>
#include <cassert>
#include <utility>

using namespace Hope ;

PostProdEffectNode::PostProdEffectNode(
    MaterialComponent* material,
    FramebufferRenderNode* input
) : OffscreenRenderingNode(material, nullptr),
    m_input(input) {}

// void PostProdEffectNode::specificAccept(IFrameGraphVisitor* visitor) {
//     assert(m_inputRenderTarget) ;
//     assert(m_outputRenderTarget) ;
//     std::swap(*m_inputRenderTarget, *m_outputRenderTarget) ;
// }
