#include <MINDOptions.hpp>
#ifdef USE_NO_SIMD

#include <simd/emulated/integers/SIMDVector4ui.hpp>

namespace Mind {
    namespace EmulatedSIMD {
        uint32x4_t Vector4ui::selection(
            const uint32x4_t& selector,
            const uint32x4_t& a,
            const uint32x4_t& b
        ) {
            uint32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                result[index] = selector[index] ? a[index] : b[index] ;
            }
            return result ;
        }

                                                      /** CONSTRUCTION / DESTRUCTION **/
        Vector4ui::Vector4ui() {}

        Vector4ui::Vector4ui(
            const uint32_t i1,
            const uint32_t i2,
            const uint32_t i3,
            const uint32_t i4
        ) {
            m_inner[0] = i1 ;
            m_inner[1] = i2 ;
            m_inner[2] = i3 ;
            m_inner[3] = i4 ;
        }

        Vector4ui::Vector4ui(const uint32_t value) {
            m_inner[0] = value ;
            m_inner[1] = value ;
            m_inner[2] = value ;
            m_inner[3] = value ;
        }

        Vector4ui::Vector4ui(const uint32x4_t& vec) {
            std::copy(vec.begin(), vec.end(), m_inner.begin()) ;
        }

        Vector4ui::Vector4ui(const float32x4_t& vec) {
            float32x4_t vecLocal = vec ;
            m_inner[0] = static_cast<uint32_t>(vecLocal[0]) ;
            m_inner[1] = static_cast<uint32_t>(vecLocal[1]) ;
            m_inner[2] = static_cast<uint32_t>(vecLocal[2]) ;
            m_inner[3] = static_cast<uint32_t>(vecLocal[3]) ;
        }

        Vector4ui::~Vector4ui() {}


                                                                /** STATIC FUNCTIONS **/
        Vector4ui Vector4ui::min(const Vector4ui& a, const Vector4ui& b) {
            uint32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                result[index] = std::min((*(uint32x4_t*)a)[index], (*(uint32x4_t*)b)[index]) ;
            }
            return result ;
        }

        Vector4ui Vector4ui::max(const Vector4ui& a, const Vector4ui& b) {
            uint32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                result[index] = std::max((*(uint32x4_t*)a)[index], (*(uint32x4_t*)b)[index]) ;
            }
            return result ;
        }

        void Vector4ui::print() {
            std::cout << "Vector4ui @"
                                    << std::hex << this << std::dec << "= { "
                                        << m_inner[0] << ", "
                                        << m_inner[1] << ", "
                                        << m_inner[2] << ", "
                                        << m_inner[3]
                                    << " }"
                                << std::endl ;
        }


                                                                      /*** UTILITIES ***/
        int64_t Vector4ui::horizontalAdd() {
            return m_inner[0] + m_inner[1] + m_inner[2] + m_inner[3] ;
        }


        size_t Vector4ui::length() const {
            return size() ;
        }

        size_t Vector4ui::size() {
            return 4 ;
        }


        Vector4ui::operator uint32x4_t() const {
            return m_inner ;
        }

        Vector4ui::operator uint32x4_t*() const {
            return (uint32x4_t*) &m_inner ;
        }
    } ;
} ;

#endif
