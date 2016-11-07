/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       NotImplementedException.cpp*/
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    26/02/2015                 */
/* UPDATE:      26/02/2015                 */
/*                                         */
/* A NotImplementedException is thrown     */
/* when a functionality is not yet         */
/* implemented.                            */
/*******************************************/


#ifdef __cplusplus

#include <exceptions/NotImplementedException.h>


namespace Doom {

    IMPLEMENT_EXCEPTION(NotImplementedException)

    void NotImplementedException::additionalInitializationTask() {}

} ;

#endif // __cplusplus
