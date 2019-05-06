#include <scene/components/cameras/PerspectiveCameraComponent.hpp>
#include <scene/Entity.hpp>
#include <utils/literals/NumberLiterals.hpp>

using namespace Hope ;

PerspectiveCameraComponent::PerspectiveCameraComponent()
    : CameraComponent(),
      m_fov(45.f) {}
