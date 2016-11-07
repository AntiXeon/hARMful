#ifndef __MIND_SIMD_TYPES__
#define __MIND_SIMD_TYPES__

#include <stdint.h>
#include <utils/Array.h>
#include <utils/AlignedArray.h>
#include <MINDOptions.h>

/** Arrays **/
typedef Doom::Array<float, 4> Array4f ;
typedef Doom::AlignedArray<float, 4, ALIGNMENT_ON_STACK> AlignedArray4f ;

typedef Doom::Array<int32_t, 4> Array4i ;
typedef Doom::AlignedArray<int32_t, 4, ALIGNMENT_ON_STACK> AlignedArray4i ;


            /** REMARK: Types names are based on NEON naming. **/

    #if defined(USE_INTEL_SSE2)
        // 64bit types
        typedef __m64   int8x8_t        ;   //  8-bit integer data
        typedef __m64   uint8x8_t       ;
        typedef __m64   int16x4_t       ;   // 16-bit integer data
        typedef __m64   uint16x4_t      ;
        typedef __m64   int32x2_t       ;   // 32-bit integer data
        typedef __m64   uint32x2_t      ;
        typedef __m64   int64x1_t       ;   // 64-bit integer data
        typedef __m64   uint64x1_t      ;
        typedef __m128  float32x2_t     ;   // 32-bit float data
        typedef __m128d float64x1_t     ;   // 64-bit float data

        // 128-bit types
        typedef __m128i int8x16_t       ;   //  8-bit integer data
        typedef __m128i uint8x16_t      ;
        typedef __m128i int16x8_t       ;   // 16-bit integer data
        typedef __m128i uint16x8_t      ;
        typedef __m128i int32x4_t       ;   // 32-bit integer data
        typedef __m128i uint32x4_t      ;
        typedef __m128i int64x2_t       ;   // 64-bit integer data
        typedef __m128i uint64x2_t      ;
        typedef __m128  float32x4_t     ;   // 32-bit float data
        typedef __m128d float64x2_t     ;   // 64-bit float data
    #elif defined(USE_ARM_NEON)
        // 64bit types
        // typedef int8x8_t    int8x8_t    ;   //  8-bit integer data
        // typedef uint8x8_t   uint8x8_t   ;
        // typedef int16x4_t   int16x4_t   ;   // 16-bit integer data
        // typedef uint16x4_t  uint16x4_t  ;
        // typedef int32x2_t   int32x2_t   ;   // 32-bit integer data
        // typedef uint32x2_t  uint32x2_t  ;
        // typedef int64x1_t   int64x1_t   ;   // 64-bit integer data
        // typedef uint64x1_t  uint64x1_t  ;
        // typedef float32x2_t float32x2_t ;   // 32-bit float data
        // typedef float64x1_t float64x1_t ;   // 64-bit float data
        //
        // 128-bit types
        // typedef int8x16_t   int8x16_t   ;   //  8-bit integer data
        // typedef uint8x16_t  uint8x16_t  ;
        // typedef int16x8_t   int16x8_t   ;   // 16-bit integer data
        // typedef uint16x8_t  uint16x8_t  ;
        // typedef int32x4_t   int32x4_t   ;   // 32-bit integer data
        // typedef uint32x4_t  uint32x4_t  ;
        // typedef int64x2_t   int64x2_t   ;   // 64-bit integer data
        // typedef uint64x2_t  uint64x2_t  ;
        // typedef float32x4_t float32x4_t ;   // 32-bit float data
        // typedef float64x2_t float64x2_t ;   // 64-bit float data
    #elif defined(USE_NO_SIMD)   // C/C++
        // 64bit types
        typedef Doom::Array<int8_t, 8>    int8x8_t    ;   //  8-bit integer data
        typedef Doom::Array<uint8_t, 8>   uint8x8_t   ;
        typedef Doom::Array<int16_t, 4>   int16x4_t   ;   // 16-bit integer data
        typedef Doom::Array<uint8_t, 4>   uint16x4_t  ;
        typedef Doom::Array<int32_t, 2>   int32x2_t   ;   // 32-bit integer data
        typedef Doom::Array<uint32_t, 2>  uint32x2_t  ;
        typedef Doom::Array<int64_t, 1>   int64x1_t   ;   // 64-bit integer data
        typedef Doom::Array<uint64_t, 1>  uint64x1_t  ;
        typedef Doom::Array<float, 2>     float32x2_t ;   // 32-bit float data
        typedef Doom::Array<double, 1>    float64x1_t ;   // 64-bit float data

        // 128-bit types
        typedef Doom::Array<int8_t, 16>   int8x16_t   ;   //  8-bit integer data
        typedef Doom::Array<uint8_t, 16>  uint8x16_t  ;
        typedef Doom::Array<int16_t, 8>   int16x8_t   ;   // 16-bit integer data
        typedef Doom::Array<uint16_t, 8>  uint16x8_t  ;
        typedef Doom::Array<int32_t, 4>   int32x4_t   ;   // 32-bit integer data
        typedef Doom::Array<uint32_t, 4>  uint32x4_t  ;
        typedef Doom::Array<int64_t, 2>   int64x2_t   ;   // 64-bit integer data
        typedef Doom::Array<int64_t, 2>   uint64x2_t  ;
        typedef Doom::Array<float, 4>     float32x4_t ;   // 32-bit float data
        typedef Doom::Array<double, 2>    float64x2_t ;   // 64-bit float data
    #endif

#endif
