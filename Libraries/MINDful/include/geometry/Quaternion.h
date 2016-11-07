#ifndef __MIND_QUATERNION__
#define __MIND_QUATERNION__

#include <simd/SIMDVector.h>
#include <matrices/Matrix3x3f.h>
#include <matrices/Matrix4x4f.h>
#include <geometry/points/Point3Df.h>


namespace Mind {

    /**
    * @brief    Quaternion allows to perform rotations in four dimensions.
    *           This additional dimension makes rotations more efficient,
    *           allowing smooth rotations, and avoids gimbal lock.
    * @author  CB (c) 2014
    * @version 0.1 2015/09/12
    */
    class Quaternion {
        private:
            /** @brief  Flag to know if the Quaternion is normalized. */
            bool m_normalized ;

            /** @brief  Values of the Quaternion. */
            SIMD::Vector4f m_values ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /** @brief  Create a Quaternion of a zero degree rotation. */
            Quaternion() ;

            /**
             * @brief   Create a Quaternion from a SIMD Vector4f.
             * @param   vector  Vector4f containing the values to put into the
             *                  new Quaternion.
             */
            Quaternion(const SIMD::Vector4f& vector) ;

            /**
             * @brief   Create a Quaternion initialized to the given values.
             * @param   x   Value on dimension X.
             * @param   y   Value on dimension Y.
             * @param   z   Value on dimension Z.
             * @param   w   Value on dimension W.
             */
            Quaternion(
                       const Scalar& x,
                       const Scalar& y,
                       const Scalar& z,
                       const Scalar& w = 0.f
                      ) ;

            /**
             * @brief   Create a Quaternion from a rotation matrix.
             * @param   matrix  Rotation matrix from which the Quaternion is
             *                  built-on.
             */
            Quaternion(const Matrix3x3f& matrix) ;

            /**
             * @brief   Create a Quaternion from a rotation matrix.
             * @param   matrix  Rotation matrix from which the Quaternion is
             *                  built-on.
             */
            Quaternion(const Matrix4x4f& matrix) ;

            /**
             * @brief   Create a Quaternion from axis and angle value.
             * @param   axis    Axis on which rotation is applied.
             * @param   angle   Angle to apply to perform a rotation (radians).
             */
            Quaternion(const Vector3f& axis, const Scalar& angle) ;

            /** @brief  Destruction of the Quaternion. */
            virtual ~Quaternion() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Compute the dot product between the current Quaternion
             *          and another one.
             * @param   other   The other Quaternion implied in the dot product.
             * @return  Scalar value of the dot product.
             */
            Scalar dot(const Quaternion& other) const ;

            /**
             * @brief  Normalize the current Quaternion if its norm is not zero.
             */
            void normalize() ;

            /**
             * @brief   Get the normalized version of the current Quaternion,
             *          without modifying it.
             * @return  A Quaternion being equal to the normalized current one.
             *          If the norm of the Quaternion is zero, a Quaternion
             *          containing only zeroes is returned instead.
             */
            Quaternion normalized() ;

            /**
             * @brief   Check if a Quaternion is normalized.
             * @return  TRUE if the norm is equal to one, FALSE else.
             */
            bool isNormalized() ;

            /**
             * @brief   Get the length of the Quaternion.
             * @return  The length of the Quaternion.
             */
            Scalar length() ;

            /**
             * @brief   Get the norm of the Quaternion.
             * @return  The norm of the Quaternion.
             */
            Scalar norm() ;

            /**
             * @brief   Check if the current Quaternion and another one
             *          have the same orientation.
             * @param   other   The other Quaternion to compare to.
             * @param   error   Error to consider two Quaternions are equal.
             */
            bool equals(
                        const Quaternion& other,
                        const Scalar& error = 1e-3
                       ) ;

            /**
             * @brief   Check if the current Quaternion and another one
             *          represent the same rotation.
             * @param   other   The other Quaternion to compare to.
             * @param   error   Error to consider two Quaternions are equal.
             */
            bool strictlyEquals(
                                const Quaternion& other,
                                const Scalar& error = 1e-3
                               ) ;

            /** @brief  Compute the invert of the current Quaternion. */
            void invert() ;

            /** @brief  Get the conjugate of the current Quaternion. */
            Quaternion conjugate() ;

            /**
             * @brief   Set the current Quaternion so that it represents the
             *          given rotation matrix.
             * @param   input   Matrix to represent as the current Quaternion.
             */
            void fromMatrix(const Matrix3x3f& input) ;

            /**
             * @brief   Set the current Quaternion so that it represents the
             *          given rotation matrix.
             * @param   input   Matrix to represent as the current Quaternion.
             */
            void fromMatrix(const Matrix4x4f& input) ;

            /**
             * @brief   Convert the current Quaternion to a rotation matrix.
             * @param   output  Matrix in which are put the corresponding
             *                  values of the current rotation in the
             *                  Quaternion.
             * @return  The same reference as parameter output for convenient
             *          use.
             */
            Matrix3x3f& toMatrix(Matrix3x3f& output) ;

            /**
             * @brief   Convert the current Quaternion to a rotation matrix.
             * @param   output  Matrix in which are put the corresponding
             *                  values of the current rotation in the
             *                  Quaternion.
             * @return  The same reference as parameter output for convenient
             *          use.
             */
            Matrix4x4f& toMatrix(Matrix4x4f& output) ;


            /**
             * @brief   Put the result of a Spherical Linear Interpolation
             *          between two Quaternions into the current one.
             * @param   from    Starting rotation.
             * @param   to      Ending rotation.
             * @param   time    Normalized time between the two Quaternions.
             * @warning SLERP allows constant velocity. Yet it is not
             *          commutative.
             */
            void slerp(
                       const Quaternion& from,
                       const Quaternion& to,
                       const Scalar& time
                      ) ;

            /**
             * @brief   Put the result of a Normalized Linear Interpolation
             *          between two Quaternions into the current one.
             * @param   from    Starting rotation.
             * @param   to      Ending rotation.
             * @param   time    Normalized time between the two Quaternions.
             * @warning NLERP is commutative but velocity is not constant.
             *          However, it is faster than SLERP...
             */
            void nlerp(
                       const Quaternion& from,
                       const Quaternion& to,
                       const Scalar& time
                      ) ;

            /**
             * @brief   Put the result of a Linear Interpolation between two
             *          Quaternions into the current one.
             * @param   from    Starting rotation.
             * @param   to      Ending rotation.
             * @param   time    Normalized time between the two Quaternions.
             * @warning LERP is commutative but velocity is not constant.
             *          However, it is faster than SLERP...
             */
            void lerp(
                      const Quaternion& from,
                      const Quaternion& to,
                      const Scalar& time
                     ) ;


            /**
             * @brief   Compute the Spherical Linear Interpolation between two
             *          Quaternions at a specified normalized time.
             * @param   from    Starting rotation.
             * @param   to      Ending rotation.
             * @param   time    Normalized time between the two Quaternions.
             * @param   result  Resulting quaternion. Its original values are
             *                  erased to contain the interpolation results.
             * @warning SLERP allows contant velocity. Yet it is not
             *          commutative.
             */
            static void slerp(
                              const Quaternion& from,
                              const Quaternion& to,
                              const Scalar& time,
                              Quaternion& result
                             ) ;

            /**
             * @brief   Compute the Normalized Linear Interpolation between two
             *          Quaternions at a specified normalized time.
             * @param   from    Starting rotation.
             * @param   to      Ending rotation.
             * @param   time    Normalized time between the two Quaternions.
             * @param   result  Resulting quaternion. Its original values are
             *                  erased to contain the interpolation results.
             * @warning NLERP is commutative but velocity is not constant.
             *          However, it is faster than SLERP...
             */
            static void nlerp(
                              const Quaternion& from,
                              const Quaternion& to,
                              const Scalar& time,
                              Quaternion& result
                             ) ;

            /**
             * @brief   Compute the Linear Interpolation between two Quaternions
             *          at a specified normalized time.
             * @param   from    Starting rotation.
             * @param   to      Ending rotation.
             * @param   time    Normalized time between the two Quaternions.
             * @param   result  Resulting quaternion. Its original values are
             *                  erased to contain the interpolation results.
             * @warning NLERP is commutative but velocity is not constant.
             *          However, it is faster than SLERP...
             */
            static void lerp(
                             const Quaternion& from,
                             const Quaternion& to,
                             const Scalar& time,
                             Quaternion& result
                            ) ;


        private:
            /**
             * @brief   Compute SLERP on SIMD enabling parallelization.
             *          It is not intended to be executed on CPU having not such
             *          instructions extensions.
             * @param   from    Starting rotation.
             * @param   to      Ending rotation.
             * @param   time    Normalized time between the two Quaternions.
             * @param   result  Resulting quaternion. Its original values are
             *                  erased to contain the interpolation results.
             */
            static void slerpSIMD(
                                  const Quaternion& from,
                                  const Quaternion& to,
                                  const Scalar& time,
                                  Quaternion& result
                                 ) ;

            /**
             * @brief   Common code for computing the scalar coefficient of
             *          SLERP. This is the speed up core of the SLERP methods,
             *          using an approximation of sine formulas by polynomial
             *          functions. This allows the use of only additions and
             *          multiplications (ie. fast operations) over sine
             *          functions (ie. slow operations).
             * @param   time        Vectorized value of time between the two
             *                      input Quaternions of SLERP related methods.
             * @param   dotMinusOne Vectorized result of the dot product between
             *                      the two input Quaternions of SLERP related
             *                      methods, from which one has been
             *                      substracted.
             * @param   result      Output vectorized result.
             */
            static void slerpSIMDCoefficient(
                                             const SIMD::Vector4f& time,
                                             const SIMD::Vector4f& dotMinusOne,
                                             SIMD::Vector4f& result
                                            ) ;

            /**
             * @brief   Compute SLERP on FPU.
             *          It is not intended to be executed on CPU having SIMD
             *          extensions as slerpSIMD speeds up computations.
             * @param   from    Starting rotation.
             * @param   to      Ending rotation.
             * @param   time    Normalized time between the two Quaternions.
             * @param   result  Resulting quaternion. Its original values are
             *                  erased to contain the interpolation results.
             * @see     Quaternion::slerpSIMD
             */
            static void slerpFPU(
                                 const Quaternion& from,
                                 const Quaternion& to,
                                 const Scalar& time,
                                 Quaternion& result
                                ) ;



        public:
                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Set the rotation by applying an angle on axis.
             * @param   axis    Axis on which rotation is applied.
             * @param   angle   Angle to apply to perform a rotation (radians).
             */
            void setRotation(const Vector3f& axis, const Scalar& angle) ;


            /**
             * @brief   Get the X value of the Quaternion.
             * @return  X value.
             */
            Scalar getX() const ;

            /**
             * @brief   Get the Y value of the Quaternion.
             * @return  Y value.
             */
            Scalar getY() const ;

            /**
             * @brief   Get the Z value of the Quaternion.
             * @return  Z value.
             */
            Scalar getZ() const ;

            /**
             * @brief   Get the W value of the Quaternion.
             * @return  W value.
             */
            Scalar getW() const ;

            /**
             * @brief   Get the coordinates of the Quaternion.
             * @param   output  Output parameter that will contain the four
             *                  coordinates of the Quaternion.
             * @return  The same array as the @a output parameter for convenient
             *          use.
             */
            AlignedArray4f& getCoordinates(AlignedArray4f& output) const ;


                                                             /*** OPERATORS ***/
                                                                  /** ACCESS **/
            /**
             * @brief   Access individual data of the Quaternion.
             * @param   index   Index of the data to get.
             * @return  The corresponding value of the Quaternion.
             */
            Scalar operator[] (const size_t index) const ;

            /**
             * @brief   Access individual data of the Quaternion.
             * @param   index   Index of the data to get.
             * @return  The corresponding value of the Quaternion.
             */
            Scalar& operator[] (const size_t index) ;


                                                             /** COMPARISONS **/
            /**
             * @brief   Equality operator.
             * @param   other   The other Quaternion to compare to.
             * @return TRUE if two Quaternions are equal. FALSE otherwise.
             */
            bool operator== (const Quaternion& other) const ;

            /**
             * @brief   Inequality operator.
             * @param   other   The other Quaternion to compare to.
             * @return TRUE if two Quaternions are different. FALSE otherwise.
             */
            bool operator!= (const Quaternion& other) const ;


                                                             /** AFFECTATION **/
            /**
             * @brief   Assignment operator.
             * @param   matrix  Matrix to set the corresponding values into the
             *                  current Quaternion.
             * @return  The current Quaternion with the value of the matrix.
             */
            Quaternion& operator= (const Matrix3x3f& matrix) ;

            /**
             * @brief   Assignment operator.
             * @param   matrix  Matrix to set the corresponding values into the
             *                  current Quaternion.
             * @return  The current Quaternion with the value of the matrix.
             */
            Quaternion& operator= (const Matrix4x4f& matrix) ;


                                                                  /** SCALES **/
            /**
             * @brief   Get the product of the current Quaternion with another
             *          Quaternion.
             * @param   other   Rotation by another Quaternion.
             * @return  The product of the current Quaternion by the other one.
             */
            Quaternion operator* (const Quaternion& other) const ;

            /**
             * @brief   Get a scaled version of the current Quaternion.
             * @param   factor  Factor by which the current Quaternion is
             *                  scaled.
             * @return  A copy of the current Quaternion scaled by the factor.
             */
            Quaternion operator* (const Scalar& factor) const ;

            /**
             * @brief   Scale the current Quaternion.
             * @param   factor  Factor of the scale.
             * @return  The current Quaternion, scaled by the given factor.
             */
            Quaternion& operator*= (const Scalar& factor) ;

            /**
             * @brief   Get the product of the current Quaternion with another
             *          Quaternion.
             * @param   other   Rotation by another Quaternion.
             * @return  The current Quaternion after it has been multiplied with
             *          the other one.
             */
            Quaternion& operator*= (const Quaternion& other) ;

            /**
             * @brief   Get an inversely scaled version of the current
             *          Quaternion.
             * @param   factor  Factor by which the Quaternion is to be scaled.
             * @return  A scaled copy of the current Quaternion.
             */
            Quaternion operator/ (const Scalar& factor) const ;

            /**
             * @brief   Inversely scale the current Quaternion.
             * @param   factor  Factor by which the Quaternion is to be scaled.
             * @return  The current Quaternion after it has been scaled.
             */
            Quaternion& operator/= (const Scalar &factor) ;


                                                               /** ADDITIONS **/
            /**
             * @brief   Add two Quaternions.
             * @param   other   The other Quaternion to add to the current one.
             * @return  Result of the addition.
             */
            Quaternion operator+ (const Quaternion& other) const ;

            /**
             * @brief   Add a Quaternion to the current one.
             * @param   other   The other Quaternion to add to the current one.
             * @return  The current Quaternion as a result of the addition.
             */
            Quaternion& operator+= (const Quaternion& other) ;


                                                   /** DIFFERENCE - NEGATIVE **/
            /**
             * @brief   Negative Quaternion.
             * @return  The negative version of the current Quaternion.
             */
            Quaternion operator- () const ;

            /**
             * @brief   Substract two Quaternions.
             * @param   other   The other Quaternion involved in difference.
             * @return  The difference between the current Quaternion and the
             *          other one.
             */
            Quaternion operator- (const Quaternion& other) const ;

            /**
             * @brief   Substract the current Quaternion to another one.
             * @param   other   The other Quaternion to substract to the current
             *                  one.
             * @return  The current Quaternion as a result of the difference.
             */
            Quaternion& operator-= (const Quaternion& other) ;

    } ;

} ;


#endif
