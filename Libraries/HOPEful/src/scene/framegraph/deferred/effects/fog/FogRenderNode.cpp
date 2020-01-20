#include <scene/framegraph/deferred/effects/fog/FogRenderNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

FogRenderNode::FogRenderNode(
    const Color& color,
    const float minDistance,
    const float maxDistance,
    FrameGraphNode* parent
) : EffectFrameGraphNode(parent) {
    setColor(color) ;
    setMinimalDistance(minDistance) ;
    setMaximalDistance(maxDistance) ;
}

void FogRenderNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
