inline float32x4_t Vector4f::selection(
    const float32x4_t& selector,
    const float32x4_t& a,
    const float32x4_t& b
) {
    #if defined (USE_INTEL_SSE4_1)
        return _mm_blendv_ps(b, a, selector) ;
    #else
        return _mm_or_ps(
            _mm_and_ps(selector, a),
            _mm_andnot_ps(selector, b)
        ) ;
    #endif
}


                                              /** CONSTRUCTION / DESTRUCTION **/
inline Vector4f::Vector4f() {}

inline Vector4f::Vector4f(
    const Scalar f1,
    const Scalar f2,
    const Scalar f3,
    const Scalar f4
) {
    m_inner = _mm_setr_ps(f1, f2, f3, f4) ;
}

inline Vector4f::Vector4f(const Scalar value) {
    m_inner = _mm_set1_ps(value) ;
}

inline Vector4f::Vector4f(const float32x4_t& vec) {
    m_inner = vec ;
}

inline Vector4f::~Vector4f() {}


                                                              /*** UTILITIES ***/
inline Scalar Vector4f::horizontalAdd() {
    // The goal of this function is to put the sum of vector elements in the
    // lower element (ie. first position) of the result, and finally return the
    // contained value in this lower element.
    #if defined (USE_INTEL_SSE3)
        // Compute sum of all elements in vector.
        // Notice that _mm_hadd_ps() function only sum adjacent positions
        // (indices 0+1 ; 2+3). It is so necessary to sum twice the vector to
        // sum the four positions.
        float32x4_t sum1 = _mm_hadd_ps(m_inner, m_inner) ;
        // Sum twice.
        float32x4_t sum2 = _mm_hadd_ps(sum1, sum1) ;
        // Get the lower element from the inner vector, containing the sum of
        // all elements.
        return _mm_cvtss_f32(sum2) ;
    #else
        // Swap high elements to low ones in tmp1.
        float32x4_t tmp1 = _mm_movehl_ps(m_inner, m_inner) ;
        // Then, sum inner to tmp1.
        float32x4_t tmp2 = _mm_add_ps(m_inner, tmp1) ;
        float32x4_t tmp3 = _mm_shuffle_ps(tmp2, tmp2, 1) ;
        float32x4_t tmp4 = _mm_add_ps(tmp2, tmp3) ;
        return _mm_cvtss_f32(tmp4) ;
    #endif
}

inline Scalar Vector4f::horizontalSub() {
    // The goal of this function is to put the difference of vector
    // elements in the lower element (ie. first position) of the result,
    // and finally return the contained value in this lower element.
    #if defined (USE_INTEL_SSE3)
        // Compute difference of all elements in vector.
        // Notice that _mm_hsub_ps() function only sub adjacent positions
        // (indices 0+1 ; 2+3). It is so necessary to sub twice the
        // vector to sub the four positions.
        float32x4_t sub1 = _mm_hsub_ps(m_inner, m_inner) ;
        // Sum twice.
        float32x4_t sub2 = _mm_hsub_ps(sub1, sub1) ;
        // Get the lower element from the inner vector, containing the sum of
        // all elements.
        return _mm_cvtss_f32(sub2) ;
    #else
        // Swap high elements to low ones in tmp1.
        float32x4_t tmp1 = _mm_movehl_ps(m_inner, m_inner) ;
        // Then, sum inner to tmp1.
        float32x4_t tmp2 = _mm_sub_ps(m_inner, tmp1) ;
        float32x4_t tmp3 = _mm_shuffle_ps(tmp2, tmp2, 1) ;
        float32x4_t tmp4 = _mm_sub_ps(tmp2, tmp3) ;
        return _mm_cvtss_f32(tmp4) ;
    #endif
}

inline void Vector4f::abs() {
    // Mask to remove the sign bit
    const float32x4_t MaskForNoSign = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)) ;
    m_inner = _mm_and_ps(m_inner, MaskForNoSign) ;
}

inline void Vector4f::squared() {
    m_inner = _mm_mul_ps(m_inner, m_inner) ;
}


                                                  /** CONDITIONAL ARITHMETIC **/
inline void Vector4f::addIf(const Vector4f::Mask& mask, const Vector4f& add) {
    *this += (add & mask) ;
}

inline void Vector4f::mulIf(const Vector4f::Mask& mask, const Vector4f& mul) {
    *this *= select(mask, mul, 1.f) ;
}

inline Scalar Vector4f::dot(const Vector4f& other) const {
    return dot(*this, other) ;
}

inline Vector4f Vector4f::cross(const Vector4f& other) const {
    return cross(*this, other) ;
}

inline Scalar Vector4f::norm() const {
    Vector4f norm2 = Vector4f(dot(*this)) ;
    float32x4_t norm = _mm_sqrt_ps((float32x4_t) norm2) ;
    return norm[0] ;
}


                                                        /** STATIC FUNCTIONS **/
inline Vector4f Vector4f::select(
    const Vector4f::Mask& selector,
    const Vector4f& a,
    const Vector4f& b
) {
    return selection(
        (float32x4_t) selector,
        (float32x4_t) a,
        (float32x4_t) b
    ) ;
}

inline Vector4f Vector4f::min(const Vector4f& a, const Vector4f& b) {
    return _mm_min_ps((float32x4_t) a, (float32x4_t) b) ;
}

inline Vector4f Vector4f::max(const Vector4f& a, const Vector4f& b) {
    return _mm_max_ps((float32x4_t) a, (float32x4_t) b) ;
}

inline Vector4f Vector4f::abs(const Vector4f& vec) {
    // Mask to remove the sign bit
    const float32x4_t MASK = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)) ;
    return Vector4f(_mm_and_ps(vec.m_inner, MASK)) ;
}

inline Vector4f Vector4f::sqrt(const Vector4f& vec) {
    return _mm_sqrt_ps((float32x4_t) vec) ;
}

inline Vector4f Vector4f::square(const Vector4f& vec) {
    return Vector4f(_mm_mul_ps(vec.m_inner, vec.m_inner)) ;
}

inline Scalar Vector4f::dot(const Vector4f& a, const Vector4f& b) {
    Vector4f product = a * b ;
    return product.horizontalAdd() ;
}

inline Vector4f Vector4f::cross(const Vector4f& a, const Vector4f& b) {
    // The fourth component is not used (the cross product is not defined in
    // R^4).
    float32x4_t firstA = _mm_shuffle_ps(a.m_inner, a.m_inner, _MM_SHUFFLE(0,2,1,3)) ;
    float32x4_t firstB = _mm_shuffle_ps(b.m_inner, b.m_inner, _MM_SHUFFLE(1,0,2,3)) ;
    float32x4_t first = _mm_mul_ps(firstA, firstB) ;

    float32x4_t secondA = _mm_shuffle_ps(a.m_inner, a.m_inner, _MM_SHUFFLE(1,0,2,3)) ;
    float32x4_t secondB = _mm_shuffle_ps(b.m_inner, b.m_inner, _MM_SHUFFLE(0,2,1,3)) ;
    float32x4_t second = _mm_mul_ps(secondA, secondB) ;

    return _mm_sub_ps((float32x4_t) first, (float32x4_t) second) ;
}

inline Vector4f Vector4f::fast_recriprocal(const Vector4f& vec) {
    return _mm_rcp_ps((float32x4_t) vec) ;
}

inline Vector4f Vector4f::fast_rsqrt(const Vector4f& vec) {
    return _mm_rsqrt_ps((float32x4_t) vec) ;
}

inline Vector4f Vector4f::fast_sqrt(const Vector4f& vec) {
    return _mm_rcp_ps(_mm_rsqrt_ps((float32x4_t) vec)) ;
}


                                                        /** FUSED OPERATIONS **/
inline Vector4f Vector4f::mul_add(
    const Vector4f& mula,
    const Vector4f& mulb,
    const Vector4f& add
) {
    #if defined (USE_FMA4)
        return _mm_macc_ps(mula, mulb, add) ;
    #elif defined (USE_FMA)
        return _mm_fmadd_ps(mula, mulb, add) ;
    #else
        return mula * mulb + add ;
    #endif
}

inline Vector4f Vector4f::mul_sub(
    const Vector4f& mula,
    const Vector4f& mulb,
    const Vector4f& sub
) {
    #if defined (USE_FMA4)
        return _mm_msub_ps(mula, mulb, sub) ;
    #elif defined (USE_FMA)
        return _mm_fnmadd_ps(mula, mulb, sub) ;
    #else
        return mula * mulb - sub ;
    #endif
}

inline Vector4f Vector4f::sub_mul(
    const Vector4f& sub,
    const Vector4f& mula,
    const Vector4f& mulb
) {
    #if defined (USE_FMA4)
        return _mm_nmacc_ps(mula, mulb, sub) ;
    #elif defined (USE_FMA)
        return _mm_fmsub_ps(mula, mulb, sub) ;
    #else
        return sub - mula * mulb ;
    #endif
}

inline void Vector4f::transposeMatrix(
    Vector4f& row1,
    Vector4f& row2,
    Vector4f& row3,
    Vector4f& row4
) {
    float32x4_t row1_t = (float32x4_t) row1 ;
    float32x4_t row2_t = (float32x4_t) row2 ;
    float32x4_t row3_t = (float32x4_t) row3 ;
    float32x4_t row4_t = (float32x4_t) row4 ;
    _MM_TRANSPOSE4_PS(row1_t, row2_t, row3_t, row4_t) ;
    row1 = row1_t ;
    row2 = row2_t ;
    row3 = row3_t ;
    row4 = row4_t ;
}


                                             /*** GETTERS / SETTERS ***/
inline Vector4f::Mask Vector4f::isNegative() {
    // Float structure :
    // [ S | EEEEEEEE | FFFFFFFFFFFFFFFFFFFFFFF ]
    // -> 1 bit for Sign (S)
    // -> 8 bits for Exponent (E)
    // -> 23 bits for Fraction (F)
    Vector4i converted = _mm_castps_si128(m_inner) ;
    Vector4i extendedSignBit = (converted >> 31) ;
    // Convert the extended sign vector to a Mask (containing either 0x00000000
    // or 0xFFFFFFFF).
    return _mm_castsi128_ps((__m128i) extendedSignBit) ;
}

inline Vector4f::Mask Vector4f::isInfinite() {
    // Float structure :
    // [ S | EEEEEEEE | FFFFFFFFFFFFFFFFFFFFFFF ]
    // -> 1 bit for Sign (S)
    // -> 8 bits for Exponent (E)
    // -> 23 bits for Fraction (F)
    const int MaskInfiniteExponent = 0xFF000000 ;

    Vector4i converted = _mm_castps_si128(m_inner) ;
    Vector4i removedSignBit = converted << 1 ;
    return _mm_castsi128_ps(removedSignBit == Vector4i(MaskInfiniteExponent)) ;
}

inline Vector4f::Mask Vector4f::isNaN() {
    // Float structure :
    // [ S | EEEEEEEE | FFFFFFFFFFFFFFFFFFFFFFF ]
    // -> 1 bit for Sign (S)
    // -> 8 bits for Exponent (E)
    // -> 23 bits for Fraction (F)
    const Vector4i MaskExponent = 0xFF000000 ;

    Vector4i converted = _mm_castps_si128(m_inner) ;
    Vector4i removedSignBit = converted << 1 ;
    Vector4i extractedExponent = removedSignBit & MaskExponent ;
    Vector4i extractedFraction = _mm_andnot_si128((int32x4_t) MaskExponent, (int32x4_t) removedSignBit) ;
    // NaN = Exponent is null while fraction is not.
    Vector4i::Mask isExponentOfNaN = extractedExponent == MaskExponent ;
    Vector4i::Mask resultMask = (Vector4i::Mask) (isExponentOfNaN & (extractedFraction != 0)) ;
    return resultMask ;
}

#ifdef ALIGNED_ARRAY
    inline void Vector4f::set(const AlignedArray4f& array) {
        m_inner = _mm_load_ps(array.data()) ;
    }

    inline void Vector4f::get(AlignedArray4f& array) const {
        float* data = array.data() ;
        _mm_store_ps(data, m_inner) ;
    }
#else
    inline void Vector4f::set(const Array4f& array) {
        m_inner = _mm_loadu_ps(array.data()) ;
    }

    inline void Vector4f::get(Array4f& array) const {
        float* data = array.data() ;
        _mm_storeu_ps(data, m_inner) ;
    }
#endif

inline size_t Vector4f::length() const {
    return Vector4f::size() ;
}

inline size_t Vector4f::size() {
    return 4 ;
}

inline void Vector4f::print() {
    float* splitted = (float*) &m_inner ;
    std::cout << "Vector4f @"
                            << std::hex << this << std::dec << "= { "
                                << splitted[0] << ", "
                                << splitted[1] << ", "
                                << splitted[2] << ", "
                                << splitted[3]
                            << " }"
                        << std::endl ;
}

                                                         /*** MXCSR ***/
inline uint32_t Vector4f::getControlWord() {
    return _mm_getcsr() ;
}

inline void Vector4f::setControlWord(const uint32_t csr) {
    _mm_setcsr(csr) ;
}

inline void Vector4f::noSubnormals() {
     uint32_t tmp = getControlWord() ;
     tmp |= (1 << 6) | (1 << 15) ;
     setControlWord(tmp) ;
}

inline void Vector4f::resetControlWord() {
    setControlWord(0x1F80) ;
}


                                                     /*** OPERATORS ***/
                                                /** AFFECT OPERATORS **/
inline Vector4f& Vector4f::operator=(const Vector4f& vec4) {
    m_inner = vec4.m_inner ;
    return *this ;
}

inline Vector4f& Vector4f::operator=(const Scalar value) {
    m_inner = _mm_set1_ps(value) ;
    return *this ;
}

inline Vector4f& Vector4f::operator=(const float32x4_t& vec) {
    m_inner = vec ;
    return *this ;
}

inline Vector4f& Vector4f::operator=(const Vector4i& vec4) {
    m_inner = _mm_cvtepi32_ps((__m128i) vec4) ;
    return *this ;
}

inline Vector4f& Vector4f::operator=(const Vector4ui& vec4) {
    m_inner = _mm_cvtepi32_ps((__m128i) vec4) ;
    return *this ;
}

                                                  /** CAST OPERATORS **/
inline Vector4f::operator float32x4_t() const {
    return m_inner ;
}

inline Vector4f::operator float*() const {
    return ((float*) &m_inner) ;
}

inline Vector4f::operator Vector4i() const {
    return Vector4i(m_inner) ;
}

inline Vector4f::operator Vector4ui() const {
    return Vector4ui(m_inner) ;
}
