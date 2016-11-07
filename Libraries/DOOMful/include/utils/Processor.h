/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Processor.h                */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	04/10/2014                 */
/* UPDATE:      04/10/2014                 */
/*                                         */
/* API to get processor informations.      */
/*******************************************/

#ifndef __DOOM__PROCESSOR__
#define __DOOM__PROCESSOR__


namespace Doom {

    namespace Processor {
        /** @brief  Endianness of the CPU. Possible values. */
        typedef enum Endianness {
            LittleEndian,
            BigEndian,
            UnhandledEndianness
        } Endianness ;


        /** @brief  Initialize informations on the CPU. */
        void InitInfo() ;


        /**
         * @brief   Get the name of the CPU.
         * @return  The name of the CPU.
         */
        const char* GetName() ;

        /**
         * @brief   Get the amount of cores available on a single CPU.
         * @return  Amount of cores on a single CPU.
         */
        unsigned short CountCores() ;

        /**
         * @brief   Get the amount of threads available on a single CPU (may be
         *          different from CoresByCPU in case CPU is hyperthreaded).
         * @return  Amount of threads on a single CPU.
         */
        unsigned short CountThreads() ;

        /**
         * @brief   Get the total amount of threads on CPUs (useful for multi-CPUs
         *          platforms).
         * @return  Total amount of threads on multi-CPUs platforms.
         */
        unsigned short CountTotalThreads() ;

        /**
         * @brief   Detect the endianness of the CPU.
         * @return  The endianness of the CPU.
         * @see     Endianness
         */
        Endianness GetEndianness() ;


        /** @brief  Print CPU informations. */
        void PrintInfo() ;
    } ;

} ;

#endif
