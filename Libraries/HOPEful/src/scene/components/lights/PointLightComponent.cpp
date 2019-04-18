#include <scene/components/lights/PointLightComponent.hpp>

using namespace Hope ;

PointLightComponent::PointLightComponent()
    : LightComponent(LightComponent::Type::Point),
      m_distance(30.f)
{
    // Nothing to do.
}
