#include <scene/components/cameras/CameraComponent.hpp>
#include <scene/Entity.hpp>
#include <utils/literals/NumberLiterals.hpp>

using namespace Hope ;

const Color CameraComponent::DefaultClearColor = Color(4_uchar, 90_uchar, 120_uchar) ;

CameraComponent::CameraComponent()
    : Component(ClassType),
      m_clearColor(DefaultClearColor) {
    m_viewMatrix.identity() ;
}
