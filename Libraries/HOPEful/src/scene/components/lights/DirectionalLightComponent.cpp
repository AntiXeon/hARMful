#include <scene/components/lights/DirectionalLightComponent.hpp>

using namespace Hope ;

DirectionalLightComponent::DirectionalLightComponent()
    : LightComponent(LightComponent::Type::Directional),
      m_direction(Mind::Vector3f(0.5f, -0.5f, 0.f))
{
    // Nothing to do.
}
