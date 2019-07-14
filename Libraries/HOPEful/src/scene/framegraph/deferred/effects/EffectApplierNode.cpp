#include <scene/framegraph/deferred/effects/EffectApplierNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

EffectApplierNode::EffectApplierNode(
    EffectData* effect,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_effect(effect) {}

void EffectApplierNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
