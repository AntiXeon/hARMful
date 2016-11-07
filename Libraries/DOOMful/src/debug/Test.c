/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Test.c                       */
/* AUTHOR : 	Denis CARLUS                 */
/* VERSION: 	1.0                          */
/* CREATION:	03/22/2014                   */
/* UPDATE:    03/22/2014                   */
/*                                         */
/* Macro and functions to perform tests,   */
/* assertions and various bug tracking     */
/* tools.                                  */
/*******************************************/

#include <debug/Test.h>
#include <debug/Log.h>

void PrintErrno(
                const char* DOOM_File_With_Error,
                int DOOM_Line_With_Error,
                const char* DOOM_Function_With_Error
               ) {
    if (errno != 0) {
        printf("%s[%s:%d %s()]%s %s%s\n",
               TERMTEXT_BOLD,
               DOOM_File_With_Error,
               DOOM_Line_With_Error,
               DOOM_Function_With_Error,
               TERMTEXT_YELLOW,
               strerror(errno),
               TERMTEXT_DEFAULT) ;
    }
}

void StopOnErrno(
                 const char* DOOM_File_With_Error,
                 int DOOM_Line_With_Error,
                 const char* DOOM_Function_With_Error
                ) {
    if (errno != 0) {
        printf("%s[%s:%d %s()]%s %s%s\n",
               TERMTEXT_BOLD,
               DOOM_File_With_Error,
               DOOM_Line_With_Error,
               DOOM_Function_With_Error,
               TERMTEXT_RED,
               strerror(errno),
               TERMTEXT_DEFAULT) ;

        // @TODO : close all threads and crash!
        exit(-1) ;
    }
}

void StopOnErrnoWithMsg(
                        const char* DOOM_File_With_Error,
                        int DOOM_Line_With_Error,
                        const char* DOOM_Function_With_Error,
                        const char* User_Message
                       ) {
    if (errno != 0) {
        printf("%s[%s:%d %s()]%s %s\n%s%s\n",
               TERMTEXT_BOLD,
               DOOM_File_With_Error,
               DOOM_Line_With_Error,
               DOOM_Function_With_Error,
               TERMTEXT_RED,
               strerror(errno),
               User_Message,
               TERMTEXT_DEFAULT) ;

        // @TODO : close all threads and crash!
        exit(-1) ;
    }
}
