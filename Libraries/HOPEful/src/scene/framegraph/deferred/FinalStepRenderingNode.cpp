#include <scene/framegraph/deferred/FinalStepRenderingNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

FinalStepRenderingNode::FinalStepRenderingNode(
    GBufferQuadMaterialComponent* material,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_material(material) {
    setRenderingStepEnabled(false) ;
}

void FinalStepRenderingNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
