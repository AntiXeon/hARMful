#ifndef __SIN_OBJECT_ROTATION_2D__
#define __SIN_OBJECT_ROTATION_2D__


#include <MINDTypes.h>
#include <geometry/points/Point2Df.h>


namespace Sin {

    /**
     * @brief   An ObjectRotation contains required data to perform a rotation :
     *          angle and pivot position.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/11
     */
    class ObjectRotation2D {
        private:
            /**
             * @brief   Pivot, center of the rotation.
             */
            Mind::Point2Df m_pivot ;

            /**
             * @brief   Angle of the rotation in degrees.
             */
            Mind::Scalar m_angle ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of an ObjectRotation2D.
             * @param   pivot   Position of the pivot.
             * @param   angle   Angle of the rotation in degrees.
             */
            ObjectRotation2D(
                             const Mind::Point2Df& pivot = Mind::Point2Df(0,0),
                             const Mind::Scalar& angle = 0.f
                            ) ;

            /**
             * @brief   Creation of an ObjectRotation2D.
             * @param   pivotX  X position of the pivot.
             * @param   pivotY  Y position of the pivot.
             * @param   angle   Angle of the rotation in degrees.
             */
            ObjectRotation2D(
                             const Mind::Scalar& pivotX,
                             const Mind::Scalar& pivotY,
                             const Mind::Scalar& angle
                            ) ;

            /**
             * @brief   Destruction of the ObjectRotation2D.
             */
            virtual ~ObjectRotation2D() ;

                                                             /*** UTILITIES ***/
            /**
             * @brief   Add (or substract) the provided one to the current angle.
             * @param   angle   Angle to add to the current one.
             */
            void addAngle(const Mind::Scalar& angle) ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Set the pivot of the rotation.
             * @param   pivot   Position of the pivot.
             */
            void setPivot(const Mind::Point2Df& pivot) ;

            /**
             * @brief   Set the pivot of the rotation.
             * @param   pivotX  X position of the pivot.
             * @param   pivotY  Y position of the pivot.
             */
            void setPivot(
                          const Mind::Scalar& pivotX,
                          const Mind::Scalar& pivotY
                      ) ;

            /**
             * @brief   Set the angle of the rotation.
             * @param   angle   Angle of the rotation in degrees.
             */
            void setAngle(const Mind::Scalar& angle) ;


            /**
             * @brief   Get the pivot of the rotation.
             * @return  Position of the pivot.
             */
            const Mind::Point2Df& getPivot() const ;

            /**
             * @brief   Get the angle of the rotation.
             * @return  Angle of the rotation in degrees.
             */
            Mind::Scalar getAngle() const ;

    } ;

} ;


#endif
