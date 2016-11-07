/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Print.h                    */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/22/2014                 */
/* UPDATE:      03/22/2014                 */
/*                                         */
/* Macro and functions to print texts on   */
/* terminal.                               */
/*******************************************/

#ifndef __DOOM__PRINT__
#define __DOOM__PRINT__

#include <errno.h>
#include <stdio.h>
#include <string.h>

	#if defined(__cplusplus)
		extern "C" {
	#endif


#define GET_VAR_NAME(x) #x

/**************************************/
/********** VARIABLE PRINT ************/
/**************************************/
#define PRINT_STR(x)    printf("%s = %s\n", GET_VAR_NAME(x), x)
#define PRINT_PTR(x)    printf("%s = %p\n", GET_VAR_NAME(x), x)
#define PRINT_CHAR(x)   printf("%s = %d\n", GET_VAR_NAME(x), x)
#define PRINT_INT(x)    printf("%s = %d\n", GET_VAR_NAME(x), x)
#define PRINT_UINT(x)   printf("%s = %u\n", GET_VAR_NAME(x), x)
#define PRINT_HEXA(x)   printf("%s = %x\n", GET_VAR_NAME(x), x)
#define PRINT_OCTAL(x)  printf("%s = %o\n", GET_VAR_NAME(x), x)
#define PRINT_FLOAT(x)  printf("%s = %g\n", GET_VAR_NAME(x), x)
#define PRINT_DOUBLE(x) PRINT_FLOAT(x)


/**************************************/
/*********** STYLE PRINT **************/
/**************************************/
#define TERMTEXT_DEFAULT	"\x1B[0m"
#define TERMTEXT_BOLD		"\x1B[1m"
#define TERMTEXT_RED		"\x1B[31m"
#define TERMTEXT_GREEN  	"\x1B[32m"
#define TERMTEXT_YELLOW 	"\x1B[33m"
#define TERMTEXT_BLUE		"\x1B[34m"
#define TERMTEXT_MAGENTA	"\x1B[35m"
#define TERMTEXT_CYAN		"\x1B[36m"
#define TERMTEXT_WHITE		"\x1B[37m"


/**
 * @brief	Print a text with the wanted style (color, bold,...).
 * @param   style   Style of the text.
 * @param   text    Text to be displayed with the given style.
 */
#define PRINT_TEXT(style, text) printf(style text TERMTEXT_DEFAULT "\n")


	#if defined(__cplusplus)
		}  /* extern "C" */
	#endif

#endif
