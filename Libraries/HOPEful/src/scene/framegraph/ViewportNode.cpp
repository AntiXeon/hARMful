#include <scene/framegraph/ViewportNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void ViewportNode::setPosition(const Mind::Point2Df& position) {
    const float MinValue = 0.f ;
    const float MaxValue = 1.f ;

    float x = std::clamp(position.get(Mind::Point2Df::X), MinValue, MaxValue) ;
    float y = std::clamp(position.get(Mind::Point2Df::Y), MinValue, MaxValue) ;
    m_position.set(x, y) ;
}

void ViewportNode::setDimension(const Mind::Dimension2Df& dimension) {
    const float MinValue = 0.f ;
    const float MaxValue = 1.f ;

    float w = std::clamp(dimension.width(), MinValue, MaxValue) ;
    float h = std::clamp(dimension.height(), MinValue, MaxValue) ;
    m_dimension.set(w, h) ;
}

void ViewportNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
