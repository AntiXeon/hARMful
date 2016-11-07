/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       IOException.cpp            */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    26/02/2015                 */
/* UPDATE:      26/02/2015                 */
/*                                         */
/* An IOException is generally thrown by   */
/* input/output operations, on files,      */
/* streams or buffers. For example :       */
/* opening, closing, reading or writing    */
/* data.                                   */
/*******************************************/


#ifdef __cplusplus

#include <exceptions/IOException.h>


namespace Doom {

    IMPLEMENT_EXCEPTION(IOException)

    void IOException::additionalInitializationTask() {}

} ;

#endif // __cplusplus
