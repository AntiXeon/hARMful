#include <scene/framegraph/deferred/postprod/AOApplyEffectNode.hpp>
#include <scene/components/materials/deferred/postprod/AOPostProdMaterialComponent.hpp>

using namespace Hope ;

AOApplyEffectNode::AOApplyEffectNode(FramebufferRenderNode* framebufferNode)
: PostProdEffectNode(
    new AOPostProdMaterialComponent(framebufferNode),
    framebufferNode
) {}
