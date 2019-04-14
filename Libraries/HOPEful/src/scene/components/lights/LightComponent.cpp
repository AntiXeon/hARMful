#include <scene/components/lights/LightComponent.hpp>
#include <utils/literals/NumberLiterals.hpp>
#include <scene/Entity.hpp>

using namespace Hope ;

LightComponent::LightComponent(const Type type)
    : Component(LightComponentType),
      m_type(type),
      m_color(Color(192_uchar, 192_uchar, 192_uchar)),
      m_power(1.f),
      m_generateSpecular(true) {}

Mind::Vector3f LightComponent::position() const {
    return (firstEntity() -> transform()).translation() ;
}
