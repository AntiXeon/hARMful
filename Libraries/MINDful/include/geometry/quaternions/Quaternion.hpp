#ifndef __MIND__GEOMETRY_QUATERNION__
#define __MIND__GEOMETRY_QUATERNION__

#include <iostream>

#include <MINDTypes.hpp>
#include <simd/SIMDVector.hpp>
#include <geometry/points/Point3Df.hpp>
#include <matrices/Matrix3x3f.hpp>

namespace Mind {
    /**
     * A Point is a very simple element that can be used in a space to place
     * elements, get distances between elements, etc.
     */
    class Quaternion final {
        public:
            /** Quaternion with all its components set to zero. */
            static const Quaternion Zero ;

            /** Quaternion with all its components set to zero but W is one. */
            static const Quaternion Identity ;

        private:
            /**
             * Axis in the Quaternion. Made to add some semantic to the code
             * instead of hardcoded values.
             */
            enum Axis { X, Y, Z, W } ;

            #ifdef USE_NO_SIMD
                /** Individual value of coordinate X. */
                Scalar m_x ;

                /** Individual value of coordinate Y. */
                Scalar m_y ;

                /** Individual value of coordinate Z. */
                Scalar m_z ;

                /** Individual value of coordinate W. */
                Scalar m_w ;
            #else
                /** Values of the Quaternion. */
                SIMD::Vector4f m_values ;

                /**
                 * Create a Quaternion from a Vector4f.
                 */
                Quaternion(const SIMD::Vector4f& values) ;
            #endif

        public:
            /**
             * Create a default Quaternion. It is initialized to a zero degree
             * rotation.
             */
            Quaternion() ;

            /**
             * Create a Quaternion from the given value, as is.
             * @param   x   Individual value of coordinate X.
             * @param   y   Individual value of coordinate Y.
             * @param   z   Individual value of coordinate Z.
             * @param   w   Individual value of coordinate W.
             */
            Quaternion(
                const Scalar& x,
                const Scalar& y,
                const Scalar& z,
                const Scalar& w
            ) ;

            /**
             * Create a Quaternion from a rotation matrix.
             * @param   matrix  Rotation matrix to generate a Quaternion from.
             */
            Quaternion(const Matrix3x3f& matrix) ;

            /**
             * Create a Quaternion from a vector and an angle.
             * @param   vector  Vector on representing the axis on which the
             *                  rotation is applied.
             * @param   angle   Angle of the rotation in radians.
             */
            Quaternion(const Vector3f& vector, const Scalar& radAngle) ;

            /**
             * Create a Quaternion from three orthonormal axis.
             * @param xAxis Values of rotation for the X axis.
             * @param yAxis Values of rotation for the Y axis.
             * @param zAxis Values of rotation for the Z axis.
             */
            Quaternion(
                const Vector3f& xAxis,
                const Vector3f& yAxis,
                const Vector3f& zAxis
            ) ;

            /**
             * Destruction of a quaternion.
             */
            virtual ~Quaternion() ;

            /**
             * Dot product between the current Quaternion and another one.
             * @param   other   Another Quaternion to compute the dot product.
             * @return  The result of the dot product.
             */
            Scalar dot(const Quaternion& other) ;

            /**
             * Norm of the Quaternion.
             * @return Norm of the Quaternion.
             */
            Scalar norm() ;

            /**
             * Set the values of the Quaternion from a rotation matrix.
             * @param matrix Rotation matrix to set the Quaternion values from.
             */
            void from(const Matrix3x3f& matrix) ;

            /**
             * Set the values of the Quaternion from axes.
             * @param xAxis Values of rotation for the X axis.
             * @param yAxis Values of rotation for the Y axis.
             * @param zAxis Values of rotation for the Z axis.
             */
            void from(
                const Vector3f& xAxis,
                const Vector3f& yAxis,
                const Vector3f& zAxis
            ) ;

            /**
             * Set the values of the Quaternion from a vector (seen as axis) and
             * an angle.
             * @param vector   Vector acting as the axis of the rotation.
             * @param radAngle Angle of the rotation in radians.
             */
            void from(const Vector3f& vector, const Scalar& radAngle) ;

            /**
             * Get the values of the Quaternion as a rotation matrix.
             * @param matrix The Matrix3x3f that will represent the same
             *               rotation than the current quaternion.
             */
            void to(Matrix3x3f& matrix) ;

            /**
             * Get the values of the Quaternion as an axis (@a vector) and an
             * angle applied on this axis.
             * @param vector   Output vector on representing the axis on which
             *                 the rotation is applied.
             * @param radAngle Output angle of the rotation in radians.
             */
            void to(Vector3f& vector, Scalar& radAngle) ;

            /**
             * Get the values of the Quaternion as a serie of three vectors, one
             * for each axis.
             * @param xAxis Values for the X axis.
             * @param yAxis Values for the Y axis.
             * @param zAxis Values for the Z axis.
             */
            void to(
                Vector3f& xAxis,
                Vector3f& yAxis,
                Vector3f& zAxis
            ) ;
    } ;
}

#endif
