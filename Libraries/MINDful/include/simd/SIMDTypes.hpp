#ifndef __MIND__SIMD_TYPES__
#define __MIND__SIMD_TYPES__

#include <array>
#include <cstdint>
#include <MINDOptions.hpp>

/** Arrays **/
using AlignedArray4i alignas(ALIGNMENT_ON_STACK) = std::array<int32_t, 4> ;
using AlignedArray4f alignas(ALIGNMENT_ON_STACK) = std::array<float, 4> ;

using Array4i = std::array<int32_t, 4> ;
using Array4f = std::array<float, 4> ;

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
        typedef std::array<int8_t, 8>    int8x8_t    ;   //  8-bit integer data
        typedef std::array<uint8_t, 8>   uint8x8_t   ;
        typedef std::array<int16_t, 4>   int16x4_t   ;   // 16-bit integer data
        typedef std::array<uint8_t, 4>   uint16x4_t  ;
        typedef std::array<int32_t, 2>   int32x2_t   ;   // 32-bit integer data
        typedef std::array<uint32_t, 2>  uint32x2_t  ;
        typedef std::array<int64_t, 1>   int64x1_t   ;   // 64-bit integer data
        typedef std::array<uint64_t, 1>  uint64x1_t  ;
        typedef std::array<float, 2>     float32x2_t ;   // 32-bit float data
        typedef std::array<double, 1>    float64x1_t ;   // 64-bit float data

        // 128-bit types
        typedef std::array<int8_t, 16>   int8x16_t   ;   //  8-bit integer data
        typedef std::array<uint8_t, 16>  uint8x16_t  ;
        typedef std::array<int16_t, 8>   int16x8_t   ;   // 16-bit integer data
        typedef std::array<uint16_t, 8>  uint16x8_t  ;
        typedef std::array<int32_t, 4>   int32x4_t   ;   // 32-bit integer data
        typedef std::array<uint32_t, 4>  uint32x4_t  ;
        typedef std::array<int64_t, 2>   int64x2_t   ;   // 64-bit integer data
        typedef std::array<int64_t, 2>   uint64x2_t  ;
        typedef std::array<float, 4>     float32x4_t ;   // 32-bit float data
        typedef std::array<double, 2>    float64x2_t ;   // 64-bit float data
    #endif

#endif
