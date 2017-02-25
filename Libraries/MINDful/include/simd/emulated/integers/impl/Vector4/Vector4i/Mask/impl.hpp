                                                /** CONSTRUCTION / DESTRUCTION **/
Vector4i::Mask::Mask() {}

Vector4i::Mask::Mask(
    const bool& b0,
    const bool& b1,
    const bool& b2,
    const bool& b3
) {
     m_inner[0] = b0 ;
     m_inner[1] = b1 ;
     m_inner[2] = b2 ;
     m_inner[3] = b3 ;
}

Vector4i::Mask::Mask(const bool& value) {
    for (unsigned int index = 0 ; index < size() ; ++index) {
        m_inner[index] = value ;
    }
}

Vector4i::Mask::Mask(const int32x4_t& vec) {
    std::copy(vec.begin(), vec.end(), m_inner.begin()) ;
}

Vector4i::Mask::~Mask() {}


                                                              /*** UTILITIES ***/
inline void Vector4i::Mask::get(Array4i& array) {
    int32_t* data = array.data() ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        data[index] = m_inner[index] ;
    }
}

inline bool Vector4i::Mask::get(const unsigned int& index) {
    return m_inner[index] ;
}

inline size_t Vector4i::Mask::length() const {
    return size() ;
}

inline size_t Vector4i::Mask::size() {
    return 4 ;
}


                                                              /*** OPERATORS ***/
                                                        /** AFFECT OPERATORS **/
inline typename Vector4i::Mask& Vector4i::Mask::operator=(const Mask& mask) {
    auto other = mask.m_inner ;
    std::copy(other.begin(), other.end(), m_inner.begin()) ;
    return *this ;
}

inline typename Vector4i::Mask& Vector4i::Mask::operator=(const bool& value) {
    for (unsigned int index = 0 ; index < size() ; ++index) {
        m_inner[index] = value ;
    }
    return *this ;
}

inline typename Vector4i::Mask& Vector4i::Mask::operator=(const int32x4_t& vec) {
    std::copy(vec.begin(), vec.end(), m_inner.begin()) ;
    return *this ;
}

inline typename Vector4i::Mask& Vector4i::Mask::operator=(const float32x4_t& vec) {
    std::copy(vec.begin(), vec.end(), m_inner.begin()) ;
    return *this ;
}

                                                            /** CAST OPERATORS **/
inline Vector4i::Mask::operator int32x4_t() const {
    return m_inner ;
}

inline Vector4i::Mask::operator int32x4_t*() const {
    return (int32x4_t*) &m_inner ;
}

inline Vector4i::Mask::operator float32x4_t() {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < size() ; ++index) {
        result[index] = m_inner[index] ;
    }
    return result ;
}
