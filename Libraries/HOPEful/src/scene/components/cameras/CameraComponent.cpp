#include <scene/components/cameras/CameraComponent.hpp>
#include <scene/Entity.hpp>
#include <utils/literals/NumberLiterals.hpp>

using namespace Hope ;

const Mind::Vector3f CameraComponent::WorldUpVector = Mind::Vector3f(0.f, 1.f, 0.f) ;
const Color CameraComponent::DefaultClearColor = Color(4_uchar, 90_uchar, 120_uchar) ;

CameraComponent::CameraComponent()
    : Component(ClassType),
      m_nearPlaneDistance(0.1f),
      m_farPlaneDistance(1000.f),
      m_viewDirection(Mind::Vector3f(0.f, 0.f, -1.f)),
      m_clearColor(DefaultClearColor) {
    m_up = WorldUpVector ;
    m_viewMatrix.identity() ;
}

void CameraComponent::setUpVector(const Mind::Vector3f& up) {
    m_up = up ;
    m_up.normalize() ;
}

void CameraComponent::lookAt(const Mind::Vector3f& target) {
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

    m_viewMatrix  = rotationMat * translationMat ;
}

Mind::Matrix4x4f& CameraComponent::projectionMatrix(
    Mind::Matrix4x4f& projection,
    const float aspectRatio
) {
    computeProjectionMatrix(projection, aspectRatio) ;
    m_projectionChanged = false ;
    return projection ;
}

void CameraComponent::onAttach(Entity* entity) {
    Mind::Vector3f position = (entity -> transform()).translation() ;
    m_target = position + m_viewDirection ;

    m_rightAxis = WorldUpVector.cross(m_viewDirection) ;
    m_rightAxis.normalize() ;
}
