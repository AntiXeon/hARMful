#include <main_rendering/Camera.h>
#include <CommonSINStrings.h>
#include <debug/Log.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    Camera::Camera(const Mind::Dimension2Df& frustum)
        : m_frustum(frustum) {}

    Camera::~Camera() {}

                                                             /*** UTILITIES ***/
    void Camera::attachTo(AbstractEntityInstance* entity) {
        AttachIterator entityPosition = search(entity) ;
        if (entityPosition == m_attachedTo.end()) {
            // Not found.
            m_attachedTo.push_back(entity) ;
        }
    }

    void Camera::detachFrom(AbstractEntityInstance* entity) {
        AttachIterator entityPosition = search(entity) ;
        if (entityPosition != m_attachedTo.end()) {
            // Found.
            m_attachedTo.erase(entityPosition) ;
        }
        else {
            Doom::Log::Write(
                             Doom::Log::LogWarning,
                             CameraMsg::Warning::EntityNotFound,
                             entity
                            ) ;
        }
    }

    Camera::AttachIterator Camera::search(AbstractEntityInstance* entity) {
        // Linear search...
        AttachIterator entityPosition = m_attachedTo.begin() ;
        for (; entityPosition != m_attachedTo.end() ; ++entityPosition) {
            if (*entityPosition == entity) {
                // Found.
                return entityPosition ;
            }
        }
        // Not found.
        return m_attachedTo.end() ;
    }

                                                     /*** SETTERS / GETTERS ***/
    void Camera::setFrustum(const Mind::Dimension2Df& frustum) {
        m_frustum = frustum ;
    }

    void Camera::setFrustum(
                            const Mind::Scalar& width,
                            const Mind::Scalar& height
                           ) {
        m_frustum.set(width, height) ;
    }

} ;
