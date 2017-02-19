#ifndef __MIND__SIMD_VECTOR4_UNSIGNED_INT__
#define __MIND__SIMD_VECTOR4_UNSIGNED_INT__

#include <MINDOptions.hpp>
#include <simd/SIMDTypes.hpp>
#include <Math.hpp>
#include <iostream>

#include "SIMDVector4i.hpp"

namespace Mind {
    namespace EmulatedSIMD {
        class Vector4ui {
            public:
                #include "impl/Vector4/Vector4ui/Mask/inner.hpp"

            private:
                /** Inner vector data. */
                uint32x4_t m_inner ;

                /**
                 * Get the combination of two inner objects. It follows this
                 * case:
                 * <code>dst[i] = selector[i] ? a[i] : b[i] ;</code>
                 * @param 	selector 	Mask to select elements from a if TRUE,
                 *						from b if FALSE.
                 * @param 	a 			First vector to pick values in.
                 * @param 	b 			Second vector to pick values in.
                 * @return	An inner data object combining @a a and @a b
                 *			following the content of @a selector.
                 */
                static uint32x4_t selection(
                    const uint32x4_t& selector,
                    const uint32x4_t& a,
                    const uint32x4_t& b
                ) ;

            public:
                                              /** CONSTRUCTION / DESTRUCTION **/
                /**
                 * Create an empty vector.
                 * @warning The content of this vector is not guaranteed!
                 */
                Vector4ui() ;

                /**
                 * Create a Vector4ui defining all its values.
                 * @param   i1  First component of the Vector4ui.
                 * @param   i2  Second component of the Vector4ui.
                 * @param   i3  Third component of the Vector4ui.
                 * @param   i4  Fourth component of the Vector4ui.
                 */
                Vector4ui(
                         const uint32_t& i1,
                         const uint32_t& i2,
                         const uint32_t& i3 = 0.f,
                         const uint32_t& i4 = 0.f
                        ) ;

                /**
                 * Create a Vector4ui in which all values are the given one.
                 * @param   value   The value to copy in the four components of
                 *                  the Vector4ui.
                 */
                Vector4ui(const uint32_t& value) ;

                /**
                 * Create directly from internally used data type.
                 * @param   vec     Data using the inner data type.
                 */
                Vector4ui(const uint32x4_t& vec) ;

                /**
                 * Create from data of a Vector4f.
                 * @param   vec     Data using the inner data type of Vector4f.
                 */
                Vector4ui(const float32x4_t& vec) ;

                /**
                 * Destruction of the Vector4ui.
                 */
                virtual ~Vector4ui() ;

                                                              /*** UTILITIES ***/
                /**
                 * Compute the sum of elements in the Vector4f.
                 * @return 	The sum of all elements in Vector4.
                 */
                int64_t horizontalAdd() ;

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

                                                        /** STATIC FUNCTIONS **/
                /**
                 * Generate a constant vector of 4 integers stored in memory.
                 * Can be converted to any integer vector type.
                 */
                template <uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3>
                static uint32x4_t constant() ;

                /**
                 * Get a minimal Vector4ui. It is the consensus of a and b,
                 * picking only the smallest value for a given element:
                 * <code>
                 * dst[i] = min(a[i], b[i]) ;
                 * </code>
                 * @param 	a 	First Vector4ui to test.
                 * @param 	b 	Second Vector4ui to test.
                 * @return 	A Vector4ui containing the minimal values contained
                 *			in a or b.
                 */
                static Vector4ui min(const Vector4ui& a, const Vector4ui& b) ;

                /**
                 * Get a maximal Vector4ui. It is the consensus of a and b,
                 * picking only the greatest value for a given element:
                 * <code>
                 * dst[i] = max(a[i], b[i]) ;
                 * </code>
                 * @param 	a 	First Vector4ui to test.
                 * @param 	b 	Second Vector4ui to test.
                 * @return 	A Vector4ui containing the maximal values contained
                 *			in a or b.
                 */
                static Vector4ui max(const Vector4ui& a, const Vector4ui& b) ;

                /**
                 * @brief Print the content of the Vector on the console output.
                 */
                void print() ;


                /**
                 * Cast the current Vector4 to its inner data type.
                 * @return  The inner data.
                 */
                operator uint32x4_t() const ;

                /**
                 * Cast the current Vector4 to its inner data type.
                 * @return  The inner data.
                 */
                operator uint32x4_t*() const ;
        } ;

        #include "impl/Vector4/Vector4ui/Mask/operators.hpp"

        #include "impl/Vector4/Vector4ui/operators.hpp"


        template <uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3>
        uint32x4_t Vector4ui::constant() {
            uint32x4_t vector ;
            vector[0] = i0 ;
            vector[1] = i1 ;
            vector[2] = i2 ;
            vector[3] = i3 ;
            return vector ;
        }
    } ;
} ;

#endif
