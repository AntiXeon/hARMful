#include <scene/Transform.hpp>
#include <scene/Entity.hpp>

using namespace Hope ;

Transform::Transform(Transform* parent)
	: Node(parent),
	  m_entity(std::make_unique<Entity>(this)) {
    m_matrix.identity() ;
}

void Transform::setRotation(const Mind::Quaternion& rotation) {
    if (rotation == m_rotation) {
        return ;
    }

    m_rotation = rotation ;
    m_outdatedMatrix = true ;

    float roll ;
    float pitch ;
    float yaw ;
    m_rotation.to(roll, pitch, yaw) ;
    m_eulerAngles.set(roll, pitch, yaw) ;
}

void Transform::setRotationOnX(const float rotation) {
    if (m_eulerAngles.get(Mind::Vector3f::X) == rotation) {
        return ;
    }

    m_eulerAngles.set(Mind::Vector3f::X, rotation) ;

    // Apply to quaternion.
    Mind::Quaternion newRotation ;
    newRotation.from(
        m_eulerAngles[Mind::Vector3f::X],
        m_eulerAngles[Mind::Vector3f::Y],
        m_eulerAngles[Mind::Vector3f::Z]
    ) ;

    if (newRotation != m_rotation) {
        m_rotation = newRotation ;
        m_outdatedMatrix = true ;
    }
}

void Transform::setRotationOnY(const float rotation) {
    if (m_eulerAngles.get(Mind::Vector3f::Y) == rotation) {
        return ;
    }

    m_eulerAngles.set(Mind::Vector3f::Y, rotation) ;

    // Apply to quaternion.
    Mind::Quaternion newRotation ;
    newRotation.from(
        m_eulerAngles[Mind::Vector3f::X],
        m_eulerAngles[Mind::Vector3f::Y],
        m_eulerAngles[Mind::Vector3f::Z]
    ) ;

    if (newRotation != m_rotation) {
        m_rotation = newRotation ;
        m_outdatedMatrix = true ;
    }
}

void Transform::setRotationOnZ(const float rotation) {
    if (m_eulerAngles.get(Mind::Vector3f::Z) == rotation) {
        return ;
    }

    m_eulerAngles.set(Mind::Vector3f::Z, rotation) ;

    // Apply to quaternion.
    Mind::Quaternion newRotation ;
    newRotation.from(
        m_eulerAngles[Mind::Vector3f::X],
        m_eulerAngles[Mind::Vector3f::Y],
        m_eulerAngles[Mind::Vector3f::Z]
    ) ;

    if (newRotation != m_rotation) {
        m_rotation = newRotation ;
        m_outdatedMatrix = true ;
    }
}

void Transform::setTranslation(const Mind::Vector3f& translation) {
    if (m_translation == translation) {
        return ;
    }

    m_translation = translation ;
    m_outdatedMatrix = true ;
}

void Transform::setScale(const float scale) {
    if (m_scale.get(Mind::Vector3f::X) == scale) {
        return ;
    }

    setScale3D(Mind::Vector3f(scale, scale, scale)) ;
}

void Transform::setScale3D(const Mind::Vector3f& scale) {
    if (m_scale == scale) {
        return ;
    }

    m_scale = scale ;
    m_outdatedMatrix = true ;
}

void Transform::setMatrix(const Mind::Matrix4x4f& matrix) {
    if (m_matrix == matrix) {
         return ;
    }

    m_matrix = matrix ;
    m_outdatedMatrix = false ;

    // Decompose the matrix to rotation, translation and scale.
    m_matrix.decompose(m_translation, m_rotation, m_scale) ;
}


Mind::Quaternion Transform::rotation() const {
    return m_rotation ;
}

float Transform::rotationOnX() const {
    return m_eulerAngles.get(Mind::Vector3f::X) ;
}

float Transform::rotationOnY() const {
    return m_eulerAngles.get(Mind::Vector3f::Y) ;
}

float Transform::rotationOnZ() const {
    return m_eulerAngles.get(Mind::Vector3f::Z) ;
}

Mind::Vector3f Transform::translation() const {
    return m_translation ;
}

float Transform::scale() const {
    return m_scale.get(Mind::Vector3f::X) ;
}

Mind::Vector3f Transform::scale3D() const {
    return m_scale ;
}

const Mind::Matrix4x4f& Transform::matrix() {
    if (m_outdatedMatrix) {
        // Recompose the matrix from the different component values.
        m_matrix.compose(m_translation, m_rotation, m_scale) ;
        m_outdatedMatrix = false ;
    }

    return m_matrix ;
}
