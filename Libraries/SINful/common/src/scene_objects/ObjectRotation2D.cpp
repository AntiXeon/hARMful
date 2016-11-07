#include <scene_objects/ObjectRotation2D.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ObjectRotation2D::ObjectRotation2D(
                                       const Mind::Point2Df& pivot,
                                       const Mind::Scalar& angle
                                      ) : m_pivot(pivot),
                                          m_angle(angle) {}

    ObjectRotation2D::ObjectRotation2D(
                                       const Mind::Scalar& pivotX,
                                       const Mind::Scalar& pivotY,
                                       const Mind::Scalar& angle
                                   ) : m_pivot(Mind::Point2Df(pivotX, pivotY)),
                                       m_angle(angle) {}

    ObjectRotation2D::~ObjectRotation2D() {}


                                                             /*** UTILITIES ***/
    void ObjectRotation2D::addAngle(const Mind::Scalar& angle) {
        m_angle += angle ;
    }


                                                     /*** SETTERS / GETTERS ***/
    void ObjectRotation2D::setPivot(const Mind::Point2Df& pivot) {
        m_pivot = pivot ;
    }

    void ObjectRotation2D::setPivot(
                                    const Mind::Scalar& pivotX,
                                    const Mind::Scalar& pivotY
                                   ) {
        m_pivot = Mind::Point2Df(pivotX, pivotY) ;
    }

    void ObjectRotation2D::setAngle(const Mind::Scalar& angle) {
        m_angle = angle ;
    }


    const Mind::Point2Df& ObjectRotation2D::getPivot() const {
        return m_pivot ;
    }

    Mind::Scalar ObjectRotation2D::getAngle() const {
        return m_angle ;
    }

} ;
