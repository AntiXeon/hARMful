#include <MINDOptions.hpp>
#ifdef USE_INTEL_SSE2

#include <simd/intel_sse2/integers/SIMDVector4ui.hpp>

namespace Mind {
    namespace SSE2 {
                                              /** CONSTRUCTION / DESTRUCTION **/
        Vector4ui::Vector4ui() : Vector4uint32() {}

        Vector4ui::Vector4ui(
                             const uint32_t& i1,
                             const uint32_t& i2,
                             const uint32_t& i3,
                             const uint32_t& i4
                            ) : Vector4uint32(i1, i2, i3, i4) {}

        Vector4ui::Vector4ui(const uint32_t& value) : Vector4uint32(value) {}

        Vector4ui::Vector4ui(const __m128i& vec) : Vector4uint32(vec) {}

        Vector4ui::Vector4ui(const __m128& vec) : Vector4uint32(vec) {}

        Vector4ui::~Vector4ui() {}


                                                        /** STATIC FUNCTIONS **/
        Vector4ui Vector4ui::min(const Vector4ui& a, const Vector4ui& b) {
            #if defined(USE_INTEL_SSE4_1)
                return _mm_min_epu32((__m128i) a, (__m128i) b) ;
            #else
                __m128i greater = _mm_cmpgt_epi32((__m128i) a, (__m128i) b) ;
                return Vector4::selection(greater, (__m128i) b, (__m128i) a) ;
            #endif
        }

        Vector4ui Vector4ui::max(const Vector4ui& a, const Vector4ui& b) {
            #if defined(USE_INTEL_SSE4_1)
                return _mm_max_epu32((__m128i) a, (__m128i) b) ;
            #else
                __m128i greater = _mm_cmpgt_epi32((__m128i) a, (__m128i) b) ;
                return Vector4::selection(greater, (__m128i) a, (__m128i) b) ;
            #endif
        }

        void Vector4ui::print() {
            Array4i& splitted = m_inner.arr ;
            std::cout << "Vector4ui @"
                                    << std::hex << this << std::dec << "= { "
                                        << splitted[0] << ", "
                                        << splitted[1] << ", "
                                        << splitted[2] << ", "
                                        << splitted[3]
                                    << " }"
                                << std::endl ;
        }
    } ;
} ;

#endif
