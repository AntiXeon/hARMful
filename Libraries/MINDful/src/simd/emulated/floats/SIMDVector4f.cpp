#include <MINDOptions.hpp>
#ifdef USE_NO_SIMD

#include <simd/emulated/floats/SIMDVector4f.hpp>
#include <Math.hpp>

namespace Mind {
    namespace EmulatedSIMD {
        float32x4_t Vector4f::selection(
            const float32x4_t& selector,
            const float32x4_t& a,
            const float32x4_t& b
        ) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                bool isNan = Math::isNaN(selector[index]) ;
                result[index] = isNan ? a[index] : b[index] ;
            }
            return result ;
        }


                                              /** CONSTRUCTION / DESTRUCTION **/
        Vector4f::Vector4f() {}

        Vector4f::Vector4f(
            const Scalar& f1,
            const Scalar& f2,
            const Scalar& f3,
            const Scalar& f4
        ) {
            m_inner[0] = f1 ;
            m_inner[1] = f2 ;
            m_inner[2] = f3 ;
            m_inner[3] = f4 ;
        }

        Vector4f::Vector4f(const Scalar& value) {
            m_inner[0] = value ;
            m_inner[1] = value ;
            m_inner[2] = value ;
            m_inner[3] = value ;
        }

        Vector4f::Vector4f(const float32x4_t& vec) {
            std::copy(vec.begin(), vec.end(), m_inner.begin()) ;
        }

        Vector4f::~Vector4f() {}


                                                              /*** UTILITIES ***/
        Scalar Vector4f::horizontalAdd() {
            return m_inner[0] + m_inner[1] + m_inner[2] + m_inner[3] ;
        }

        void Vector4f::abs() {
            for (unsigned int index = 0 ; index < size() ; ++index) {
                if (m_inner[index] < ((Scalar) 0.)) {
                    m_inner[index] = -m_inner[index] ;
                }
            }
        }

        void Vector4f::squared() {
            for (unsigned int index = 0 ; index < size() ; ++index) {
                m_inner[index] = m_inner[index] * m_inner[index] ;
            }
        }

                                                  /** CONDITIONAL ARITHMETIC **/
        void Vector4f::addIf(const Vector4f::Mask& mask, const Vector4f& add) {
            *this += (add & mask) ;
        }

        void Vector4f::mulIf(const Vector4f::Mask& mask, const Vector4f& mul) {
            *this *= select(mask, mul, (Scalar) 1.) ;
        }

        Scalar Vector4f::dot(const Vector4f& other) const {
            return dot(*this, other) ;
        }

        Scalar Vector4f::norm() const {
            return dot(*this) ;
        }


                                                        /** STATIC FUNCTIONS **/
        Vector4f Vector4f::select(
            const Vector4f::Mask& selector,
            const Vector4f& a,
            const Vector4f& b
        ) {
            return selection((float32x4_t)selector, a.m_inner, b.m_inner) ;
        }

        Vector4f Vector4f::min(const Vector4f& a, const Vector4f& b) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar valueA = (*((float32x4_t*) a))[index] ;
                Scalar valueB = (*((float32x4_t*) b))[index] ;
                result[index] = (valueA < valueB) ? valueA : valueB ;
            }
            return result ;
        }

        Vector4f Vector4f::max(const Vector4f& a, const Vector4f& b) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar valueA = (*((float32x4_t*) a))[index] ;
                Scalar valueB = (*((float32x4_t*) b))[index] ;
                result[index] = (valueA > valueB) ? valueA : valueB ;
            }
            return result ;
        }

        Vector4f Vector4f::abs(const Vector4f& vec) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar value = (*((float32x4_t*) vec))[index] ;
                if (Math::isNegative(value)) {
                    result[index] = -value ;
                }
            }

            return result ;
        }

        Vector4f Vector4f::sqrt(const Vector4f& vec) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar value = (*((float32x4_t*) vec))[index] ;
                result[index] = FastMath::sqrt(value) ;
            }
            return result ;
        }

        Vector4f Vector4f::square(const Vector4f& vec) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar value = (*((float32x4_t*) vec))[index] ;
                result[index] = value * value ;
            }
            return result ;
        }

        Scalar Vector4f::dot(const Vector4f& a, const Vector4f& b) {
            Vector4f product = a * b ;
            return product.horizontalAdd() ;
        }

        Vector4f Vector4f::fast_recriprocal(const Vector4f& vec) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar value = (*((float32x4_t*) vec))[index] ;
                result[index] = ((Scalar) 1.) / value ;
            }
            return result ;
        }

        Vector4f Vector4f::fast_rsqrt(const Vector4f& vec) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar value = (*((float32x4_t*) vec))[index] ;
                result[index] = ((Scalar) 1.) / FastMath::sqrt(value) ;
            }
            return result ;
        }

        Vector4f Vector4f::fast_sqrt(const Vector4f& vec) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar value = (*((float32x4_t*) vec))[index] ;
                result[index] = FastMath::sqrt(value) ;
            }
            return result ;
        }


                                                        /** FUSED OPERATIONS **/
        Vector4f Vector4f::mul_add(
            const Vector4f& mula,
            const Vector4f& mulb,
            const Vector4f& add
        ) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar mulaValue = (*(float32x4_t*) mula)[index] ;
                Scalar mulbValue = (*(float32x4_t*) mulb)[index] ;
                Scalar addValue = (*(float32x4_t*) add)[index] ;
                result[index] = (mulaValue * mulbValue) + addValue ;
            }
            return result ;
        }

        Vector4f Vector4f::mul_sub(
            const Vector4f& mula,
            const Vector4f& mulb,
            const Vector4f& sub
        ) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar mulaValue = (*(float32x4_t*) mula)[index] ;
                Scalar mulbValue = (*(float32x4_t*) mulb)[index] ;
                Scalar subValue = (*(float32x4_t*) sub)[index] ;
                result[index] = (mulaValue * mulbValue) - subValue ;
            }
            return result ;
        }

        Vector4f Vector4f::sub_mul(
            const Vector4f& sub,
            const Vector4f& mula,
            const Vector4f& mulb
        ) {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar mulaValue = (*(float32x4_t*) mula)[index] ;
                Scalar mulbValue = (*(float32x4_t*) mulb)[index] ;
                Scalar subValue = (*(float32x4_t*) sub)[index] ;
                result[index] = subValue - (mulaValue * mulbValue) ;
            }
            return result ;
        }

        void Vector4f::transposeMatrix(
            Vector4f& row1,
            Vector4f& row2,
            Vector4f& row3,
            Vector4f& row4
        ) {
             float32x4_t col1, col2, col3, col4 ;
            // Prepare transposition from row1 to col1.
            col1[0] = row1.m_inner[0] ;
            col1[1] = row2.m_inner[0] ;
            col1[2] = row3.m_inner[0] ;
            col1[3] = row4.m_inner[0] ;
            // Prepare transposition from row2 to col2.
            col2[0] = row1.m_inner[1] ;
            col2[1] = row2.m_inner[1] ;
            col2[2] = row3.m_inner[1] ;
            col2[3] = row4.m_inner[1] ;
            // Prepare transposition from row3 to col3.
            col3[0] = row1.m_inner[2] ;
            col3[1] = row2.m_inner[2] ;
            col3[2] = row3.m_inner[2] ;
            col3[3] = row4.m_inner[2] ;
            // Prepare transposition from row4 to col4.
            col4[0] = row1.m_inner[3] ;
            col4[1] = row2.m_inner[3] ;
            col4[2] = row3.m_inner[3] ;
            col4[3] = row4.m_inner[3] ;

            // Transpose rows to columns.
            row1 = col1 ;
            row2 = col2 ;
            row3 = col3 ;
            row4 = col4 ;
        }


                                                     /*** GETTERS / SETTERS ***/
        Vector4f::Mask Vector4f::isNegative() {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar value = m_inner[index] ;
                uint32_t isNegative = -uint32_t(std::isless(value, 0.f)) ;
                float* tmpPtr = reinterpret_cast<float*>(&isNegative) ;
                result[index] = *tmpPtr ;
            }
            return result ;
        }

        Vector4f::Mask Vector4f::isInfinite() {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar value = m_inner[index] ;
                uint32_t isInfinite = -uint32_t(std::isless(value, 0.f)) ;
                float* tmpPtr = reinterpret_cast<float*>(&isInfinite) ;
                result[index] = *tmpPtr ;
            }
            return result ;
        }

        Vector4f::Mask Vector4f::isNaN() {
            float32x4_t result ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                Scalar value = m_inner[index] ;
                uint32_t isNaN = -uint32_t(Math::isNaN(value)) ;
                float* tmpPtr = reinterpret_cast<float*>(&isNaN) ;
                result[index] = *tmpPtr ;
            }
            return result ;
        }

        #ifdef ALIGNED_ARRAY
            void Vector4f::set(const AlignedArray4f& array) {
                std::copy(array.begin(), array.end(), m_inner.begin()) ;
            }

            void Vector4f::get(AlignedArray4f& array) const {
                std::copy(m_inner.begin(), m_inner.end(), array.begin()) ;
            }
        #else
            void Vector4f::set(const Array4f& array) {
                std::copy(array.begin(), array.end(), m_inner.begin()) ;
            }

            void Vector4f::get(Array4f& array) const {
                std::copy(m_inner.begin(), m_inner.end(), array.begin()) ;
            }
        #endif



        size_t Vector4f::length() const {
            return Vector4f::size() ;
        }

        size_t Vector4f::size() {
            return 4 ;
        }

        void Vector4f::print() {
            std::cout << "Vector4f @"
                                    << std::hex << this << std::dec << "= { "
                                        << m_inner[0] << ", "
                                        << m_inner[1] << ", "
                                        << m_inner[2] << ", "
                                        << m_inner[3]
                                    << " }"
                                << std::endl ;
        }

                                                                    /*** MXCSR ***/
        uint32_t Vector4f::getControlWord() {
            return 0 ;
        }

        void Vector4f::setControlWord(uint32_t) {}

        void Vector4f::noSubnormals() {}

        void Vector4f::resetControlWord() {}


                                                             /*** OPERATORS ***/
                                                        /** AFFECT OPERATORS **/
        Vector4f& Vector4f::operator=(const Vector4f& vec4) {
            auto other = (float32x4_t) vec4 ;
            std::copy(other.begin(), other.end(), m_inner.begin()) ;
            return *this ;
        }

        Vector4f& Vector4f::operator=(const Scalar& value) {
            for (unsigned int index = 0 ; index < size() ; ++index) {
                m_inner[index] = value ;
            }
            return *this ;
        }

        Vector4f& Vector4f::operator=(const float32x4_t& vec) {
            std::copy(vec.begin(), vec.end(), m_inner.begin()) ;
            return *this ;
        }

        Vector4f& Vector4f::operator=(const Vector4i& vec4) {
            int32x4_t vec4Array = vec4 ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                m_inner[index] = vec4Array[index] ;
            }
            return *this ;
        }

        Vector4f& Vector4f::operator=(const Vector4ui& vec4) {
            uint32x4_t vec4Array = vec4 ;
            for (unsigned int index = 0 ; index < size() ; ++index) {
                m_inner[index] = vec4Array[index] ;
            }
            return *this ;
        }

        Scalar& Vector4f::operator[](const int& index) {
            return m_inner[index] ;
        }

                                                            /** CAST OPERATORS **/
        Vector4f::operator float32x4_t() const {
            return m_inner ;
        }

        Vector4f::operator float32x4_t*() const {
            return (float32x4_t*) &m_inner ;
        }

        Vector4f::operator float*() const {
            return (float*) m_inner.data() ;
        }

        Vector4f::operator Vector4i() const {
            return Vector4i(m_inner) ;
        }

        Vector4f::operator Vector4ui() const {
            return Vector4ui(m_inner) ;
        }
    } ;
} ;

#endif
