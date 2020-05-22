#include <scene/framegraph/RenderCapabilityNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void RenderCapabilityNode::addCapability(API::Capability* capability) {
    if (capability) {
        m_capabilities.push_back(capability) ;
    }
}

void RenderCapabilityNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
