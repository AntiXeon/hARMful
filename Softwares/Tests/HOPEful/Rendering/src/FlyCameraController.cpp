#include "FlyCameraController.hpp"
#include <scene/Entity.hpp>
#include <algorithm>

#include <iostream>

const float FlyCameraController::WalkSpeed = 5.f ;
const float FlyCameraController::RunSpeed = 15.f ;

FlyCameraController::FlyCameraController(Hope::CameraComponent* camera)
: m_camera(camera),
  m_cameraTransform(m_camera -> firstEntity() -> transform()) {}

void FlyCameraController::setSpeed(const float speed) {
    m_speed = std::clamp(speed, 0.5f, 10.f) ;
}

void FlyCameraController::move(
    const MoveDirection moveDirection,
    const float deltaTime
) {
    float velocity = m_speed * deltaTime ;

    auto direction = m_camera -> viewDirection() ;
    auto up = m_camera -> up() ;
    auto right = direction.cross(up) ;

    Mind::Vector3f newCameraPosition ;

    switch (moveDirection) {
        case MoveDirection::Forward:
            newCameraPosition = m_cameraTransform.get().translation() - (direction * velocity) ;
            break ;

        case MoveDirection::Backward:
            newCameraPosition = m_cameraTransform.get().translation() + (direction * velocity) ;
            break ;

        case MoveDirection::Right:
            newCameraPosition = m_cameraTransform.get().translation() - (right * velocity) ;
            break ;

        case MoveDirection::Left:
            newCameraPosition = m_cameraTransform.get().translation() + (right * velocity) ;
            break ;

        case MoveDirection::Up:
            newCameraPosition = m_cameraTransform.get().translation() + (up * velocity) ;
            break ;

        case MoveDirection::Down:
            newCameraPosition = m_cameraTransform.get().translation() - (up * velocity) ;
            break ;
    }

    m_cameraTransform.get().setTranslation(newCameraPosition) ;
    m_camera -> lookAt(newCameraPosition - direction) ;
}

void FlyCameraController::look(const Mind::Vector2f& cursorOffset) {
    Mind::Vector2f sensibilityOffset(
        cursorOffset.get(Mind::Vector2f::X) - m_oldCursorOffset.get(Mind::Vector2f::X),
        m_oldCursorOffset.get(Mind::Vector2f::Y) - cursorOffset.get(Mind::Vector2f::Y)
    ) ;
    sensibilityOffset *= m_mouseSensibility ;

    float cameraYaw = m_cameraViewAngles.get(Mind::Vector2f::X) + sensibilityOffset.get(Mind::Vector2f::X) ;
    float cameraPitch = m_cameraViewAngles.get(Mind::Vector2f::Y) + sensibilityOffset.get(Mind::Vector2f::Y) ;
    cameraPitch = std::clamp(cameraPitch, -89.f, 89.f) ;

    m_cameraViewAngles = Mind::Vector2f(cameraYaw, cameraPitch) ;

    Mind::Vector3f cameraDirection(
        std::cos(Mind::Math::toRadians(cameraYaw)) * std::cos(Mind::Math::toRadians(cameraPitch)),
        std::sin(Mind::Math::toRadians(cameraPitch)),
        std::sin(Mind::Math::toRadians(cameraYaw)) * std::cos(Mind::Math::toRadians(cameraPitch))
    ) ;
    cameraDirection.normalize() ;
    m_camera -> lookAt(m_cameraTransform.get().translation() + cameraDirection) ;

    m_oldCursorOffset = cursorOffset ;
}
