#include <DOOMStrings.h>


namespace Doom {

    namespace TimeMsg {
        namespace Error {
            const char* DateTimeBufferTooSmall =                                "Date-time buffer is to small. Use DateTimeBufferSize as minimal size." ;
            const char* DateBufferTooSmall =                                    "Date buffer is to small. Use DateBufferSize as minimal size." ;
            const char* TimeBufferTooSmall =                                    "Time buffer is to small. Use TimeBufferSize as minimal size." ;
        }
    } ;

    namespace LogMsg {
        namespace Error {
            const char* CannotLogToFile =                                       "Cannot write log to file" ;
        } ;
    } ;

    namespace CallStackMsg {
        namespace Text {
            const char* Title =                                                 "============ Stack trace ============" ;
            const char* Corrupt =                                               "No stack trace, possibly corrupt" ;
        } ;
    } ;

    namespace ProcessorMsg {
        namespace Error {
            const char* UnableToOpenCPUInfo =                                   "Unable to open %s to get CPU informations" ;
        } ;

        namespace Warning {
            const char* UnableToGetCorrectInfo =                                "Unable to get correct informations on CPUs. Default value (%d) used." ;
            const char* UnableToGetInfo =                                       "Unable to open %s to get CPU informations" ;
            const char* BadThreadsByCPU =                                       "Bad ThreadsByCPU count. Cannot be null, default value (%d) used." ;
            const char* BadCoresByCPU =                                         "Bad CoresByCPU count. Cannot be null, default value (%d) used." ;
            const char* NameNotFound =                                          "CPU name not found, default value (%s) used" ;
        } ;

        namespace Text {
            const char* Name =                                                  "Name:          " ;
            const char* Frequency =                                             "Frequency:     " ;
            const char* Cores =                                                 "Cores:         " ;
            const char* Threads =                                               "Threads:       " ;
            const char* Hyperthreading =                                        "Hyperthreaded: " ;
            const char* Endianness =                                            "Endianness:    " ;

            const char* LittleEndian =                                          "Little endian" ;
            const char* BigEndian =                                             "Big endian" ;
            const char* UnknownEndian =                                         "Unhandled endianness" ;
        } ;
    } ;

    namespace ThreadManagerMsg {
        namespace Error {
            const char* AlreadyInUse =                                          "Thread \"%s\" already exists." ;
            const char* NotRegistered =                                         "Thread \"%s\" is not registered." ;
            const char* ThreadStopMismatch =                                    "It seems that all threads were not correctly stopped." ;
        } ;
    } ;

    namespace ListMsg {
        namespace Error {
            const char* SizeCannotBeNegative =                                  "List size cannot be negative" ;
            const char* Mismatch =                                              "List mismatch" ;
            const char* NullNode =                                              "Node is NULL" ;
            const char* NodeNotUsed =                                           "Node not in use, no access" ;
            const char* NoPreviousNodeToHead =                                  "List head must not have previous node" ;
            const char* NoNextNodeToTail =                                      "List tail must not have next node" ;
            const char* HeadNullIfNoTail =                                      "List head must be NULL if no tail found" ;
            const char* HeadIsTailIfSizeIsOne =                                 "Head and Tail must be the same while size is 1" ;
            const char* HeadNotNullButSizeIsZero =                              "Head not NULL while size is 0" ;
            const char* TailNotNullButSizeIsZero =                              "Tail not NULL while size is 0" ;
            const char* HeadNullButSizeGreaterThanZero =                        "Head NULL while size is greater than 0" ;
            const char* HeadNullButSizeGreaterThanOne =                         "Head NULL while size is greater than 1" ;
            const char* TailNullButSizeGreaterThanZero =                        "Tail NULL while size is greater than 0" ;
            const char* TailNullButSizeGreaterThanOne =                         "Tail NULL while size is greater than 1" ;
        } ;
    } ;

    namespace SizedStackMsg {
        namespace Error {
            const char* Empty =                                                 "Empty stack" ;
            const char* InvalidIndex =                                          "Invalid stack index" ;
            const char* InvalidSize =                                           "Invalid size" ;
        } ;

        namespace Warning {
            const char* AlreadyFull =                                           "The SizedStack is already full." ;
        } ;
    } ;

    namespace ObjectPoolMsg {
        namespace Error {
            const char* NoNullFactoryAllowed =                                  "The Factory cannot be NULL." ;
            const char* DifferentOriginOfInstance =                             "The dropped instance does not come from this ObjectPool." ;
            const char* InstanceAlreadyInCache =                                "The dropped instance is already stored in cache." ;
            const char* NoUndefinedValueInCacheAllowed =                        "An undefined value cannot be stored in cache." ;
        }
    }

} ;
