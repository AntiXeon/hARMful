/*******************************************/
/* MINDful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* File : 		SIMDVector4ui.h            */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	10/07/2015                 */
/* UPDATE:      10/07/2015                 */
/*                                         */
/* This file cannot be directly included.  */
/* Use #include <simd/SIMDVector.h> .      */
/*******************************************/

#ifndef __MIND_SIMD_VECTOR4_UNSIGNED_INT__
#define __MIND_SIMD_VECTOR4_UNSIGNED_INT__

#include <MINDOptions.h>
#include <simd/SIMDTypes.h>
#include <iostream>

#include "SIMDVector4.h"


namespace Mind {

	namespace SSE2 {

        class Vector4ui : public Vector4uint32 {
            public:
                                              /** CONSTRUCTION / DESTRUCTION **/
                /**
				 * @brief  	Create an empty vector.
				 * @warning The content of this vector is not guaranteed!
				 */
                Vector4ui() ;

                /**
                 * @brief   Create a Vector4ui defining all its values.
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
                 * @brief   Create a Vector4ui in which all values are the given
                 *          one.
                 * @param   value   The value to copy in the four components of
                 *                  the Vector4ui.
                 */
                Vector4ui(const uint32_t& value) ;

                /**
                 * @brief   Create directly from internally used data type.
                 * @param   vec     Data using the inner data type.
                 */
                Vector4ui(const uint32x4_t& vec) ;

                /**
                 * @brief   Create from data of a Vector4f.
                 * @param   vec     Data using the inner data type of Vector4f.
                 */
                Vector4ui(const float32x4_t& vec) ;

				/**
				 * @brief 	Destruction of the Vector4ui.
				 */
				virtual ~Vector4ui() ;


                                                        /** STATIC FUNCTIONS **/
                /**
                 * @brief   Generate a constant vector of 4 integers stored in
                 *          memory. Can be converted to any integer vector type.
                 */
                template <uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3>
                static uint32x4_t constant() ;

				/**
				 * @brief 	Get a minimal Vector4ui. It is the consensus of a
				 *			and b, picking only the smallest value for a given
				 *			element:
				 *			<code>
				 *			dst[i] = min(a[i], b[i]) ;
				 *			</code>
				 * @param 	a 	First Vector4ui to test.
				 * @param 	b 	Second Vector4ui to test.
				 * @return 	A Vector4ui containing the minimal values contained
				 *			in a or b.
				 */
                static Vector4ui min(const Vector4ui& a, const Vector4ui& b) ;

				/**
				 * @brief 	Get a maximal Vector4ui. It is the consensus of a
				 *			and b, picking only the greatest value for a given
				 *			element:
				 *			<code>
				 *			dst[i] = max(a[i], b[i]) ;
				 *			</code>
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
        } ;

        // #include "impl/Vector4/Vector4ui/impl.h"
        #include "impl/Vector4/Vector4ui/operators.h"


        template <uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3>
        inline uint32x4_t Vector4ui::constant() {
            static const union {
                int integer[4] ;
                uint32x4_t vector ;
            } u = {{i0, i1, i2, i3}} ;
            return u.vector ;
        }

    } ;

} ;


#endif
