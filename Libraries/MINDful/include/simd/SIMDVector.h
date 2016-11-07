/*******************************************/
/* MINDful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* File : 		SIMDVector.h               */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	10/07/2015                 */
/* UPDATE:      10/07/2015                 */
/*                                         */
/* Include this file into any application  */
/* using SIMD vectors (instead of separate */
/* headers).                               */
/*******************************************/

#ifndef __SIMDVECTOR_SELECTOR__
#define __SIMDVECTOR_SELECTOR__

#include <MINDOptions.h>
#include <simd/SIMDTypes.h>

    #if     defined(USE_INTEL_SSE2)
        #define PARALLELIZATION_ENABLED
        #include <simd/intel_sse2/integers/SIMDVector4.h>
        #include <simd/intel_sse2/integers/SIMDVector4i.h>
        #include <simd/intel_sse2/integers/SIMDVector4ui.h>
        #include <simd/intel_sse2/floats/SIMDVector4f.h>
    #elif   defined(USE_ARM_NEON)
        #define PARALLELIZATION_ENABLED
        #include <simd/arm_neon/integers/SIMDVector4.h>
        #include <simd/arm_neon/integers/SIMDVector4i.h>
        #include <simd/arm_neon/integers/SIMDVector4ui.h>
        #include <simd/arm_neon/floats/SIMDVector4f.h>
    #else
        #include <simd/emulated/integers/SIMDVector4i.h>
        #include <simd/emulated/integers/SIMDVector4ui.h>
        #include <simd/emulated/floats/SIMDVector4f.h>
    #endif

#endif
