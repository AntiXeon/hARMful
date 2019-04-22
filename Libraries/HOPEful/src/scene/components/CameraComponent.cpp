#include <scene/components/CameraComponent.hpp>
#include <scene/Entity.hpp>
#include <utils/literals/NumberLiterals.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>

using namespace Hope ;

const Mind::Vector3f CameraComponent::WorldUpVector = Mind::Vector3f(0.f, 1.f, 0.f) ;
const Color CameraComponent::DefaultClearColor = Color(4_uchar, 90_uchar, 120_uchar) ;

CameraComponent::CameraComponent()
    : Component(Hope::CameraComponentType),
      m_viewDirection(Mind::Vector3f(0.f, 0.f, -1.f)),
      m_clearColor(DefaultClearColor) {
    m_viewMatrix.identity() ;
    m_up = WorldUpVector ;
}

void CameraComponent::accept(ISceneGraphVisitor* visitor) {
    FrameID currentFrame = visitor -> currentFrameID() ;

    if (lastFrame() < currentFrame) {
        lookAt(m_target) ;
        updateLastFrame(currentFrame) ;

        // No need to be visited!
    }
}

bool CameraComponent::isShareable() const {
    return false ;
}

void CameraComponent::setClearColor(const Color& color) {
    m_clearColor = color ;
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

    m_viewMatrix = rotationMat * translationMat ;
    m_viewMatrix.transposed(m_viewMatrix) ;
}

Mind::Vector3f CameraComponent::target() {
    return m_target ;
}

Mind::Vector3f CameraComponent::viewDirection() {
    return m_viewDirection ;
}

Mind::Vector3f CameraComponent::rightAxis() {
    return m_rightAxis ;
}

Mind::Vector3f CameraComponent::up() {
    return m_up ;
}

Mind::Matrix4x4f CameraComponent::viewMatrix() {
    return m_viewMatrix ;
}

Color CameraComponent::clearColor() {
    return m_clearColor ;
}

void CameraComponent::onAttach(Entity* entity) {
    Mind::Vector3f position = (entity -> transform()).translation() ;
    m_target = position + m_viewDirection ;

    m_rightAxis = WorldUpVector.cross(m_viewDirection) ;
    m_rightAxis.normalize() ;
}
