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
Vector4f::Vector4f() {}

Vector4f::Vector4f(
                   const Scalar& f1,
                   const Scalar& f2,
                   const Scalar& f3,
                   const Scalar& f4
                  ) {
    m_inner = _mm_setr_ps(f1, f2, f3, f4) ;
}

Vector4f::Vector4f(const Scalar& value) {
    m_inner = _mm_set1_ps(value) ;
}

Vector4f::Vector4f(const float32x4_t& vec) {
    m_inner = vec ;
}

Vector4f::~Vector4f() {}


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

inline void Vector4f::abs() {
    // Mask to remove the sign bit
    const float32x4_t MaskForNoSign = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)) ;
    m_inner = _mm_and_ps(m_inner, MaskForNoSign) ;
}

inline void Vector4f::squared() {
    m_inner = _mm_mul_ps(m_inner, m_inner) ;
}

template <int i0, int i1, int i2, int i3>
void Vector4f::permute() {
    ABORT_CONDITION((i0 <= 3), "Bad value. Expected i0 <= 3") ;
    ABORT_CONDITION((i1 <= 3), "Bad value. Expected i1 <= 3") ;
    ABORT_CONDITION((i2 <= 3), "Bad value. Expected i2 <= 3") ;
    ABORT_CONDITION((i3 <= 3), "Bad value. Expected i3 <= 3") ;

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
            // Zero all values.
            m_inner = _mm_setzero_ps() ;
        }
        else {
            const int32x4_t MaskZeroPositions = Vector4i::constant<
                                                                 -int(i0 > -1),
                                                                 -int(i1 > -1),
                                                                 -int(i2 > -1),
                                                                 -int(i3 > -1)
                                                                >() ;

            m_inner = _mm_and_ps(m_inner,_mm_castsi128_ps(MaskZeroPositions)) ;
        }
    }
    else if (NeedShuffle and !DoZero) {
        // Only shuffle the values in the vector.
        m_inner = _mm_shuffle_ps(
                                 m_inner,
                                 m_inner,
                                 ((i0) | (i1 << 2) | (i2 << 4) | (i3 << 6))
                                ) ;
    }
    else if (((i0 & i1) < 0) && ((i2 | i3) >= 0)) {
        // Zero on lower elements, shuffle higher ones.
        m_inner = _mm_shuffle_ps(_mm_setzero_ps(), m_inner, (i2 << 4) | (i3 <<6));
    }
    else if ((i0 | i1) >= 0 && (i2 & i3) < 0) {
        // Zero on higher elements, shuffle lower ones.
        m_inner = _mm_shuffle_ps(m_inner, _mm_setzero_ps(), (i0 | (i1 << 2))) ;
    }
    else {
        #if defined (USE_INTEL_SSSE3)
            // With SSSE3 we can do both with the PSHUFB instruction
            const int j0 = i0 << 2 ;
            const int j1 = i1 << 2 ;
            const int j2 = i2 << 2 ;
            const int j3 = i3 << 2 ;
            __m128i MaskZeroPositions = Vector4i::constant <
                                                            i0 < 0 ? -1 : j0 | (j0+1)<<8 | (j0+2)<<16 | (j0+3) << 24,
                                                            i1 < 0 ? -1 : j1 | (j1+1)<<8 | (j1+2)<<16 | (j1+3) << 24,
                                                            i2 < 0 ? -1 : j2 | (j2+1)<<8 | (j2+2)<<16 | (j2+3) << 24,
                                                            i3 < 0 ? -1 : j3 | (j3+1)<<8 | (j3+2)<<16 | (j3+3) << 24
                                                           > () ;
            m_inner = _mm_castsi128_ps(_mm_shuffle_epi8(_mm_castps_si128(a),mask2)) ;
        #else
            __m128 tmp = _mm_shuffle_ps(m_inner, m_inner, ((i0) | (i1 << 2) | (i2 << 4) | (i3 << 6))) ;
            __m128i MaskZeroPositions = Vector4i::constant<
                                                           -int(i0 > -1),
                                                           -int(i1 > -1),
                                                           -int(i2 > -1),
                                                           -int(i3 > -1)
                                                          >() ;
            m_inner = _mm_and_ps(tmp,_mm_castsi128_ps(MaskZeroPositions)) ;
        #endif
    }
}

template <bool i0, bool i1, bool i2, bool i3>
inline void Vector4f::changeSign() {
    if ((i0 | i1 | i2 | i3) == true) {
        // Mask to set flip the bit for negative sign (on Scalar values).
        const __m128i MaskNegative = Vector4i::constant<
                                                        i0 ? 0x80000000 : 0,
                                                        i1 ? 0x80000000 : 0,
                                                        i2 ? 0x80000000 : 0,
                                                        i3 ? 0x80000000 : 0
                                                       >() ;

        m_inner = _mm_xor_ps(m_inner, _mm_castsi128_ps(MaskNegative)) ;
    }
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
    ABORT_CONDITION((i0 <= 3), "Bad value. Expected i0 <= 3") ;
    ABORT_CONDITION((i1 <= 3), "Bad value. Expected i1 <= 3") ;
    ABORT_CONDITION((i2 <= 3), "Bad value. Expected i2 <= 3") ;
    ABORT_CONDITION((i3 <= 3), "Bad value. Expected i3 <= 3") ;

    output = _mm_shuffle_ps(
                            input,
                            input,
                            ((i0) | (i1 << 2) | (i2 << 4) | (i3 << 6))
                           ) ;

    return output ;
}

inline Vector4f Vector4f::min(const Vector4f& a, const Vector4f& b) {
    return _mm_min_ps(a, b) ;
}

inline Vector4f Vector4f::max(const Vector4f& a, const Vector4f& b) {
    return _mm_max_ps(a, b) ;
}

inline Vector4f Vector4f::abs(const Vector4f& vec) {
    // Mask to remove the sign bit
    const float32x4_t MASK = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)) ;
    return Vector4f(_mm_and_ps(vec.m_inner, MASK)) ;
}

inline Vector4f Vector4f::sqrt(const Vector4f& vec) {
    return _mm_sqrt_ps(vec) ;
}

inline Vector4f Vector4f::square(const Vector4f& vec) {
    return Vector4f(_mm_mul_ps(vec.m_inner, vec.m_inner)) ;
}

inline Scalar Vector4f::dot(const Vector4f& a, const Vector4f& b) {
    Vector4f product = a * b ;
    return product.horizontalAdd() ;
}

inline Vector4f Vector4f::fast_recriprocal(const Vector4f& vec) {
    return _mm_rcp_ps(vec) ;
}

inline Vector4f Vector4f::fast_rsqrt(const Vector4f& vec) {
    return _mm_rsqrt_ps(vec) ;
}

inline Vector4f Vector4f::fast_sqrt(const Vector4f& vec) {
    return _mm_rcp_ps(_mm_rsqrt_ps(vec)) ;
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
    return _mm_castsi128_ps(extendedSignBit) ;
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
    Vector4i extractedFraction = _mm_andnot_si128(MaskExponent, removedSignBit) ;
    // NaN = Exponent is null while fraction is not.
    Vector4i::Mask resultMask = (extractedExponent == MaskExponent) & (extractedFraction != 0) ;
    return resultMask ;
}

inline void Vector4f::set(const Array4f& array) {
    m_inner = _mm_loadu_ps(array.data()) ;
}

inline void Vector4f::set(const AlignedArray4f& array) {
    m_inner = _mm_load_ps(array.data()) ;
}

inline void Vector4f::get(Array4f& array) const {
    float* data = array.data() ;
    _mm_storeu_ps(data, m_inner) ;
}

inline void Vector4f::get(AlignedArray4f& array) const {
    float* data = array.data() ;
    _mm_store_ps(data, m_inner) ;
}

inline size_t Vector4f::length() const {
    return Array4f::size() ;
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

inline void Vector4f::setControlWord(uint32_t csr) {
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

inline Vector4f& Vector4f::operator=(const Scalar& value) {
    m_inner = _mm_set1_ps(value) ;
    return *this ;
}

inline Vector4f& Vector4f::operator=(const float32x4_t& vec) {
    m_inner = vec ;
    return *this ;
}

inline Vector4f& Vector4f::operator=(const Vector4i& vec4) {
    m_inner = _mm_cvtepi32_ps(vec4) ;
    return *this ;
}

inline Vector4f& Vector4f::operator=(const Vector4ui& vec4) {
    m_inner = _mm_cvtepi32_ps(vec4) ;
    return *this ;
}

                                          				  /** CAST OPERATORS **/
inline Vector4f::operator float32x4_t() const {
    return m_inner ;
}

inline Vector4f::operator Vector4i() const {
    return Vector4i(m_inner) ;
}

inline Vector4f::operator Vector4ui() const {
    return Vector4ui(m_inner) ;
}
