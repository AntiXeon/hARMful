#include <scene/framegraph/deferred/postprod/AOApplyEffectNode.hpp>
#include <scene/components/materials/deferred/postprod/AOPostProdMaterialComponent.hpp>
#include <memory>

using namespace Hope ;

AOApplyEffectNode::AOApplyEffectNode(FramebufferRenderNode* framebufferNode)
: PostProdEffectNode(
    std::make_unique<AOPostProdMaterialComponent>(framebufferNode),
    framebufferNode
) {}
