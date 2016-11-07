/*********************************************/
/* DOOMful - Part of the hARMful Engine      */
/* All rights reserved (c) Denis CARLUS      */
/*                                           */
/* FILE :       ArrayOutOfBoundException.cpp */
/* AUTHOR :     Denis CARLUS                 */
/* VERSION:     1.0                          */
/* CREATION:    26/02/2015                   */
/* UPDATE:      26/02/2015                   */
/*                                           */
/* An ArrayOutOfBoundException is thrown     */
/* when a user tries to access data from     */
/* an array that is not inside it.           */
/* For example, an access to the 42th        */
/* element of an array containing only 30    */
/* values.                                   */
/*********************************************/


#ifdef __cplusplus

#include <exceptions/ArrayOutOfBoundException.h>


namespace Doom {

    IMPLEMENT_EXCEPTION(ArrayOutOfBoundException)

    void ArrayOutOfBoundException::additionalInitializationTask() {}

} ;

#endif // __cplusplus
