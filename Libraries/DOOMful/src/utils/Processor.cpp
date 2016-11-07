/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Processor.cpp              */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	04/10/2014                 */
/* UPDATE:      04/10/2014                 */
/*                                         */
/* API to get processor informations.      */
/*******************************************/

#include <Types.h>
#include <Platform.h>
#include <debug/Log.h>
#include <debug/Test.h>
#include <debug/Print.h>
#include <DOOMStrings.h>
#include <utils/String.h>
#include <utils/Processor.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CPUINFO_FILE    "/proc/cpuinfo"

#define LABEL_LENGTH    32
#define VALUE_LENGTH    16


#define CPU_PROCESSOR_LABEL     "processor"
#define CPU_THREADS_LABEL       "siblings"
#define CPU_CORES_LABEL         "cpu cores"
#define CPU_FREQUENCY_LABEL     "cpu MHz"
#define CPU_MODEL_NAME_LABEL    "model name"
#define CPU_FLAGS_LABEL         "flags"
#define CPU_FLAG_HT_LABEL       " ht "


namespace Doom {

    namespace Processor {
        /** @brief  To know if the CPU informations has been initialized. */
        static bool Initialized = false ;


        /** @brief  Name of the CPU. */
        static char CPUName[LABEL_LENGTH] ;

        /** @brief  Amount of cores available on a single CPU. */
        static unsigned short CoresByCPU = 0 ;

        /** @brief  Amount of threads available on a single CPU (may be different from
         *          CoresByCPU in case CPU is hyperthreaded).
         */
        static unsigned short ThreadsByCPU = 0 ;

        /** @brief  Total amount of threads on CPUs (useful for multi-CPUs platforms). */
        static unsigned short TotalThreadOnCPUs = 0 ;

        /** @brief  CPU frequency (MHz). */
        static unsigned short Frequency = 0 ;

        /** @brief  To know if the CPU is hyperthreaded (twice detected units). */
        static bool IsHyperThreaded = false ;

        /** @brief  To know the endianness of the CPU. */
        static Endianness CPUEndianness ;


        /**
         * @brief   Get the total amount of threads on CPUs (useful for multi-CPUs
         *          platforms) from the /proc/cpuinfo file.
         */
        static void TotalCPUThreadsCount() {
            // Open the file containing informations on CPU
            FILE* CPUInfo = fopen(CPUINFO_FILE, "rb") ;
            if (CPUInfo == NULL) {
                if (Log::IsReady()) {
                    Log::Write(
                               Log::LogError,
                               ProcessorMsg::Error::UnableToOpenCPUInfo,
                               CPUINFO_FILE
                              ) ;
                }

                TotalThreadOnCPUs = 1 ;
                return ;
            }

            char* Line = 0 ;
            size_t LineLength = 0 ;
            if (getdelim(&Line, &LineLength, '\0', CPUInfo) != 1) {
                char* Position = strstr(Line, CPU_PROCESSOR_LABEL) ;
                while (Position != NULL) {
                    TotalThreadOnCPUs++ ;
                    Position = strstr(Position + 1, CPU_PROCESSOR_LABEL) ;
                }
            }
            free(Line) ;
            fclose(CPUInfo) ;


            // Problem on reading /proc/cpuinfo ?
            if (TotalThreadOnCPUs == 0) {
                TotalThreadOnCPUs = 1 ;

                Log::Write(
                           Log::LogWarning,
                           ProcessorMsg::Error::UnableToOpenCPUInfo,
                           TotalThreadOnCPUs
                          ) ;
            }
        }


        /**
         * @brief   Get the informations on a single CPU from the /proc/cpuinfo file :
         *          Name, cores and threads available by CPU.
         */
        static void SingleCPUInfo() {
            // Open the file containing informations on CPU
            FILE* CPUInfo = fopen(CPUINFO_FILE, "rb") ;
            if (CPUInfo == NULL) {
                Log::Write(
                           Log::LogError,
                           ProcessorMsg::Error::UnableToOpenCPUInfo,
                           CPUINFO_FILE
                          ) ;

                ThreadsByCPU = 1 ;
                CoresByCPU = 1 ;
                return ;
            }


            char* Line = 0 ;
            char Label[LABEL_LENGTH] ;
            char ParsedValue[VALUE_LENGTH] ;
            size_t LineLength = 0 ;

            while (getline(&Line, &LineLength, CPUInfo) != 1) {
                size_t StopPosition = strchr(Line, ':') - Line ;

                if (StopPosition != 0) {
                    size_t PositionBefore = StopPosition - 1 ;
                    size_t PositionAfter = StopPosition + 1 ;

                    strncpy(Label, Line, PositionBefore) ;
                    Label[PositionBefore] = '\0' ;
                    String::Trim(Label) ;

                    if (strcmp(Label, CPU_THREADS_LABEL) == 0) {
                        strcpy(ParsedValue, Line + PositionAfter) ;
                        ThreadsByCPU = atoi(ParsedValue) ;
                    }
                    else if (strcmp(Label, CPU_CORES_LABEL) == 0) {
                        strcpy(ParsedValue, Line + PositionAfter) ;
                        CoresByCPU = atoi(ParsedValue) ;
                    }
                    else if (strcmp(Label, CPU_MODEL_NAME_LABEL) == 0) {
                        char TempNameBuffer[LABEL_LENGTH] ;
                        // Copy the first characters of CPU name
                        char* Name = Line + PositionAfter ;
                        String::Trim(Name) ;
                        strncpy(TempNameBuffer, Name, LABEL_LENGTH) ;
                        // Now trim the CPU name
                        Name = TempNameBuffer ;
                        TempNameBuffer[LABEL_LENGTH - 1] = '\0' ;
                        String::Trim(Name) ;
                        strcpy(CPUName, Name) ;
                    }
                    else if (strcmp(Label, CPU_FREQUENCY_LABEL) == 0) {
                        strcpy(ParsedValue, Line + PositionAfter) ;
                        Frequency = atoi(ParsedValue) ;
                    }
                    else if (strcmp(Label, CPU_FLAGS_LABEL) == 0) {
                        if (strstr(Line + PositionAfter, CPU_FLAG_HT_LABEL) != NULL) {
                            IsHyperThreaded = true ;
                        }
                    }
                }
            }

            memset(Label, 0, LABEL_LENGTH) ;
            memset(ParsedValue, 0, VALUE_LENGTH) ;
            free(Line) ;
            fclose(CPUInfo) ;
        }

        /**
         * @brief   Detect the endianness of the CPU.
         */
        static void DetectEndianness() {
            union {
                   int integer ;
                   char bytes[sizeof(int)] ;
                  } DetectEndianness ;

            DetectEndianness.integer = 0x01020304 ;

            // If little Endian, less significant byte is first
            if (DetectEndianness.bytes[0] == 0x04) {
                CPUEndianness = LittleEndian ;
            }
            else {
                if (DetectEndianness.bytes[0] == 0x01) {
                    CPUEndianness = BigEndian ;
                }
                else {
                    CPUEndianness = UnhandledEndianness ;
                }
            }
        }



        void InitInfo() {
            SingleCPUInfo() ;
            TotalCPUThreadsCount() ;
            DetectEndianness() ;

            if (ThreadsByCPU == 0) {
                if (IsHyperThreaded) ThreadsByCPU = 2 ;
                else ThreadsByCPU = 1 ;

                Log::Write(
                           Log::LogWarning,
                           ProcessorMsg::Warning::BadThreadsByCPU,
                           ThreadsByCPU
                          ) ;
            }

            if (CoresByCPU == 0) {
                if (IsHyperThreaded) CoresByCPU = TotalThreadOnCPUs / 2 ;
                else CoresByCPU = 1 ;

                Log::Write(
                           Log::LogWarning,
                           ProcessorMsg::Warning::BadCoresByCPU,
                           CoresByCPU
                          ) ;
            }

            if (CPUName == NULL) {
                Log::Write(
                           Log::LogWarning,
                           ProcessorMsg::Warning::NameNotFound,
                           CPUName
                        ) ;
            }

            Initialized = true ;
        }

        const char* GetName() {
            if (!Initialized) InitInfo() ;
            return CPUName ;
        }

        unsigned short CountCores() {
            if (!Initialized) InitInfo() ;
            return CoresByCPU ;
        }

        unsigned short CountThreads() {
            if (!Initialized) InitInfo() ;
            return ThreadsByCPU ;
        }

        unsigned short CountTotalThreads() {
            if (!Initialized) InitInfo() ;
            return TotalThreadOnCPUs ;
        }


        Endianness GetEndianness() {
            return CPUEndianness ;
        }


        void PrintInfo() {
            if (!Initialized) InitInfo() ;

            printf("%s%s\n\n", ProcessorMsg::Text::Name, CPUName) ;
            printf("%s%d MHz\n\n", ProcessorMsg::Text::Frequency, Frequency) ;
            printf("%s%d\n\n", ProcessorMsg::Text::Cores, CoresByCPU) ;
            printf("%s%d\n\n", ProcessorMsg::Text::Threads, TotalThreadOnCPUs) ;
            printf("%s%d\n\n", ProcessorMsg::Text::Hyperthreading, IsHyperThreaded) ;

            printf("%s", ProcessorMsg::Text::Endianness) ;
            switch (CPUEndianness) {
                case LittleEndian:
                    printf("%s\n\n", ProcessorMsg::Text::LittleEndian) ;
                    break ;

                case BigEndian:
                    printf("%s\n\n", ProcessorMsg::Text::BigEndian) ;
                    break ;

                default:
                    printf("%s\n\n", ProcessorMsg::Text::UnknownEndian) ;
                    break ;
            }
        }

    } ;

} ;
