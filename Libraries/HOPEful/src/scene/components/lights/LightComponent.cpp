#include <scene/components/lights/LightComponent.hpp>
#include <utils/literals/NumberLiterals.hpp>
#include <scene/Entity.hpp>

using namespace Hope ;

LightComponent::LightComponent(const Type type)
    : Component(LightComponentType) {
    m_type = type ;
    m_ambient = Color(48_uchar, 48_uchar, 48_uchar) ;
    m_diffuse = Color(192_uchar, 192_uchar, 192_uchar) ;
    m_specular = Color(255_uchar, 255_uchar, 255_uchar) ;
}

void LightComponent::onAttach(Entity* entity) {
    if (!entity) {
        return ;
    }

    if (entity -> renderData()) {
        entity -> renderData() -> addLight(this) ;
    }
}

void LightComponent::onDetach(Entity* entity) {
    if (!entity) {
        return ;
    }

    if (entity -> renderData()) {
        entity -> renderData() -> removeLight(this) ;
    }
}

Mind::Vector3f LightComponent::position() const {
    return (firstEntity() -> transform()).translation() ;
}
