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
            /**
             * Axis in the Quaternion. Made to add some semantic to the code
             * instead of hardcoded values.
             */
            enum Axis : unsigned int { X, Y, Z, W } ;

            /** Quaternion with all its components set to zero. */
            static const Quaternion Zero ;

            /** Quaternion with all its components set to zero but W is one. */
            static const Quaternion Identity ;

        private:
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
             * Copy constructor of a Quaternion.
             * @param other The Quaternion to copy.
             */
            Quaternion(const Quaternion& other) ;

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
            Scalar dot(const Quaternion& other) const ;

            /**
             * Norm of the Quaternion.
             * @return Norm of the Quaternion.
             */
            Scalar norm() const ;

            /**
             * Normalize the current Quaternion. The norm before normalization
             * is returned.
             * @return The norm of the Quaternion before the normalization is
             *         applied.
             */
            Scalar normalize() ;

            /**
             * Compute the inverse Quaternion of the current one.
             * There is no change in the current Quaternion components values.
             * @return The inverse of the current Quaternion.
             */
            Quaternion inverse() const ;

            /**
             * Swap the current Quaternion with another one.
             * @param other The other Quaternion to swap with the current one.
             */
            void swap(Quaternion& other) ;

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

            /**
             * Access to a component of the Quaternion (read-only).
             * @param  axis  Axis to get value of.
             * @return       Value of the component on the wanted @a axis.
             */
            Scalar operator[](const Axis& axis) const ;

            /**
             * Access to a component of the Quaternion (read and write).
             * @param  axis  Axis to get value of.
             * @return       Value of the component on the wanted @a axis.
             */
            Scalar& operator[](const Axis& axis) ;

            /**
             * Set the value of the other Quaternion into the current one.
             * @param  other Another Quaternion for which the values are copied
             *               into the current one.
             * @return       Reference on the current Quaternion once it has
             *               been affected.
             */
            Quaternion& operator=(const Quaternion& other) ;

            /**
             * Addition of two Quaternions.
             * @param  other Another Quaternion that is added to the current
             *               one.
             * @return       Reference on the current Quaternion once it has
             *               been added to the @other one.
             */
            Quaternion& operator+=(const Quaternion& other) ;

            /**
             * Addition of two Quaternions.
             * @param  other Another Quaternion that is added to the current
             *               one.
             * @return       The result of the addition.
             */
            Quaternion operator+(const Quaternion& other) const ;

            /**
             * Soustraction of two Quaternions.
             * @param  other Another Quaternion that is substracted from the
             *               current one.
             * @return       Reference on the current Quaternion once it has
             *               been subtracted from the @other one.
             */
            Quaternion& operator-=(const Quaternion& other) ;

            /**
             * Soustraction of two Quaternions.
             * @param  other Another Quaternion that is substracted from the
             *               current one.
             * @return       The result of the soustraction.
             */
            Quaternion operator-(const Quaternion& other) const ;

            /**
             * Mulitplication of a Quaternion with a Scalar.
             * @param  scalar Value to multiply each component of the current
             *                Quaternion.
             * @return        Reference on the current Quaternion once it has
             *                been multiplied by @a value.
             */
            Quaternion& operator*=(const Scalar& scalar) ;

            /**
             * Mulitplication of a Quaternion with a Scalar.
             * @param  scalar Value to multiply each component of the Quaternion.
             * @return        The result of the multiplication.
             */
            Quaternion operator*(const Scalar& scalar) const ;

            /**
             * Multiplication of a Quaternion with another one.
             * Be aware that the multiplication is not commutative.
             * @param  other Another Quaternion that is multiplied with the
             *               current one.
             * @return       Reference on the current Quaternion once it has
             *               been subtracted from the @other one.
             */
            Quaternion& operator*=(const Quaternion& other) ;

            /**
             * Multiplication of a Quaternion with another one.
             * Be aware that the multiplication is not commutative.
             * @param  other Another Quaternion that is multiplied with the
             *               current one.
              * @return      The result of the multiplication.
             */
            Quaternion operator*(const Quaternion& other) const ;

            /**
             * Check if two Quaternions have the same values.
             * @param  other Another Quaternion that is compared to the current
             *               one.
             * @return       TRUE if the Quaternions have the same component
             *               values, FALSE otherwise.
             */
            bool operator==(const Quaternion& other) const ;

            /**
             * Check if two Quaternions have the different values.
             * @param  other Another Quaternion that is compared to the current
             *               one.
             * @return       TRUE if the Quaternions have different component
             *               values, FALSE otherwise.
             */
            bool operator!=(const Quaternion& other) const ;
    } ;
}

#endif
