#include <scene_objects/AbstractSceneObject.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AbstractSceneObject::AbstractSceneObject() {}

    AbstractSceneObject::AbstractSceneObject(const Mind::Point2Df& position)
        : m_position(position) {}

    AbstractSceneObject::AbstractSceneObject(
                                             const Mind::Scalar& positionX,
                                             const Mind::Scalar& positionY
                                            ) : m_position(positionX, positionY) {}

    AbstractSceneObject::~AbstractSceneObject() {}


                                                             /*** UTILITIES ***/
    void AbstractSceneObject::render(
                                     const Mind::Scalar& relativeX,
                                     const Mind::Scalar& relativeY
                                    ) {
        render(Mind::Point2Df(relativeX, relativeY)) ;
    }

    void AbstractSceneObject::translate(const Mind::Point2Df& relative) {
        m_position = m_position + relative ;
    }

    void AbstractSceneObject::translate(
                                        const Mind::Scalar& relativeX,
                                        const Mind::Scalar& relativeY
                                       ) {
        m_position = m_position + (Mind::Point2Df(relativeX, relativeY)) ;
    }


                                                     /*** SETTERS / GETTERS ***/
    void AbstractSceneObject::setPosition(const Mind::Point2Df& position) {
        m_position = position ;
    }

    void AbstractSceneObject::setPosition(
                                          const Mind::Scalar& positionX,
                                          const Mind::Scalar& positionY
                                         ) {
        m_position = Mind::Point2Df(positionX, positionY) ;
    }

    const Mind::Point2Df& AbstractSceneObject::getPosition() const {
        return m_position ;
    }

} ;
