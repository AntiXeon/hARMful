/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       DOOMStrings.h              */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    03/22/2014                 */
/* UPDATE:      03/22/2014                 */
/*                                         */
/* Group of all the strings used in one    */
/* place for C++ API of DOOM.              */
/*******************************************/

#ifndef __DOOM__TEXT_STRINGS_INCLUDE__
#define __DOOM__TEXT_STRINGS_INCLUDE__


#include <string>


namespace Doom {

    namespace TimeMsg {
        namespace Error {
            extern const char* DateTimeBufferTooSmall ;
            extern const char* DateBufferTooSmall ;
            extern const char* TimeBufferTooSmall ;
        }
    } ;

    namespace LogMsg {
        namespace Error {
            extern const char* CannotLogToFile ;
        } ;
    } ;

    namespace CallStackMsg {
        namespace Text {
            extern const char* Title ;
            extern const char* Corrupt ;
        } ;
    } ;

    namespace ProcessorMsg {
        namespace Error {
            extern const char* UnableToOpenCPUInfo ;
        } ;

        namespace Warning {
            extern const char* UnableToGetCorrectInfo ;
            extern const char* UnableToGetInfo ;
            extern const char* BadThreadsByCPU ;
            extern const char* BadCoresByCPU ;
            extern const char* NameNotFound ;
        } ;

        namespace Text {
            extern const char* Name ;
            extern const char* Frequency ;
            extern const char* Cores ;
            extern const char* Threads ;
            extern const char* Hyperthreading ;
            extern const char* Endianness ;

            extern const char* LittleEndian ;
            extern const char* BigEndian ;
            extern const char* UnknownEndian ;
        } ;
    } ;

    namespace ThreadManagerMsg {
        namespace Error {
            extern const char* AlreadyInUse ;
            extern const char* NotRegistered ;
            extern const char* ThreadStopMismatch ;
        } ;
    } ;

    namespace ListMsg {
        namespace Error {
            extern const char* SizeCannotBeNegative ;
            extern const char* Mismatch ;
            extern const char* NullNode ;
            extern const char* NodeNotUsed ;
            extern const char* NoPreviousNodeToHead ;
            extern const char* NoNextNodeToTail ;
            extern const char* HeadNullIfNoTail ;
            extern const char* HeadIsTailIfSizeIsOne ;
            extern const char* HeadNotNullButSizeIsZero ;
            extern const char* TailNotNullButSizeIsZero ;
            extern const char* HeadNullButSizeGreaterThanZero ;
            extern const char* HeadNullButSizeGreaterThanOne ;
            extern const char* TailNullButSizeGreaterThanZero ;
            extern const char* TailNullButSizeGreaterThanOne ;
        } ;
    } ;

    namespace SizedStackMsg {
        namespace Error {
            extern const char* Empty ;
            extern const char* InvalidIndex ;
            extern const char* InvalidSize ;
        } ;

        namespace Warning {
            extern const char* AlreadyFull ;
        } ;
    } ;

    namespace ObjectPoolMsg {
        namespace Error {
            extern const char* NoNullFactoryAllowed ;
            extern const char* DifferentOriginOfInstance ;
            extern const char* InstanceAlreadyInCache ;
            extern const char* NoUndefinedValueInCacheAllowed ;
        }
    }

} ;


#endif
