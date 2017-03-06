inline float32x4_t Vector4f::selection(
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
inline Scalar Vector4f::horizontalAdd() {
    return m_inner[0] + m_inner[1] + m_inner[2] + m_inner[3] ;
}

inline void Vector4f::abs() {
    for (unsigned int index = 0 ; index < size() ; ++index) {
        if (m_inner[index] < ((Scalar) 0.)) {
            m_inner[index] = -m_inner[index] ;
        }
    }
}

inline void Vector4f::squared() {
    for (unsigned int index = 0 ; index < size() ; ++index) {
        m_inner[index] = m_inner[index] * m_inner[index] ;
    }
}

template <int i0, int i1, int i2, int i3>
void Vector4f::permute() {
    static_assert((i0 <= 3), "Bad value. Expected i0 <= 3") ;
    static_assert((i1 <= 3), "Bad value. Expected i1 <= 3") ;
    static_assert((i2 <= 3), "Bad value. Expected i2 <= 3") ;
    static_assert((i3 <= 3), "Bad value. Expected i3 <= 3") ;

    // Check if shuffling is required.
    const bool NeedShuffle = (i0 > 0)
                                || ((i1 != 1) && (i1 >= 0))
                                || ((i2 != 2) && (i2 >= 0))
                                || ((i3 != 3) && (i3 >= 0)) ;

    // Check if zeroing required.
    const bool DoZero = (((i0 | i1 | i2 | i3) < 0) && ((i0 | i1 | i2 | i3) & 0x80)) ;

    if (DoZero and !NeedShuffle) {
        // Only make some / all positions zeroed in the vector.
        if ((i0 | i1 | i2 | i3) < 0) {
            const float ZeroFloat = 0.f ;
            const int ZeroFloatAsInt = *((int*) &ZeroFloat) ;
            memset(&m_inner, ZeroFloatAsInt, sizeof(float32x4_t)) ;
        }
        else {
            int32x4_t MaskZeroPositions = Vector4i::constant<
                -int(i0 > -1),
                -int(i1 > -1),
                -int(i2 > -1),
                -int(i3 > -1)
            >() ;

            for (unsigned int index = 0 ; index < size() ; ++index) {
                int32_t binaryVecValue = *((int32_t*) &m_inner[index]) ;
                Scalar tmp = *((Scalar*) &(MaskZeroPositions[index])) ;
                int32_t binaryMaskValue = *((int32_t*) &tmp) ;
                m_inner[index] = binaryVecValue & binaryMaskValue ;
            }
        }
    }
    else {
        float32x4_t tmp = m_inner ;
        int32x4_t Indices ;
        Indices[0] = i0 ;
        Indices[1] = i1 ;
        Indices[2] = i2 ;
        Indices[3] = i3 ;

        if (NeedShuffle and !DoZero) {
            // Only shuffle the values in the vector.
            for (unsigned int index = 0 ; index < size() ; ++index) {
                m_inner[index] = tmp[Indices[index]] ;
            }
        }
        else if (((i0 & i1) < 0) && ((i2 | i3) >= 0)) {
            // Zero on lower elements, shuffle higher ones.
            m_inner[0] = 0.f ;
            m_inner[1] = 0.f ;
            for (unsigned int index = 2 ; index < size() ; ++index) {
                m_inner[index] = tmp[Indices[index]] ;
            }
        }
        else if ((i0 | i1) >= 0 && (i2 & i3) < 0) {
            // Zero on higher elements, shuffle lower ones.
            m_inner[2] = 0.f ;
            m_inner[3] = 0.f ;
            for (unsigned int index = 0 ; index < 2 ; ++index) {
                m_inner[index] = tmp[Indices[index]] ;
            }
        }
        else {
            // Shuffle the values in the vector.
            for (unsigned int index = 0 ; index < size() ; ++index) {
                tmp[index] = m_inner[Indices[index]] ;
            }

            // Make some / all positions zeroed in the vector.
            int32x4_t MaskZeroPositions = Vector4i::constant<
                -int(i0 > -1),
                -int(i1 > -1),
                -int(i2 > -1),
                -int(i3 > -1)
            >() ;

            for (unsigned int index = 0 ; index < size() ; ++index) {
                int32_t binaryVecValue = *((int32_t*) &m_inner[index]) ;
                Scalar tmp = *((Scalar*) &(MaskZeroPositions[index])) ;
                int32_t binaryMaskValue = *((int32_t*) &tmp) ;
                m_inner[index] = binaryVecValue & binaryMaskValue ;
            }
        }
    }
}

template <bool i0, bool i1, bool i2, bool i3>
inline void Vector4f::changeSign() {
    if (i0) m_inner[0] = -m_inner[0] ;
    if (i1) m_inner[1] = -m_inner[1] ;
    if (i2) m_inner[2] = -m_inner[2] ;
    if (i3) m_inner[3] = -m_inner[3] ;
}


                                                  /** CONDITIONAL ARITHMETIC **/
inline void Vector4f::addIf(const Vector4f::Mask& mask, const Vector4f& add) {
    *this += (add & mask) ;
}

inline void Vector4f::mulIf(const Vector4f::Mask& mask, const Vector4f& mul) {
    *this *= select(mask, mul, (Scalar) 1.) ;
}

inline Scalar Vector4f::dot(const Vector4f& other) const {
    return dot(*this, other) ;
}

inline Vector4f Vector4f::cross(const Vector4f& other) const {
    return cross(*this, other) ;
}

inline Scalar Vector4f::norm() const {
    return dot(*this) ;
}


                                                        /** STATIC FUNCTIONS **/
inline Vector4f Vector4f::select(
    const Vector4f::Mask& selector,
    const Vector4f& a,
    const Vector4f& b
) {
    return selection((float32x4_t)selector, (float32x4_t)a, (float32x4_t)b) ;
}

template <unsigned char i0, unsigned char i1, unsigned char i2, unsigned char i3>
inline Vector4f& Vector4f::shuffle(
    const Vector4f& input,
    Vector4f& output
) {
    static_assert((i0 <= 3), "Bad value. Expected i0 <= 3") ;
    static_assert((i1 <= 3), "Bad value. Expected i1 <= 3") ;
    static_assert((i2 <= 3), "Bad value. Expected i2 <= 3") ;
    static_assert((i3 <= 3), "Bad value. Expected i3 <= 3") ;

    float32x4_t tmp = input.m_inner ;
    int32x4_t Indices ;
    Indices[0] = i0 ;
    Indices[1] = i1 ;
    Indices[2] = i2 ;
    Indices[3] = i3 ;

    for (unsigned int index = 0 ; index < size() ; ++index) {
        output.m_index[index] = tmp[Indices[index]] ;
    }

    return output ;
}

inline Vector4f Vector4f::min(const Vector4f& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar valueA = (*((float32x4_t*) a))[index] ;
        Scalar valueB = (*((float32x4_t*) b))[index] ;
        result[index] = (valueA < valueB) ? valueA : valueB ;
    }
    return result ;
}

inline Vector4f Vector4f::max(const Vector4f& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar valueA = (*((float32x4_t*) a))[index] ;
        Scalar valueB = (*((float32x4_t*) b))[index] ;
        result[index] = (valueA > valueB) ? valueA : valueB ;
    }
    return result ;
}

inline Vector4f Vector4f::abs(const Vector4f& vec) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar value = (*((float32x4_t*) vec))[index] ;
        if (Math::isNegative(value)) {
            result[index] = -value ;
        }
    }

    return result ;
}

inline Vector4f Vector4f::sqrt(const Vector4f& vec) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar value = (*((float32x4_t*) vec))[index] ;
        result[index] = FastMath::sqrt(value) ;
    }
    return result ;
}

inline Vector4f Vector4f::square(const Vector4f& vec) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar value = (*((float32x4_t*) vec))[index] ;
        result[index] = value * value ;
    }
    return result ;
}

inline Scalar Vector4f::dot(const Vector4f& a, const Vector4f& b) {
    Vector4f product = a * b ;
    return product.horizontalAdd() ;
}

inline Vector4f Vector4f::cross(const Vector4f& a, const Vector4f& b) {
    return Vector4f(
        (a.m_inner[1] * b.m_inner[2] - a.m_inner[2] * b.m_inner[1]),
        (a.m_inner[2] * b.m_inner[0] - a.m_inner[0] * b.m_inner[2]),
        (a.m_inner[0] * b.m_inner[1] - a.m_inner[1] * b.m_inner[0]),
        0.f
    ) ;
}

inline Vector4f Vector4f::fast_recriprocal(const Vector4f& vec) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar value = (*((float32x4_t*) vec))[index] ;
        result[index] = ((Scalar) 1.) / value ;
    }
    return result ;
}

inline Vector4f Vector4f::fast_rsqrt(const Vector4f& vec) {
    float32x4_t result ;
    float32x4_t vecLocal = vec ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar value = (*((float32x4_t*) vec))[index] ;
        result[index] = ((Scalar) 1.) / FastMath::sqrt(value) ;
    }
    return result ;
}

inline Vector4f Vector4f::fast_sqrt(const Vector4f& vec) {
    float32x4_t result ;
    float32x4_t vecLocal = vec ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar value = (*((float32x4_t*) vec))[index] ;
        result[index] = FastMath::sqrt(value) ;
    }
    return result ;
}


                                                        /** FUSED OPERATIONS **/
inline Vector4f Vector4f::mul_add(
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

inline Vector4f Vector4f::mul_sub(
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

inline Vector4f Vector4f::sub_mul(
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


                                                     /*** GETTERS / SETTERS ***/
inline Vector4f::Mask Vector4f::isNegative() {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar value = m_inner[index] ;
        uint32_t isNegative = -uint32_t(Math::isNegative(value)) ;
        result[index] = *((float*) &isNegative) ;
    }
    return result ;
}

inline Vector4f::Mask Vector4f::isInfinite() {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar value = m_inner[index] ;
        uint32_t isInfinite = -uint32_t(Math::isInf(value)) ;
        result[index] = *((float*) &isInfinite) ;
    }
    return result ;
}

inline Vector4f::Mask Vector4f::isNaN() {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        Scalar value = m_inner[index] ;
        uint32_t isNaN = -uint32_t(Math::isNaN(value)) ;
        result[index] = *((float*) &isNaN) ;
    }
    return result ;
}

inline void Vector4f::set(const Array4f& array) {
    std::copy(array.begin(), array.end(), m_inner.begin()) ;
}

inline void Vector4f::get(Array4f& array) const {
    std::copy(array.begin(), array.end(), m_inner.begin()) ;
}

inline size_t Vector4f::length() const {
    return Array4f::size() ;
}

inline size_t Vector4f::size() {
    return 4 ;
}

inline void Vector4f::print() {
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
inline uint32_t Vector4f::getControlWord() {
    return 0 ;
}

inline void Vector4f::setControlWord(uint32_t) {}

inline void Vector4f::noSubnormals() {}

inline void Vector4f::resetControlWord() {}


                                                             /*** OPERATORS ***/
                                                        /** AFFECT OPERATORS **/
inline Vector4f& Vector4f::operator=(const Vector4f& vec4) {
    auto other = (float32x4_t) vec4 ;
    std::copy(other.begin(), other.end(), m_inner.begin()) ;
    return *this ;
}

inline Vector4f& Vector4f::operator=(const Scalar& value) {
    for (unsigned int index = 0 ; index < size() ; ++index) {
        m_inner[index] = value ;
    }
    return *this ;
}

inline Vector4f& Vector4f::operator=(const float32x4_t& vec) {
    std::copy(vec.begin(), vec.end(), m_inner.begin()) ;
    return *this ;
}

inline Vector4f& Vector4f::operator=(const Vector4i& vec4) {
    int32x4_t vec4Array = vec4 ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        m_inner[index] = vec4Array[index] ;
    }
    return *this ;
}

inline Vector4f& Vector4f::operator=(const Vector4ui& vec4) {
    uint32x4_t vec4Array = vec4 ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        m_inner[index] = vec4Array[index] ;
    }
    return *this ;
}

                                                            /** CAST OPERATORS **/
inline Vector4f::operator float32x4_t() const {
    return m_inner ;
}

inline Vector4f::operator float32x4_t*() const {
    return (float32x4_t*) &m_inner ;
}

inline Vector4f::operator Vector4i() const {
    return Vector4i(m_inner) ;
}

inline Vector4f::operator Vector4ui() const {
    return Vector4ui(m_inner) ;
}
