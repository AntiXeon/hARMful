/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		AlignedArray.h             */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/10/2016                 */
/* UPDATE:      01/10/2016                 */
/*                                         */
/* Aligned array as an object with a fixed */
/* size and type.                          */
/*******************************************/

#ifndef __DOOM_ALIGNED_ARRAY__
#define __DOOM_ALIGNED_ARRAY__


#include <stdint.h>
#include <stddef.h>
#include <string.h>


namespace Doom {

   /**
    * @brief   Aligned array as an object with a fixed size and type.
    * @author  CB (c) 2016
    * @version 0.1     2016/01/10
    */
    template <typename Type, unsigned int Size, unsigned int Align>
    class AlignedArray {
        private:
            /** @brief  Inner array. */
            Type m_array[Size] __attribute__ ((aligned (Align))) ;

        public:
                                                  /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create an empty array. Values are uninitialized.
             */
            AlignedArray() ;

            /**
             * @brief   Initialize the array with the given values.
             * @param   values  List of values to put in the array at its creation.
             * @warning There must be at least the same amount of values as the size
             *          of the AlignedArray.
             */
            AlignedArray(Type* values) ;

            /**
             * @brief   Destruction of the AlignedArray.
             */
            virtual ~AlignedArray() ;

                                                                   /** UTILITIES **/
            /**
             * @brief   Fill the entire array with the given value.
             * @param   value   The value to put into the Array.
             */
            void fill(const Type& value) ;

            /**
             * @brief   Swap the content of the current Array with another one.
             * @param   other   The other Array to swap content.
             */
            void swap(AlignedArray<Type, Size, Align>& other) ;


                                                           /** GETTERS / SETTERS **/
            /**
             * @brief   Check if the Array is empty.
             * @return  TRUE if the Array has a null size.
             */
            bool empty() const ;

            /**
             * @brief   Get the inner data.
             * @return  The inner array.
             */
            Type* data() ;

            /**
             * @brief   Get the inner data.
             * @return  The inner array.
             */
            const Type* data() const ;

            /**
             * @brief   Access operator.
             * @param   index   Index of the element to access.
             * @return  The element at wanted index.
             */
            Type& operator[] (uint32_t index) ;

            /**
             * @brief   Access operator.
             * @param   index   Index of the element to access.
             * @return  The element at wanted index.
             */
            const Type& operator[] (uint32_t index) const ;

            /**
             * @brief   Access method.
             * @param   index   Index of the element to access.
             * @return  The element at wanted index.
             */
            Type& at(uint32_t index) ;

            /**
             * @brief   Get the size of Arrays from generic point of view.
             * @return  Size of the Arrays.
             */
            unsigned int length() const ;

            /**
             * @brief   Get the size of the Array.
             * @return  Size of the Array.
             */
            static unsigned int size() ;


                                                     /*** AFFECTATION OPERATORS ***/
            /**
             * @brief   Affect the content of another Array to the current one.
             * @param   other   The other Array to copy data into the current one.
             * @return  The current Array containing the same data as the @a other
             *          one.
             * @warning Pointers are just copied, pointed objects are not cloned.
             */
            AlignedArray<Type, Size, Align>& operator=(const AlignedArray<Type, Size, Align>& other) ;

            /**
             * @brief   Affect the content of another Array to the current one.
             * @param   other   The other array to copy data into the current one.
             * @return  The current Array containing the same data as the @a other
             *          one.
             * @warning Pointers are just copied, pointed objects are not cloned.
             */
            AlignedArray<Type, Size, Align>& operator=(const Type* other) ;
    } ;

    #include "Array/AlignedArray.impl"

} ;


#endif
