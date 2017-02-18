                              				  /** CONSTRUCTION / DESTRUCTION **/
template <typename Type>
Vector4<Type>::Mask::Mask() {}

template <typename Type>
Vector4<Type>::Mask::Mask(
    const bool& b0,
    const bool& b1,
    const bool& b2,
    const bool& b3
) {
     m_inner = _mm_setr_epi32(b0, b1, b2, b3) ;
}

template <typename Type>
Vector4<Type>::Mask::Mask(const bool& value) {
    m_inner = _mm_set1_epi32(value) ;
}

template <typename Type>
Vector4<Type>::Mask::Mask(const int32x4_t& vec) {
    m_inner = vec ;
}

template <typename Type>
Vector4<Type>::Mask::~Mask() {}


                                             				 /*** UTILITIES ***/
template <typename Type>
inline void Vector4<Type>::Mask::get(AlignedArray4i& array) {
    int32_t* data = array.data() ;
    _mm_store_si128((__m128i*) data, m_inner) ;
}

template <typename Type>
inline bool Vector4<Type>::Mask::get(const unsigned int& index) {
    AlignedArray4i tmp ;
    get(tmp) ;
    return tmp[index] ;
}

template <typename Type>
inline size_t Vector4<Type>::Mask::length() const {
    return size() ;
}

template <typename Type>
inline size_t Vector4<Type>::Mask::size() {
    return 4 ;
}


                                             				 /*** OPERATORS ***/
                                        				/** AFFECT OPERATORS **/
template <typename Type>
inline typename Vector4<Type>::Mask& Vector4<Type>::Mask::operator=(const Mask& mask) {
    m_inner = mask.m_inner ;
    return *this ;
}

template <typename Type>
inline typename Vector4<Type>::Mask& Vector4<Type>::Mask::operator=(const bool& value) {
    m_inner = _mm_set1_epi32(-int32_t(value)) ;
    return *this ;
}

template <typename Type>
inline typename Vector4<Type>::Mask& Vector4<Type>::Mask::operator=(const int32x4_t& vec) {
    m_inner = vec ;
    return *this ;
}

template <typename Type>
inline typename Vector4<Type>::Mask& Vector4<Type>::Mask::operator=(const float32x4_t& vec) {
    m_inner = _mm_castps_si128(vec) ;
    return *this ;
}

                                          				  /** CAST OPERATORS **/
template <typename Type>
inline Vector4<Type>::Mask::operator int32x4_t() const {
    return m_inner ;
}

template <typename Type>
inline Vector4<Type>::Mask::operator float32x4_t() const {
    return _mm_castsi128_ps(m_inner) ;
}
