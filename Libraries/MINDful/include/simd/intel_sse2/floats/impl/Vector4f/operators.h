                                                                /** ADDITION **/
/**
 * @brief   Add two Vector4f, each element of a Vector4f to its corresponding
 *          one in the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4f operator+(const Vector4f& a, const Vector4f& b) {
    return _mm_add_ps(a, b) ;
}

/**
 * @brief   Add a Vector4f to a float. The float is converted to a Vector4f
 *          where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4f operator+(const Vector4f& a, const float& b) {
    return a + Vector4f(b) ;
}

/**
 * @brief   Add a Vector4f to a float. The float is converted to a Vector4f
 *          where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4f operator+(const float& a, const Vector4f& b) {
    return Vector4f(a) + b ;
}

/**
 * @brief   Add a Vector4f to a float. The float is converted to a Vector4f
 *          where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition stored in the first operand.
 */
static inline Vector4f& operator+=(Vector4f& a, const Vector4f& b) {
    a = a + b ;
    return a ;
}

/**
 * @brief   Add two Vector4f, each element of a Vector4f to its corresponding
 *          one in the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition stored in the first operand.
 */
static inline Vector4f& operator+=(Vector4f& a, const float& b) {
    a = a + Vector4f(b) ;
    return a ;
}


                                                               /** INCREMENT **/
/**
 * @brief   Postfix incrementation.
 * @param   a   Vector4f for which each component is increased of +1.
 * @warning Quite slower than prefix incrementation.
 */
static inline Vector4f operator++(Vector4f& a, int) {
    Vector4f previous = a ;
    a = a + 1.f ;
    return previous ;
}

/**
 * @brief   Prefix incrementation.
 * @param   a   Vector4f for which each component is increased of +1.

 */
static inline Vector4f& operator++(Vector4f& a) {
    a = a + 1.f ;
    return a ;
}


                                                              /** DIFFERENCE **/
/**
 * @brief   Substract two Vector4f, each element of a Vector4f to its
 *          corresponding one in the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4f operator-(const Vector4f& a, const Vector4f& b) {
    return _mm_sub_ps(a, b) ;
}

/**
 * @brief   Substract a Vector4f to a float. The float is converted to a
 *          Vector4f where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4f operator-(const Vector4f& a, const float& b) {
    return a - Vector4f(b) ;
}

/**
 * @brief   Substract a Vector4f to a float. The float is converted to a
 *          Vector4f where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4f operator-(const float& a, const Vector4f& b) {
    return Vector4f(a) - b ;
}

/**
 * @brief   Substract two Vector4f, each element of a Vector4f to its
 *          corresponding one in the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference stored in the first operand.
 */
static inline Vector4f& operator-=(Vector4f& a, const Vector4f& b) {
    a = a - b ;
    return a ;
}

/**
 * @brief   Substract a Vector4f to a float. The float is converted to a
 *          Vector4f where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference stored in the first operand.
 */
static inline Vector4f& operator-=(Vector4f& a, const float& b) {
    a = a - Vector4f(b) ;
    return a ;
}


                                                                  /** NEGATE **/
static inline Vector4f operator-(const Vector4f& a) {
    const int MaskNegateBit = 0x80000000 ;
    return _mm_xor_ps(a, _mm_castsi128_ps(_mm_set1_epi32(MaskNegateBit))) ;
}


                                                               /** DECREMENT **/
/**
 * @brief   Postfix decrementation.
 * @param   a   Vector4f for which each component is decreased of -1.
 * @warning Quite slower than prefix decrementation.
 */
static inline Vector4f operator--(Vector4f& a, int) {
    Vector4f previous = a ;
    a = a - 1.f ;
    return previous ;
}

/**
 * @brief   Prefix decrementation.
 * @param   a   Vector4f for which each component is decreased of -1.

 */
static inline Vector4f& operator--(Vector4f& a) {
    a = a - 1.f ;
    return a ;
}


                                                                /** MULTIPLY **/
/**
 * @brief   Multiply two Vector4f, each element of a Vector4f to its
 *          corresponding one in the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4f operator*(const Vector4f& a, const Vector4f& b) {
    return _mm_mul_ps(a, b) ;
}

/**
 * @brief   Multiply a Vector4f to a float. The float is converted to a
 *          Vector4f where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4f operator*(const Vector4f& a, const float& b) {
    return a * Vector4f(b) ;
}

/**
 * @brief   Multiply a Vector4f to a float. The float is converted to a
 *          Vector4f where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4f operator*(const float& a, const Vector4f& b) {
    return Vector4f(a) * b ;
}

/**
 * @brief   Multiply two Vector4f, each element of a Vector4f to its
 *          corresponding one in the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product stored in the first operand.
 */
static inline Vector4f& operator*=(Vector4f& a, const Vector4f& b) {
    a = a * b ;
    return a ;
}

/**
 * @brief   Multiply a Vector4f to a float. The float is converted to a
 *          Vector4f where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product stored in the first operand.
 */
static inline Vector4f& operator*=(Vector4f& a, const float& b) {
    a = a * Vector4f(b) ;
    return a ;
}


                                                                  /** DIVIDE **/
/**
 * @brief   Divide two Vector4f, each element of a Vector4f to its
 *          corresponding one in the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the division.
 */
static inline Vector4f operator/(const Vector4f& a, const Vector4f& b) {
    return _mm_div_ps(a, b) ;
}

/**
 * @brief   Divide a Vector4f to a float. The float is converted to a
 *          Vector4f where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the division.
 */
static inline Vector4f operator/(const Vector4f& a, const float& b) {
    return a / Vector4f(b) ;
}

/**
 * @brief   Divide a Vector4f to a float. The float is converted to a
 *          Vector4f where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the division.
 */
static inline Vector4f operator/(const float& a, const Vector4f& b) {
    return Vector4f(a) / b ;
}

/**
 * @brief   Divide two Vector4f, each element of a Vector4f to its
 *          corresponding one in the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the division stored in the first operand.
 */
static inline Vector4f& operator/=(Vector4f& a, const Vector4f& b) {
    a = a / b ;
    return a ;
}

/**
 * @brief   Divide a Vector4f to a float. The float is converted to a
 *          Vector4f where all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the division stored in the first operand.
 */
static inline Vector4f& operator/=(Vector4f& a, const float& b) {
    a = a / Vector4f(b) ;
    return a ;
}

                                                  /*** COMPARISON OPERATORS ***/
/**
 * @brief   Check if two Vector4f objects contain the same values.
 *          The positions for which the values are equal are set to TRUE.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values are
 *          equal, FALSE for different values in the Vector4f parameters.
 */
static inline Vector4f::Mask operator==(const Vector4f& a, const Vector4f& b) {
    return _mm_cmpeq_ps(a, b) ;
}

/**
 * @brief   Check if two Vector4f objects contain the different values.
 *          The positions for which the values are different are set to TRUE.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values are
 *          different, FALSE for equal values in the Vector4f parameters.
 */
static inline Vector4f::Mask operator!=(const Vector4f& a, const Vector4f& b) {
    return _mm_cmpneq_ps(a, b) ;
}

/**
 * @brief   Check positions <i>p</i> in Vector4f objects at which
 *          a[<i>p</i>] < b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values of
 *          @a a are lower than values of @a b.
 */
static inline Vector4f::Mask operator<(const Vector4f& a, const Vector4f& b) {
    return _mm_cmplt_ps(a, b) ;
}

/**
 * @brief   Check positions <i>p</i> in Vector4f objects at which
 *          @a a[<i>p</i>] <= @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values of
 *          @a a are lower or equal to values of @a b.
 */
static inline Vector4f::Mask operator<=(const Vector4f& a, const Vector4f& b) {
    return _mm_cmple_ps(a, b) ;
}

/**
 * @brief   Check positions <i>p</i> in Vector4f objects at which
 *          a[<i>p</i>] > b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values of
 *          @a a are greater than values of @a b.
 */
static inline Vector4f::Mask operator>(const Vector4f& a, const Vector4f& b) {
    return b < a ;
}

/**
 * @brief   Check positions <i>p</i> in Vector4f objects at which
 *          @a a[<i>p</i>] >= @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values of
 *          @a a are greater or equal to values of @a b.
 */
static inline Vector4f::Mask operator>=(const Vector4f& a, const Vector4f& b) {
    return b <= a ;
}


                                             /*** BITWISE LOGICAL OPERATORS ***/
                                                                     /** AND **/
/**
 * @brief   Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4f operator&(const Vector4f& a, const Vector4f& b) {
    return _mm_and_ps(a, b) ;
}

/**
 * @brief   Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4f& operator&=(Vector4f& a, const Vector4f& b) {
    a = a & b ;
    return a ;
}

/**
 * @brief   Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4f operator&(const Vector4f& a, const Vector4f::Mask& b) {
    return _mm_and_ps(a, b) ;
}

/**
 * @brief   Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4f& operator&=(Vector4f& a, const Vector4f::Mask& b) {
    a = a & b ;
    return a ;
}

/**
 * @brief   Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4f operator&(const Vector4f::Mask& a, const Vector4f& b) {
    return _mm_and_ps(a, b) ;
}


                                                                      /** OR **/
/**
 * @brief   Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4f operator|(const Vector4f& a, const Vector4f& b) {
    return _mm_or_ps(a, b) ;
}

/**
 * @brief   Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4f& operator|=(Vector4f& a, const Vector4f& b) {
    a = a | b ;
    return a ;
}

/**
 * @brief   Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4f operator|(const Vector4f& a, const Vector4f::Mask& b) {
    return _mm_or_ps(a, b) ;
}

/**
 * @brief   Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4f& operator|=(Vector4f& a, const Vector4f::Mask& b) {
    a = a | b ;
    return a ;
}

/**
 * @brief   Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4f operator|(const Vector4f::Mask& a, const Vector4f& b) {
    return _mm_or_ps(a, b) ;
}


                                                                     /** XOR **/
/**
 * @brief   Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4f operator^(const Vector4f& a, const Vector4f& b) {
    return _mm_xor_ps(a, b) ;
}

/**
 * @brief   Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4f& operator^=(Vector4f& a, const Vector4f& b) {
    a = a ^ b ;
    return a ;
}

/**
 * @brief   Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4f operator^(const Vector4f& a, const Vector4f::Mask& b) {
    return _mm_xor_ps(a, b) ;
}

/**
 * @brief   Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4f& operator^=(Vector4f& a, const Vector4f::Mask& b) {
    a = a ^ b ;
    return a ;
}

/**
 * @brief   Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4f operator^(const Vector4f::Mask& a, const Vector4f& b) {
    return _mm_xor_ps(a, b) ;
}
