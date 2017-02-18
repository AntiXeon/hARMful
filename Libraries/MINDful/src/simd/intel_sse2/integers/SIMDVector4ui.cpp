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

        Vector4ui::Vector4ui(const uint32x4_t& vec) : Vector4uint32(vec) {}

        Vector4ui::Vector4ui(const float32x4_t& vec) : Vector4uint32(vec) {}

        Vector4ui::~Vector4ui() {}


                                                        /** STATIC FUNCTIONS **/
        Vector4ui Vector4ui::min(const Vector4ui& a, const Vector4ui& b) {
            #if defined(USE_INTEL_SSE4_1)
                return _mm_min_epu32(a, b) ;
            #else
                int32x4_t greater = _mm_cmpgt_epi32(a, b) ;
                return Vector4::selection(greater, b, a) ;
            #endif
        }

        Vector4ui Vector4ui::max(const Vector4ui& a, const Vector4ui& b) {
            #if defined(USE_INTEL_SSE4_1)
                return _mm_max_epu32(a, b) ;
            #else
                int32x4_t greater = _mm_cmpgt_epi32(a, b) ;
                return Vector4::selection(greater, a, b) ;
            #endif
        }

        void Vector4ui::print() {
            int32_t* splitted = (int32_t*) &m_inner ;
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
