#ifndef __MIND_SIMD_VECTOR4__
#define __MIND_SIMD_VECTOR4__

#include <MINDOptions.h>
#include <simd/SIMDTypes.h>
#include <MINDTypes.h>
#include <typeinfo>


namespace Mind {

	namespace SSE2 {

		/**
		 * @brief   A vector of four integer values.
		 *			Used to optimize operations on such
		 *			data structure by using SSE2 instructions on Intel/AMD CPUs.
		 *
		 *			This class is highly inspired by the work of Agner Fog.
		 *			http://www.agner.org/optimize/
		 *
		 * @author  CB (c) 2015
		 * @version 0.1     2015/09/23
		 */
		template <typename Type>
		class Vector4 {
		    public:
				#include "impl/Vector4/Mask/inner.h"

            protected:
                /** @brief  Inner vector data. */
                int32x4_t m_inner ;

                /**
				 * @brief 	Get the combination of two inner objects. It
				 *			follows this case:
				 *			<code>dst[i] = selector[i] ? a[i] : b[i] ;</code>
				 * @param 	selector 	Mask to select elements from a if TRUE,
				 *						from b if FALSE.
				 * @param 	a 			First vector to pick values in.
				 * @param 	b 			Second vector to pick values in.
				 * @return	An inner data object combining @a a and @a b
				 *			following the content of @a selector.
				 */
				static int32x4_t selection(
										   const int32x4_t& selector,
										   const int32x4_t& a,
										   const int32x4_t& b
										  ) ;


            public:
                                              /** CONSTRUCTION / DESTRUCTION **/
                /**
				 * @brief  	Create an empty vector.
				 */
                Vector4() ;

                /**
                 * @brief   Create a Vector4 defining all its values.
                 * @param   f1  First component of the Vector4.
                 * @param   f2  Second component of the Vector4.
                 * @param   f3  Third component of the Vector4.
                 * @param   f4  Fourth component of the Vector4.
                 */
                Vector4(
                         const Type& f1,
                         const Type& f2,
                         const Type& f3 = 0.f,
                         const Type& f4 = 0.f
                        ) ;

                /**
                 * @brief   Create a Vector4 in which all values are the given
                 *          one.
                 * @param   value   The value to copy in the four components of
                 *                  the Vector4.
                 */
                Vector4(const Type& value) ;

                /**
                 * @brief   Create directly from internally used data type.
                 * @param   vec     Data using the inner data type.
                 */
                Vector4(const int32x4_t& vec) ;

                /**
                 * @brief   Create from data of a Vector4f.
                 * @param   vec     Data using the inner data type of Vector4f.
                 */
                Vector4(const float32x4_t& vec) ;

				/**
				 * @brief 	Destruction of the Vector4.
				 */
				virtual ~Vector4() ;


                                             				 /*** UTILITIES ***/
				/**
				 * @brief 	Truncate the Vector4. Elements that are "dropped"
				 *			are just replace by zeros into the inner data.
				 * @param 	amount 	Amount of values to keep once the Vector has
				 *					been truncated.
				 */
				// void truncate(const int32_t& amount) ;

				/**
				 * @brief 	Compute the sum of elements in the Vector4f.
				 * @return 	The sum of all elements in Vector4.
				 */
				Type horizontalAdd() ;

		        /**
		         * @brief   Get the length of the Vector4f.
		         * @return  The length of the Vector4f.
		         */
		        size_t length() const ;

		        /**
		         * @brief   Size of a Vector4f.
		         * @return  The length of a Vector4f.
		         */
		        static size_t size() ;

                                            				 /*** OPERATORS ***/
                                          				  /** CAST OPERATORS **/
		        /**
		         * @brief   Cast the current Vector4 to its inner data type.
		         * @return  The inner data.
		         */
		        operator int32x4_t() const ;
		} ;


        #include "impl/Vector4/Mask/operators.h"
        #include "impl/Vector4/Mask/impl.h"

        // #include "impl/Vector4/impl.h"


        typedef Vector4<int32_t> Vector4int32 ;
        typedef Vector4<uint32_t> Vector4uint32 ;
    } ;
} ;

#endif
