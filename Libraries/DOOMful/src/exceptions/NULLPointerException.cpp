/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       NULLPointerException.cpp   */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    22/03/2015                 */
/* UPDATE:      22/03/2015                 */
/*                                         */
/* NULLPointerException when a pointer is  */
/* NULL while it should not be.            */
/*******************************************/


#ifdef __cplusplus

#include <exceptions/NULLPointerException.h>


namespace Doom {

    IMPLEMENT_EXCEPTION(NULLPointerException)

    void NULLPointerException::additionalInitializationTask() {}

} ;

#endif // __cplusplus
