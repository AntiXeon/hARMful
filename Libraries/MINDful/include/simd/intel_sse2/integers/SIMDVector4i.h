/*******************************************/
/* MINDful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* File : 		SIMDVector4i.h             */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	10/07/2015                 */
/* UPDATE:      10/07/2015                 */
/*                                         */
/* This file cannot be directly included.  */
/* Use #include <simd/SIMDVector.h> .      */
/*******************************************/

#ifndef __MIND_SIMD_VECTOR4_INT__
#define __MIND_SIMD_VECTOR4_INT__

#include <MINDOptions.h>
#include <simd/SIMDTypes.h>
#include <iostream>

#include "SIMDVector4.h"

namespace Mind {

	namespace SSE2 {

        class Vector4i : public Vector4int32 {
            public:
                                              /** CONSTRUCTION / DESTRUCTION **/
                /**
				 * @brief  	Create an empty vector.
				 * @warning The content of this vector is not guaranteed!
				 */
                Vector4i() ;

                /**
                 * @brief   Create a Vector4i defining all its values.
                 * @param   i1  First component of the Vector4i.
                 * @param   i2  Second component of the Vector4i.
                 * @param   i3  Third component of the Vector4i.
                 * @param   i4  Fourth component of the Vector4i.
                 */
                Vector4i(
                         const int32_t& i1,
                         const int32_t& i2,
                         const int32_t& i3 = 0.f,
                         const int32_t& i4 = 0.f
                        ) ;

                /**
                 * @brief   Create a Vector4i in which all values are the given
                 *          one.
                 * @param   value   The value to copy in the four components of
                 *                  the Vector4i.
                 */
                Vector4i(const int32_t& value) ;

                /**
                 * @brief   Create directly from internally used data type.
                 * @param   vec     Data using the inner data type.
                 */
                Vector4i(const int32x4_t& vec) ;

                /**
                 * @brief   Create from data of a Vector4f.
                 * @param   vec     Data using the inner data type of Vector4f.
                 */
                Vector4i(const float32x4_t& vec) ;

				/**
				 * @brief 	Destruction of the Vector4i.
				 */
				virtual ~Vector4i() ;


                                                        /** STATIC FUNCTIONS **/
                /**
                 * @brief   Generate a constant vector of 4 integers stored in
                 *          memory. Can be converted to any integer vector type.
                 */
                template <int32_t i0, int32_t i1, int32_t i2, int32_t i3>
                static int32x4_t constant() ;

				/**
				 * @brief 	Get a minimal Vector4i. It is the consensus of a and
				 *			b, picking only the smallest value for a given
				 *			element:
				 *			<code>
				 *			dst[i] = min(a[i], b[i]) ;
				 *			</code>
				 * @param 	a 	First Vector4i to test.
				 * @param 	b 	Second Vector4i to test.
				 * @return 	A Vector4i containing the minimal values contained
				 *			in a or b.
				 */
                static Vector4i min(const Vector4i& a, const Vector4i& b) ;

				/**
				 * @brief 	Get a maximal Vector4i. It is the consensus of a and
				 *			b, picking only the greatest value for a given
				 *			element:
				 *			<code>
				 *			dst[i] = max(a[i], b[i]) ;
				 *			</code>
				 * @param 	a 	First Vector4i to test.
				 * @param 	b 	Second Vector4i to test.
				 * @return 	A Vector4i containing the maximal values contained
				 *			in a or b.
				 */
				static Vector4i max(const Vector4i& a, const Vector4i& b) ;

				/**
				 * @brief	Get a copy of the given Vector4i in which all
				 *			elements are absolute values.
				 * @param 	vec 	Vector4i to get its absolute values.
				 * @return 	Vector4i in which the values are absolute values
				 *			from @a vec.
				 */
				static Vector4i abs(const Vector4i& vec) ;

				/**
				 * @brief Print the content of the Vector on the console output.
				 */
				void print() ;
        } ;

    	// #include "impl/Vector4/Vector4i/impl.h"
        #include "impl/Vector4/Vector4i/operators.h"


        template <int32_t i0, int32_t i1, int32_t i2, int32_t i3>
        int32x4_t Vector4i::constant() {
            static const union {
                int integer[4] ;
                int32x4_t vector ;
            } u = {{i0, i1, i2, i3}} ;
            return u.vector ;
        }

    } ;

} ;


#endif
