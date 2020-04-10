#include <scene/Transform.hpp>
#include <scene/Entity.hpp>

using namespace Hope ;

Transform::Transform(Transform* parent)
	: Node(parent),
	  m_entity(std::make_unique<Entity>(this)) {
    m_localMatrix.identity() ;
	m_worldMatrix.identity() ;
}

void Transform::setRotation(const Mind::Quaternion& rotation) {
    if (rotation == m_rotation) {
        return ;
    }

    m_rotation = rotation ;
    m_outdatedLocal = true ;
	notifyWorldChangeToChildren() ;

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
        m_outdatedLocal = true ;
		notifyWorldChangeToChildren() ;
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
        m_outdatedLocal = true ;
		notifyWorldChangeToChildren() ;
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
        m_outdatedLocal = true ;
		notifyWorldChangeToChildren() ;
    }
}

void Transform::setTranslation(const Mind::Vector3f& translation) {
    if (m_translation == translation) {
        return ;
    }

    m_translation = translation ;
    m_outdatedLocal = true ;
	notifyWorldChangeToChildren() ;
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
    m_outdatedLocal = true ;
	notifyWorldChangeToChildren() ;
}

void Transform::setLocal(const Mind::Matrix4x4f& matrix) {
    if (m_localMatrix == matrix) {
         return ;
    }

    m_localMatrix = matrix ;
    m_outdatedLocal = false ;

    // Decompose the matrix to rotation, translation and scale.
    m_localMatrix.decompose(m_translation, m_rotation, m_scale) ;
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

const Mind::Matrix4x4f& Transform::local() {
    if (m_outdatedLocal) {
        // Recompose the matrix from the different component values.
        m_localMatrix.compose(m_translation, m_rotation, m_scale) ;
        m_outdatedLocal = false ;
		notifyWorldChangeToChildren() ;
    }

    return m_localMatrix ;
}

const Mind::Matrix4x4f& Transform::world() {
	auto* parentNode = parent() ;

	if (!parentNode) {
		m_worldMatrix = local() ;
		m_outdatedWorld = false ;
	}
	else if (m_outdatedWorld) {
		auto* parentTransform = static_cast<Transform*>(parentNode) ;

		m_worldMatrix = (parentTransform -> world()) * local() ;
		m_outdatedWorld = false ;
	}

	return m_worldMatrix ;
}

void Transform::notifyWorldChangeToChildren() {
	m_outdatedWorld = true ;
	
	auto childTransforms = children() ;

	for (auto* child: childTransforms) {
		Transform* childTransform = static_cast<Transform*>(child) ;
		childTransform -> notifyWorldChangeToChildren() ;
	}
}
