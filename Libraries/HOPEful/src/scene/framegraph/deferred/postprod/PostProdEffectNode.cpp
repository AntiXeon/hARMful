#include <scene/framegraph/deferred/postprod/PostProdEffectNode.hpp>

using namespace Hope ;

PostProdEffectNode::PostProdEffectNode(
    MaterialComponent* material,
    FramebufferRenderNode* input
) : OffscreenRenderingNode(material, nullptr),
    m_input(input) {

}
