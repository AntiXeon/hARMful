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
template <uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3>
inline uint32x4_t Vector4ui::constant() {
    static const union {
        int integer[4] ;
        uint32x4_t vector ;
    } u = {{i0, i1, i2, i3}} ;
    return u.vector ;
}

inline Vector4ui Vector4ui::min(const Vector4ui& a, const Vector4ui& b) {
    #if defined(USE_INTEL_SSE4_1)
        return _mm_min_epu32(a, b) ;
    #else
        int32x4_t greater = _mm_cmpgt_epi32(a, b) ;
        return Vector4::selection(greater, b, a) ;
    #endif
}

inline Vector4ui Vector4ui::max(const Vector4ui& a, const Vector4ui& b) {
    #if defined(USE_INTEL_SSE4_1)
        return _mm_max_epu32(a, b) ;
    #else
        int32x4_t greater = _mm_cmpgt_epi32(a, b) ;
        return Vector4::selection(greater, a, b) ;
    #endif
}

inline void Vector4ui::print() {
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


//inline static Vector4ui operator<<(const Vector4ui& vec, int32_t bits) {
//    return _mm_sll_epi32(vec,_mm_cvtsi32_si128(bits)) ;
//}

//inline static Vector4ui& operator<<=(Vector4ui& vec, int32_t bits) {
//    vec = vec << bits ;
//    return vec ;
//}

//inline static Vector4ui operator>>(const Vector4ui& vec, int32_t bits) {
//    return _mm_sra_epi32(vec,_mm_cvtsi32_si128(bits)) ;
//}

//inline static Vector4ui& operator>>=(Vector4ui& vec, int32_t bits) {
//    vec = vec << bits ;
//    return vec ;
//}

//inline static Vector4ui operator==(const Vector4ui& a, const Vector4ui&b) {
//    return _mm_cmpeq_epi32(a, b) ;
//}
