/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       FactoryUnableToCreateIn... */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    22/03/2015                 */
/* UPDATE:      22/03/2015                 */
/*                                         */
/* FactoryUnableToCreateInstanceException  */
/* is thrown when a factory is unable to   */
/* create a new object.                    */
/*******************************************/


#ifdef __cplusplus

#include <exceptions/FactoryUnableToCreateInstanceException.h>


namespace Doom {

    IMPLEMENT_EXCEPTION(FactoryUnableToCreateInstanceException)

    void FactoryUnableToCreateInstanceException::additionalInitializationTask() {}

} ;

#endif // __cplusplus
