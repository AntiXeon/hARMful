#ifndef __MIND__SIMD_VECTOR4_FLOAT__
#define __MIND__SIMD_VECTOR4_FLOAT__

#include <simd/SIMDTypes.hpp>
#include <MINDTypes.hpp>
#include <typeinfo>

#include <simd/intel_sse2/integers/SIMDVector4.hpp>
#include <simd/intel_sse2/integers/SIMDVector4i.hpp>
#include <simd/intel_sse2/integers/SIMDVector4ui.hpp>

namespace Mind {
    namespace SSE2 {
        /**
         * A vector of four single float values.
         * Used to optimize operations on such data structure by using SSE2
         * instructions on Intel/AMD CPUs.
         *
         * This class is highly inspired by the work of Agner Fog.
         * http://www.agner.org/optimize/
         */
        class Vector4f {
            public:
                #include "impl/Vector4f/Mask/inner.hpp"

            private:
                /** Inner vector data. */
                float32x4_t m_inner ;


                /**
                 * Get the combination of two inner objects. It
                 * follows this case:
                 * <code>dst[i] = selector[i] ? a[i] : b[i] ;</code>
                 * @param     selector     Mask to select elements from a if TRUE,
                 *             from b if FALSE.
                 * @param     a             First vector to pick values in.
                 * @param     b             Second vector to pick values in.
                 * @return    An inner data object combining @a a and @a b
                 * following the content of @a selector.
                 */
                static float32x4_t selection(
                    const float32x4_t& selector,
                    const float32x4_t& a,
                    const float32x4_t& b
                ) ;


            public:
                                              /** CONSTRUCTION / DESTRUCTION **/
                /**
                 * Create an empty vector.
                 */
                Vector4f() ;

                /**
                 * Create a Vector4f defining all its values.
                 * @param   f1  First component of the Vector4f.
                 * @param   f2  Second component of the Vector4f.
                 * @param   f3  Third component of the Vector4f.
                 * @param   f4  Fourth component of the Vector4f.
                 */
                Vector4f(
                    const Scalar& f1,
                    const Scalar& f2,
                    const Scalar& f3 = 0.f,
                    const Scalar& f4 = 0.f
                ) ;

                /**
                 * Create a Vector4f in which all values are the given one.
                 * @param   value   The value to copy in the four components of
                 *                  the Vector4f.
                 */
                Vector4f(const Scalar& value) ;

                /**
                 * Create directly from internally used data type.
                 * @param   vec     Data using the inner data type.
                 */
                Vector4f(const float32x4_t& vec) ;

                /**
                 * Destruction of the Vector4f.
                 */
                virtual ~Vector4f() ;


                                                              /*** UTILITIES ***/
                /**
                 * Compute the sum of elements in the Vector4f.
                 * @return     The sum of all elements in Vector4f.
                 */
                Scalar horizontalAdd() ;

                /**
                 * Compute the difference of elements in the Vector4f.
                 * @return     The difference of all elements in Vector4f.
                 */
                Scalar horizontalSub() ;

                /**
                 * Make all values of the current Vector4f to absolute values.
                 */
                void abs() ;

                /**
                 * Multiply each value of the current Vector4f by itself.
                 */
                void squared() ;

                /**
                 * Permute elements in the current Vector4f.
                 * The new positions are set into the template.
                 * Positions can be set between 0 and 3 for existing positions.
                 * If position is set to -1, it is zeroed.
                 * <code>
                 * Vector4f vec4f ;
                 *            // Rotate positions.
                 * permute<3,0,1,2>(vec4f) ;
                 * // Zero in the first value.
                 * permute<-1,1,2,3>(vec4f) ;
                 * </code>
                 * @warning Cause an assertion fail if template values are not
                 *          inside interval [-1 ; 3].
                 */
                template <int i0, int i1, int i2, int i3>
                void permute() ;

                /**
                 * Change the sign of elements in the current Vector4f.
                 * <code>
                 * Vector4f vec4f ;
                 * // Invert sign of first value
                 * changeSign<1,0,0,0>(vec4f) ;
                 * </code>
                 */
                template <bool i0, bool i1, bool i2, bool i3>
                void changeSign() ;


                                                  /** CONDITIONAL ARITHMETIC **/
                /**
                 * Add elements of another Vector4f for which the mask is true:
                 * <code>
                 * this[i] = mask[i] ? this[i] + add[i] : this[i] ;
                 * </code>
                 * @param     mask     Mask to add some elements only.
                 * @param     add     The Vector4f to add to the current one for
                 *                     values being TRUE in the Mask.
                 */
                void addIf(const Mask& mask, const Vector4f& add) ;

                /**
                 * Multiply elements of another Vector4f for which the mask is
                 * true:
                 * <code>
                 * this[i] = mask[i] ? this[i] * mul[i] : this[i] ;
                 * </code>
                 * @param     mask     Mask to add some elements only.
                 * @param     mul      The Vector4f to mulitply to the current
                 *                     one for values being TRUE in the Mask.
                 */
                void mulIf(const Mask& mask, const Vector4f& mul) ;

                /**
                 * Get the dot product of the current Vector4f with another one.
                 * @param     other     The other Vector4f to compute dot product.
                 * @return     Dot product of the two Vector4f.
                 */
                Scalar dot(const Vector4f& other) const ;

                /**
                 * Compute the cross product of the current Vector4f with an @a
                 * other one.
                 * @param  other The second operand of the cross product.
                 * @return       Resulting Vector4f of the cross product.
                 */
                Vector4f cross(const Vector4f& other) const ;

                /**
                 * Compute the norm of the Vector4f.
                 * @return     The norm of the Vector4f.
                 */
                Scalar norm() const ;


                                                        /** STATIC FUNCTIONS **/
                /**
                 * Get the combination of two Vector4f objects. It follows this
                 * case:
                 * <code>dst[i] = selector[i] ? a[i] : b[i] ;</code>
                 * @param     selector     Mask to select elements from a if TRUE,
                 *             from b if FALSE.
                 * @param     a             First Vector4f to pick values in.
                 * @param     b             Second Vector4f to pick values in.
                 * @return    A Vector4f combining @a a and @a b following the
                 *          content of @a selector.
                 */
                static Vector4f select(
                    const Mask& selector,
                    const Vector4f& a,
                    const Vector4f& b
                ) ;

                /**
                 * Shuffle the values in a Vector4f and return the corresponding
                 * result.
                 * @param     input     Vector from which value must be shuffled.
                 * @param     output    Resulting shuffle.
                 * @return    Same reference as @a output for convenient use.
                 */
                template <unsigned char i0, unsigned char i1, unsigned char i2, unsigned char i3>
                static Vector4f& shuffle(
                    const Vector4f& input,
                    Vector4f& output
                ) ;

                /**
                 * Get a minimal Vector4f. It is the consensus of a and b,
                 * picking only the smallest value for a given element:
                 * <code>
                 * dst[i] = min(a[i], b[i]) ;
                 * </code>
                 * @param     a     First Vector4f to test.
                 * @param     b     Second Vector4f to test.
                 * @return     A Vector4f containing the minimal values contained
                 *          in a or b.
                 */
                static Vector4f min(const Vector4f& a, const Vector4f& b) ;

                /**
                 * Get a maximal Vector4f. It is the consensus of a and b,
                 * picking only the greatest value for a given element:
                 * <code>
                 * dst[i] = max(a[i], b[i]) ;
                 * </code>
                 * @param     a     First Vector4f to test.
                 * @param     b     Second Vector4f to test.
                 * @return     A Vector4f containing the maximal values contained
                 *          in a or b.
                 */
                static Vector4f max(const Vector4f& a, const Vector4f& b) ;

                /**
                 * Get a copy of the given Vector4f in which all elements are
                 * absolute values.
                 * @param     vec     Vector4f to get its absolute values.
                 * @return     Vector4f in which the values are absolute values
                 *          from @a vec.
                 */
                static Vector4f abs(const Vector4f& vec) ;

                /**
                 * Compute squareroot for each element of @a vec.
                 * @param     vec     Values for which to get squareroot.
                 * @return     A Vector4f containing the squareroots of elements
                 *          from @a vec.
                 */
                static Vector4f sqrt(const Vector4f& vec) ;

                /**
                 * Square the values of a Vector4f.
                 * @param     vec        Values for which to get squared values.
                 * @return     A Vector4f containing the squared values of @a vec.
                 */
                static Vector4f square(const Vector4f& vec) ;

                /**
                 * Get the dot product of a Vector4f.
                 * @param     a    First Vector4f in dot product.
                 * @param     b    Second Vector4f in dot product.
                 * @return     The dot product of the given Vector4f.
                 */
                static Scalar dot(const Vector4f& a, const Vector4f& b) ;

                /**
                 * Get the cross product of a Vector4f.
                 * @param     a    First Vector4f in cross product.
                 * @param     b    Second Vector4f in cross product.
                 * @return     The cross product of the given Vector4f.
                 */
                static Vector4f cross(const Vector4f& a, const Vector4f& b) ;


                                                 /** APPROXIMATE - FAST MATH **/
                /**
                 * Compute for each element of @a vec 1 / @a vec[i].
                 * The maximum relative error for this approximation is
                 * less than 1.5*2^-12.
                 * @param     vec     The Vector4f for which compute the
                 *                  reciprocal.
                 * @return     The reciprocal of @a vec.
                 */
                static Vector4f fast_recriprocal(const Vector4f& vec) ;

                /**
                 * Compute for each element of @a vec
                 * 1 / sqrt(@a vec[i]).
                 * The maximum relative error for this approximation is
                 * less than 1.5*2^-12.
                 * @param     vec     Vector4f for which compute the reverse
                 *                     squareroot.
                 * @return  Vector4f containing the reverse squareroot of each
                 *          element in @a vec.
                 */
                static Vector4f fast_rsqrt(const Vector4f& vec) ;

                /**
                 * Compute for each element of @a vec sqrt(@a vec[i]).
                 * The maximum relative error for this approximation is
                 * less than 1.5*2^-12.
                 * @param     vec     Vector4f for which compute the squareroot.
                 * @return  Vector4f containing the squareroot of each element
                 *          in @a vec.
                 */
                static Vector4f fast_sqrt(const Vector4f& vec) ;


                                                        /** FUSED OPERATIONS **/
                /**
                 * Multiply two Vector4f then add a third one.
                 * @param     mula     First operand of the multiplication.
                 * @param     mulb     Second operand of the multiplication.
                 * @param     add     The Vector4f to add to the product of
                 *                        @a mula by @a mulb.
                 * @return     The result of the operation.
                 */
                static Vector4f mul_add(
                    const Vector4f& mula,
                    const Vector4f& mulb,
                    const Vector4f& add
                ) ;

                /**
                 * Multiply two Vector4f then substract a third one.
                 * @param     mula     First operand of the multiplication.
                 * @param     mulb     Second operand of the multiplication.
                 * @param     sub     The Vector4f to substract to the product of
                 *                  @a mula by @a mulb.
                 * @return     The result of the operation.
                 */
                static Vector4f mul_sub(
                    const Vector4f& mula,
                    const Vector4f& mulb,
                    const Vector4f& sub
                ) ;

                /**
                 * Substract a Vector to the product of others.
                 * @param     sub     The Vector4f to be substracted.
                 * @param     mula     First operand of the multiplication.
                 * @param     mulb     Second operand of the multiplication.
                 * @return     The result of the operation.
                 */
                static Vector4f sub_mul(
                    const Vector4f& sub,
                    const Vector4f& mula,
                    const Vector4f& mulb
                ) ;

                /**
                 * Transpose a 4x4 matrix.
                 * @param     row1     First row of the matrix in which first
                 *                     column is put as output.
                 * @param     row2     Second row of the matrix in which second
                 *                     column is put as output.
                 * @param     row3     Third row of the matrix in which third
                 *                     column is put as output.
                 * @param     row4     Fourth row of the matrix in which fourth
                 *                     column is put as output.
                 */
                static void transposeMatrix(
                    Vector4f& row1,
                    Vector4f& row2,
                    Vector4f& row3,
                    Vector4f& row4
                ) ;


                                                     /*** GETTERS / SETTERS ***/
                /**
                 * Get a Mask in which elements are TRUE for negative element
                 * in the current Vector4f, FALSE for positive elements in the
                 * current Vector4f.
                 * Works also for -0.0, -INF and -NaN.
                 * @return     A Mask containing TRUE for negative elements in the
                 *          current Vector4f.
                 */
                Mask isNegative() ;

                /**
                 * Get a Mask in which elements are TRUE for infinite
                 * values in current Vector4f, FALSE for finite values.
                 * @return     A Mask containing TRUE for infinite elements in the
                 *          current Vector4f.
                 */
                Mask isInfinite() ;

                /**
                 * Get a Mask in which elements are TRUE for NaN values in
                 * current Vector4f, FALSE for determined values.
                 * NaN corresponds to a null exponent with a non-null fraction.
                 * @return     A Mask containing TRUE for NaN elements in the
                 * current Vector4f.
                 */
                Mask isNaN() ;

                /**
                 * Load from an array that is not aligned.
                 * @param     array    The array to load into the Vector4f.
                 */
                void set(const Array4f& array) ;

                /**
                 * Copy the values on the Vector4f into an unaligned
                 * array.
                 * @param     array     Output parameter in which values of the
                 *                     Vector4f are stored.
                 * @param    count     Amount of values to set, having
                 *                     0 < count < 4.
                 */
                void get(Array4f& array) const ;

                /**
                 * Get the length of the Vector4f.
                 * @return  The length of the Vector4f.
                 */
                size_t length() const ;

                /**
                 * Size of a Vector4f.
                 * @return  The length of a Vector4f.
                 */
                static size_t size() ;

                /**
                 * Print the content of the Vector on the console output.
                 */
                void print() ;


            protected:
                                                                    /*** MXCSR ***/
                /**
                 * Read the MXCSR control word.
                 * @return    The current MXCSR control word.
                 */
                static uint32_t getControlWord() ;

                /**
                 * Write the MXCSR control word.
                 * @param     csr     The new MXCSR control word.
                 */
                static void setControlWord(uint32_t csr) ;

                /**
                 * Set "Denormals Are Zeros" and "Flush to Zero" mode
                 * to avoid the extremely time-consuming denormals in
                 * case of underflow.
                 */
                static void noSubnormals() ;

                /**
                 * Set the MXCSR control word to the default value
                 * 0x1F80. This will mask floating point exceptions,
                 * set rounding mode to nearest (or even), and allow
                 * denormals.
                 */
                static void resetControlWord() ;

            public:
                                                             /*** OPERATORS ***/
                                                        /** AFFECT OPERATORS **/
                /**
                 * Get the values from another Vector4f and put it in inner
                 * data.
                 * @param   vec4    The Vector4f to copy.
                 * @return  The current Vector4f once the vec4 is affected to
                 *          its inner data.
                 */
                Vector4f& operator=(const Vector4f& vec4) ;

                /**
                 * Affect the inner value of the Vector4f to the broadcasted one
                 * given as parameter.
                 * @param   value   The value to put in the Vector4f, to all its
                 *                     values.
                 * @return  The current Vector4f once the value is affected to
                 *          its inner data.
                 */
                Vector4f& operator=(const Scalar& value) ;

                /**
                 * Affect the inner value to the Vector4f.
                 * @param   vec     The value to put in the Vector4f.
                 * @return  The current Vector4f once the vec is affected to its
                 *          inner data.
                 */
                Vector4f& operator=(const float32x4_t& vec) ;

                /**
                 * Get the values from a Vector4i (integers) and put it in
                 * inner data.
                 * @param   vec4    The vector to convert.
                 * @return  The current Vector4f once the vec is affected to its
                 *          inner data.
                 */
                Vector4f& operator=(const Vector4i& vec4) ;

                /**
                 * Get the values from a Vector4ui (integers) and put it in
                 * inner data.
                 * @param   vec4    The vector to convert.
                 * @return  The current Vector4f once the vec is affected to its
                 *          inner data.
                 */
                Vector4f& operator=(const Vector4ui& vec4) ;

                                                            /** CAST OPERATORS **/
                /**
                 * Cast the current Vector4f to its inner data type.
                 * @return  The inner data.
                 */
                explicit operator float32x4_t() const ;

                /**
                 * Cast the current Vector4f to an array of float values.
                 * @return     The inner data as array of float values.
                 */
                explicit operator float*() const ;

                /**
                 * Cast the current Vector4f to a Vector4i.
                 * @return  The current Vector4f converted to Vector4i object.
                 */
                explicit operator Vector4i() const ;

                /**
                 * Cast the current Vector4f to a Vector4ui.
                 * @return  The current Vector4f converted to Vector4ui object.
                 * @warning Be careful with negative values.
                 */
                explicit operator Vector4ui() const ;
        } ;


        #include "impl/Vector4f/Mask/operators.hpp"
        #include "impl/Vector4f/Mask/impl.hpp"

        #include "impl/Vector4f/operators.hpp"

        template <int i0, int i1, int i2, int i3>
        void Vector4f::permute() {
            static_assert((i0 <= 3), "Bad value. Expected i0 <= 3") ;
            static_assert((i1 <= 3), "Bad value. Expected i1 <= 3") ;
            static_assert((i2 <= 3), "Bad value. Expected i2 <= 3") ;
            static_assert((i3 <= 3), "Bad value. Expected i3 <= 3") ;

            // Check if shuffling is required.
            const bool NeedShuffle = (i0 > 0)
                                        || ((i1 != 1) && (i1 >= 0))
                                        || ((i2 != 2) && (i2 >= 0))
                                        || ((i3 != 3) && (i3 >= 0)) ;

            // Check if zeroing required.
            const bool DoZero = (((i0 | i1 | i2 | i3) < 0) && ((i0 | i1 | i2 | i3) & 0x80)) ;

            if (DoZero and !NeedShuffle) {
                // Only make some / all positions zeroed in the vector.
                if ((i0 | i1 | i2 | i3) < 0) {
                    // Zero all values.
                    m_inner = _mm_setzero_ps() ;
                }
                else {
                    const int32x4_t MaskZeroPositions = Vector4i::constant<
                        -int(i0 > -1),
                        -int(i1 > -1),
                        -int(i2 > -1),
                        -int(i3 > -1)
                    >() ;

                    m_inner = _mm_and_ps(m_inner,_mm_castsi128_ps(MaskZeroPositions)) ;
                }
            }
            else if (NeedShuffle and !DoZero) {
                // Only shuffle the values in the vector.
                m_inner = _mm_shuffle_ps(
                    m_inner,
                    m_inner,
                    ((i0) | (i1 << 2) | (i2 << 4) | (i3 << 6))
                ) ;
            }
            else if (((i0 & i1) < 0) && ((i2 | i3) >= 0)) {
                // Zero on lower elements, shuffle higher ones.
                m_inner = _mm_shuffle_ps(_mm_setzero_ps(), m_inner, (i2 << 4) | (i3 <<6));
            }
            else if ((i0 | i1) >= 0 && (i2 & i3) < 0) {
                // Zero on higher elements, shuffle lower ones.
                m_inner = _mm_shuffle_ps(m_inner, _mm_setzero_ps(), (i0 | (i1 << 2))) ;
            }
            else {
                #if defined (USE_INTEL_SSSE3)
                    // With SSSE3 we can do both with the PSHUFB instruction
                    const int j0 = i0 << 2 ;
                    const int j1 = i1 << 2 ;
                    const int j2 = i2 << 2 ;
                    const int j3 = i3 << 2 ;
                    __m128i MaskZeroPositions = Vector4i::constant <
                        i0 < 0 ? -1 : j0 | (j0+1)<<8 | (j0+2)<<16 | (j0+3) << 24,
                        i1 < 0 ? -1 : j1 | (j1+1)<<8 | (j1+2)<<16 | (j1+3) << 24,
                        i2 < 0 ? -1 : j2 | (j2+1)<<8 | (j2+2)<<16 | (j2+3) << 24,
                        i3 < 0 ? -1 : j3 | (j3+1)<<8 | (j3+2)<<16 | (j3+3) << 24
                    > () ;
                    m_inner = _mm_castsi128_ps(_mm_shuffle_epi8(_mm_castps_si128(a),mask2)) ;
                #else
                    float32x4_t tmp = _mm_shuffle_ps(m_inner, m_inner, ((i0) | (i1 << 2) | (i2 << 4) | (i3 << 6))) ;
                    __m128i MaskZeroPositions = Vector4i::constant<
                        -int(i0 > -1),
                        -int(i1 > -1),
                        -int(i2 > -1),
                        -int(i3 > -1)
                    >() ;
                    m_inner = _mm_and_ps(tmp,_mm_castsi128_ps(MaskZeroPositions)) ;
                #endif
            }
        }

        template <bool i0, bool i1, bool i2, bool i3>
        void Vector4f::changeSign() {
            if ((i0 | i1 | i2 | i3) == true) {
                // Mask to set flip the bit for negative sign (on Scalar values).
                const __m128i MaskNegative = Vector4i::constant<
                    i0 ? 0x80000000 : 0,
                    i1 ? 0x80000000 : 0,
                    i2 ? 0x80000000 : 0,
                    i3 ? 0x80000000 : 0
                >() ;

                m_inner = _mm_xor_ps(m_inner, _mm_castsi128_ps(MaskNegative)) ;
            }
        }

        template <unsigned char i0, unsigned char i1, unsigned char i2, unsigned char i3>
        Vector4f& Vector4f::shuffle(
            const Vector4f& input,
            Vector4f& output
       ) {
            static_assert((i0 <= 3), "Bad value. Expected i0 <= 3") ;
            static_assert((i1 <= 3), "Bad value. Expected i1 <= 3") ;
            static_assert((i2 <= 3), "Bad value. Expected i2 <= 3") ;
            static_assert((i3 <= 3), "Bad value. Expected i3 <= 3") ;

            output = _mm_shuffle_ps(
                (float32x4_t) input,
                (float32x4_t) input,
                ((i0) | (i1 << 2) | (i2 << 4) | (i3 << 6))
            ) ;

            return output ;
        }

    } ;

} ;

#endif
