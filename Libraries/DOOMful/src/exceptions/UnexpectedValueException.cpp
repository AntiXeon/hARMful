/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       UnexpectedValueExcep...cpp */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    19/04/2015                 */
/* UPDATE:      19/04/2015                 */
/*                                         */
/* An UnexpectedValueException is thrown   */
/* when a value that should not be given   */
/* is found.                               */
/*******************************************/


#ifdef __cplusplus

#include <exceptions/UnexpectedValueException.h>


namespace Doom {

    IMPLEMENT_EXCEPTION(UnexpectedValueException)

    void UnexpectedValueException::additionalInitializationTask() {}

} ;

#endif // __cplusplus
