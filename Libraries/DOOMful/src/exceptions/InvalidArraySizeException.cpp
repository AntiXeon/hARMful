/**********************************************/
/* DOOMful - Part of the hARMful Engine       */
/* All rights reserved (c) Denis CARLUS       */
/*                                            */
/* FILE :       InvalidArraySizeException.cpp */
/* AUTHOR :     Denis CARLUS                  */
/* VERSION:     1.0                           */
/* CREATION:    26/02/2015                    */
/* UPDATE:      26/02/2015                    */
/*                                            */
/* An InvalidArraySizeException is thrown     */
/* when the size of an array is not equal     */
/* to the expected size.                      */
/**********************************************/


#ifdef __cplusplus

#include <exceptions/InvalidArraySizeException.h>


namespace Doom {

    IMPLEMENT_EXCEPTION(InvalidArraySizeException)

    void InvalidArraySizeException::additionalInitializationTask() {}

} ;

#endif // __cplusplus
