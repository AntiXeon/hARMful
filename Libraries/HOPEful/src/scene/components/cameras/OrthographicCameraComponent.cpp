#include <scene/components/cameras/OrthographicCameraComponent.hpp>
#include <scene/Entity.hpp>
#include <utils/literals/NumberLiterals.hpp>

using namespace Hope ;

OrthographicCameraComponent::OrthographicCameraComponent()
    : CameraComponent(),
      m_top(1.f),
      m_bottom(0.f),
      m_left(0.f),
      m_right(1.f) {}
