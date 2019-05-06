#include <scene/components/cameras/PerspectiveCameraComponent.hpp>
#include <scene/Entity.hpp>
#include <utils/literals/NumberLiterals.hpp>

using namespace Hope ;

const Mind::Vector3f PerspectiveCameraComponent::WorldUpVector = Mind::Vector3f(0.f, 1.f, 0.f) ;

PerspectiveCameraComponent::PerspectiveCameraComponent()
    : CameraComponent(),
      m_viewDirection(Mind::Vector3f(0.f, 0.f, -1.f)) {
    m_up = WorldUpVector ;
}

void PerspectiveCameraComponent::setUpVector(const Mind::Vector3f& up) {
    m_up = up ;
    m_up.normalize() ;
}

void PerspectiveCameraComponent::lookAt(const Mind::Vector3f& target) {
    m_target = target ;
    Mind::Vector3f position = (firstEntity() -> transform()).translation() ;

    m_viewDirection = position - m_target ;
    m_viewDirection.normalize() ;

    m_rightAxis = m_up.cross(m_viewDirection) ;
    m_rightAxis.normalize() ;

    Mind::Vector3f up = m_viewDirection.cross(m_rightAxis) ;

    Mind::Matrix4x4f translationMat ;
    translationMat.identity() ;
    translationMat.setColumnValues(3, -position) ;

    Mind::Matrix4x4f rotationMat ;
    rotationMat.identity() ;
    rotationMat.setRowValues(0, m_rightAxis) ;
    rotationMat.setRowValues(1, up) ;
    rotationMat.setRowValues(2, m_viewDirection) ;

    setViewMatrix(rotationMat * translationMat) ;
}

void PerspectiveCameraComponent::onAttach(Entity* entity) {
    Mind::Vector3f position = (entity -> transform()).translation() ;
    m_target = position + m_viewDirection ;

    m_rightAxis = WorldUpVector.cross(m_viewDirection) ;
    m_rightAxis.normalize() ;
}
