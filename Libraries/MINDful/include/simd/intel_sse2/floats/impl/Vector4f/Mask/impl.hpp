                                                /** CONSTRUCTION / DESTRUCTION **/
inline Vector4f::Mask::Mask(
    const bool& b0,
    const bool& b1,
    const bool& b2,
    const bool& b3
) {
    m_inner = _mm_castsi128_ps(
        _mm_setr_epi32(
            -int32_t(b0),
            -int32_t(b1),
            -int32_t(b2),
            -int32_t(b3)
        )
    ) ;
}

inline Vector4f::Mask::Mask(const bool& value) {
    m_inner = _mm_castsi128_ps(_mm_set1_epi32(-int32_t(value))) ;
}

inline Vector4f::Mask::Mask(const float32x4_t& vec) {
    m_inner = vec ;
}

inline Vector4f::Mask::Mask(const Vector4i::Mask& mask) {
    m_inner = _mm_castsi128_ps(mask) ;
}

inline Vector4f::Mask::Mask(const Vector4ui::Mask& mask) {
    m_inner = _mm_castsi128_ps(mask) ;
}

inline Vector4f::Mask::~Mask() {}


                                                              /*** UTILITIES ***/
inline bool Vector4f::Mask::get(const unsigned int& index) {
    return Vector4i::Mask(_mm_castps_si128(m_inner)).get(index) ;
}

inline size_t Vector4f::Mask::length() const {
    return size() ;
}

inline size_t Vector4f::Mask::size() {
    return Vector4f::size() ;
}

inline void Vector4f::Mask::print() {
    float* splitted = (float*) &m_inner ;
    std::cout << "Vector4f::Mask @"
                            << std::hex << this << std::dec << "= { "
                                << splitted[0] << ", "
                                << splitted[1] << ", "
                                << splitted[2] << ", "
                                << splitted[3]
                            << " }"
                        << std::endl ;
}


                                                              /*** OPERATORS ***/
                                                        /** AFFECT OPERATORS **/
inline Vector4f::Mask& Vector4f::Mask::operator=(const Mask& mask) {
    m_inner = mask.m_inner ;
    return *this ;
}

inline Vector4f::Mask& Vector4f::Mask::operator=(const bool& value) {
    m_inner = _mm_castsi128_ps(_mm_set1_epi32(-int32_t(value))) ;
    return *this ;
}

inline Vector4f::Mask& Vector4f::Mask::operator=(const int32x4_t& vec) {
    m_inner = _mm_castsi128_ps(vec) ;
    return *this ;
}

inline Vector4f::Mask& Vector4f::Mask::operator=(const float32x4_t& vec) {
    m_inner = vec ;
    return *this ;
}

inline Vector4f::Mask& Vector4f::Mask::operator=(const Vector4i::Mask& mask) {
    m_inner = _mm_castsi128_ps(mask) ;
    return *this ;
}

                                                            /** CAST OPERATORS **/
inline Vector4f::Mask::operator int32x4_t() const {
    return _mm_castps_si128(m_inner) ;
}

inline Vector4f::Mask::operator float32x4_t() const {
    return m_inner ;
}

inline Vector4f::Mask::operator Vector4i::Mask() const {
    return _mm_castps_si128(m_inner) ;
}

inline Vector4f::Mask::operator Vector4ui::Mask() const {
    return _mm_castps_si128(m_inner) ;
}
