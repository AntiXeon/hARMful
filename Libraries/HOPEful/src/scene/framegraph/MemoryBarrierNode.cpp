#include <scene/framegraph/MemoryBarrierNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

MemoryBarrierNode::MemoryBarrierNode(
    const uint32_t bits,
    Hope::FrameGraphNode* parent
) : Hope::FrameGraphNode(parent),
    m_bits(bits) {}

void MemoryBarrierNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
