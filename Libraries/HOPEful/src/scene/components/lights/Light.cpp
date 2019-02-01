#include <scene/components/lights/Light.hpp>

using namespace Hope ;

Light::Light(const Type type)
    : Component(LightType) {
    m_type = type ;
    m_color = Color(0xFFFFFFFF) ;
    m_intensity = 1.f ;
}

bool Light::isShareable() const {
    return false ;
}

void Light::setColor(const Color& color) {
    m_color = color ;
}

void Light::setColor(const int color) {
    m_color = Color(color) ;
}

void Light::setColor(
    const uint8_t red,
    const uint8_t green,
    const uint8_t blue
) {
    m_color = Color(red, green, blue, 255) ;
}

void Light::setIntensity(const float intensity) {
    m_intensity = intensity ;
}

Color Light::color() const {
    return m_color ;
}

float Light::intensity() const {
    return m_intensity ;
}

Type Light::type() const {
    return m_type ;
}

void Light::onAttach(Entity* entity) override {
    Entity* entity = firstEntity() ;

    if (!entity) {
        return ;
    }

    if (entity -> renderData()) {
        entity -> renderData() -> addLight(*this) ;
    }
}

void Light::onDetach(Entity* entity) override {
    Entity* entity = firstEntity() ;

    if (!entity) {
        return ;
    }

    if (entity -> renderData()) {
        entity -> renderData() -> removeLight(*this) ;
    }
}
