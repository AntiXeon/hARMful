                                                                /** ADDITION **/
/**
 * Add two Vector4i, each element of a Vector4i to its corresponding one in the
 * other Vector4i.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4i operator+(const Vector4i& a, const Vector4i b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] + (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Add a Vector4i to a float. The float is converted to a Vector4i where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4i operator+(const Vector4i& a, const float b) {
    return a + Vector4i(static_cast<int32_t>(b)) ;
}

/**
 * Add a Vector4i to a float. The float is converted to a Vector4i where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4i operator+(const float a, const Vector4i& b) {
    return Vector4i(static_cast<int32_t>(a)) + b ;
}

/**
 * Add a Vector4i to a float. The float is converted to a Vector4i where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition stored in the first operand.
 */
static inline Vector4i& operator+=(Vector4i& a, const Vector4i& b) {
    a = a + b ;
    return a ;
}

/**
 * Add two Vector4i, each element of a Vector4i to its corresponding
 * one in the other Vector4i.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition stored in the first operand.
 */
static inline Vector4i& operator+=(Vector4i& a, const float b) {
    a = a + Vector4i(static_cast<int32_t>(b)) ;
    return a ;
}


                                                               /** INCREMENT **/
/**
 * Postfix incrementation.
 * @param   a   Vector4i for which each component is increased of +1.
 * @warning Quite slower than prefix incrementation.
 */
static inline Vector4i operator++(Vector4i& a, int) {
    Vector4i previous = a ;
    a = a + 1.f ;
    return previous ;
}

/**
 * Prefix incrementation.
 * @param   a   Vector4i for which each component is increased of +1.
 */
static inline Vector4i& operator++(Vector4i& a) {
    a = a + 1.f ;
    return a ;
}


                                                              /** DIFFERENCE **/
/**
 * Substract two Vector4i, each element of a Vector4i to its corresponding one
 * in the other Vector4i.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4i operator-(const Vector4i& a, const Vector4i b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] - (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Substract a Vector4i to a float. The float is converted to a Vector4i where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4i operator-(const Vector4i& a, const float b) {
    return a - Vector4i(static_cast<int32_t>(b)) ;
}

/**
 * Substract a Vector4i to a float. The float is converted to a Vector4i where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4i operator-(const float a, const Vector4i& b) {
    return Vector4i(static_cast<int32_t>(a)) - b ;
}

/**
 * Substract two Vector4i, each element of a Vector4i to its corresponding one
 * in the other Vector4i.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference stored in the first operand.
 */
static inline Vector4i& operator-=(Vector4i& a, const Vector4i& b) {
    a = a - b ;
    return a ;
}

/**
 * Substract a Vector4i to a float. The float is converted to a Vector4i where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference stored in the first operand.
 */
static inline Vector4i& operator-=(Vector4i& a, const float b) {
    a = a - Vector4i(static_cast<int32_t>(b)) ;
    return a ;
}


                                                                  /** NEGATE **/
/**
 * Negate a Vector4.
 * @param   a   The Vector4 to negate.
 * @return  The negated Vector4.
 */
static inline Vector4i operator-(const Vector4i& a) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = -(*aRaw)[index] ;
    }
    return result ;
}


                                                               /** DECREMENT **/
/**
 * Postfix decrementation.
 * @param   a   Vector4i for which each component is decreased of -1.
 * @warning Quite slower than prefix decrementation.
 */
static inline Vector4i operator--(Vector4i& a, int) {
    Vector4i previous = a ;
    a = a - 1.f ;
    return previous ;
}

/**
 * Prefix decrementation.
 * @param   a   Vector4i for which each component is decreased of -1.
 */
static inline Vector4i& operator--(Vector4i& a) {
    a = a - 1.f ;
    return a ;
}


                                                                /** MULTIPLY **/
/**
 * Multiply two Vector4i, each element of a Vector4i to its corresponding one
 * in the other Vector4i.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4i operator*(const Vector4i& a, const Vector4i b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] * (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Multiply a Vector4i to a float. The float is converted to a Vector4i where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4i operator*(const Vector4i& a, const float b) {
    return a * Vector4i(static_cast<int32_t>(b)) ;
}

/**
 * Multiply a Vector4i to a float. The float is converted to a Vector4i where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4i operator*(const float a, const Vector4i& b) {
    return Vector4i(static_cast<int32_t>(a)) * b ;
}

/**
 * Multiply two Vector4i, each element of a Vector4i to its corresponding one in
 * the other Vector4i.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product stored in the first operand.
 */
static inline Vector4i& operator*=(Vector4i& a, const Vector4i& b) {
    a = a * b ;
    return a ;
}

/**
 * Multiply a Vector4i to a float. The float is converted to a Vector4i where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product stored in the first operand.
 */
static inline Vector4i& operator*=(Vector4i& a, const float b) {
    a = a * Vector4i(static_cast<int32_t>(b)) ;
    return a ;
}


                                                  /*** COMPARISON OPERATORS ***/
/**
 * Check if two Vector4i objects contain the same values.
 * The positions for which the values are equal are set to TRUE.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4i::Mask in which TRUE is set for positions where values are
 * equal, FALSE for different values in the Vector4i parameters.
 */
static inline Vector4i::Mask operator==(const Vector4i& a, const Vector4i& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] == (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Check if two Vector4i objects contain different values.
 * The positions for which the values are different are set to TRUE.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4i::Mask in which TRUE is set for positions where values
 * are different, FALSE for different values in the Vector4i
 * parameters.
 */
static inline Vector4i::Mask operator!=(const Vector4i& a, const Vector4i& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] != (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Check positions <i>p</i> in Vector4i objects at which
 * @a a[<i>p</i>] < @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4i::Mask in which TRUE is set for positions where values of
 * @a a are lower than values of @a b.
 */
static inline Vector4i::Mask operator<(const Vector4i& a, const Vector4i& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] < (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Check positions <i>p</i> in Vector4i objects at which
 * @a a[<i>p</i>] > @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4i::Mask in which TRUE is set for positions where values of
 * @a a are greater than values of @a b.
 */
static inline Vector4i::Mask operator>(const Vector4i& a, const Vector4i& b) {
    return b < a ;
}

/**
 * Check positions <i>p</i> in Vector4i objects at which
 * @a a[<i>p</i>] >= @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4i::Mask in which TRUE is set for positions where values of
 * @a a are greater or equal to values of @a b.
 */
static inline Vector4i::Mask operator>=(const Vector4i& a, const Vector4i& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] >= (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Check positions <i>p</i> in Vector4i objects at which
 * @a a[<i>p</i>] <= @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4i::Mask in which TRUE is set for positions where values of
 * @a a are lower or equal to values of @a b.
 */
static inline Vector4i::Mask operator<=(const Vector4i& a, const Vector4i& b) {
    return b >= a ;
}

                                             /*** BITWISE LOGICAL OPERATORS ***/
/**
 * Reverse bits of a Vector4i.
 * @param   a   Vector for which the bits have to be reversed.
 * @return  A Vector4i corresponding the the @a a reversed at bit level.
 */
static inline Vector4i operator~(const Vector4i& a) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = ~(*aRaw)[index] ;
    }
    return result ;
}

                                                                     /** AND **/
/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4i operator&(const Vector4i& a, const Vector4i& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] & (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4i& operator&=(Vector4i& a, const Vector4i& b) {
    a = a & b ;
    return a ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4i operator&(const Vector4i& a, const Vector4i::Mask& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] & (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4i& operator&=(Vector4i& a, const Vector4i::Mask& b) {
    a = a & b ;
    return a ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4i operator&(const Vector4i::Mask& a, const Vector4i& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] & (*bRaw)[index] ;
    }
    return result ;
}


                                                                      /** OR **/
/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4i operator|(const Vector4i& a, const Vector4i& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] | (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4i& operator|=(Vector4i& a, const Vector4i& b) {
    a = a | b ;
    return a ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4i operator|(const Vector4i& a, const Vector4i::Mask& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] | (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4i& operator|=(Vector4i& a, const Vector4i::Mask& b) {
    a = a | b ;
    return a ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4i operator|(const Vector4i::Mask& a, const Vector4i& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] | (*bRaw)[index] ;
    }
    return result ;
}


                                                                     /** XOR **/
/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4i operator^(const Vector4i& a, const Vector4i& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] ^ (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4i& operator^=(Vector4i& a, const Vector4i& b) {
    a = a ^ b ;
    return a ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4i operator^(const Vector4i& a, const Vector4i::Mask& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] ^ (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4i& operator^=(Vector4i& a, const Vector4i::Mask& b) {
    a = a ^ b ;
    return a ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4i operator^(const Vector4i::Mask& a, const Vector4i& b) {
    int32x4_t result ;
    int32x4_t* aRaw = static_cast<int32x4_t*>(a) ;
    int32x4_t* bRaw = static_cast<int32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] ^ (*bRaw)[index] ;
    }
    return result ;
}


                                                                   /** SHIFT **/
/**
 * Shift left values of the Vector.
 * @param   vec     The Vector to shift.
 * @param   bits    Amount of bits to shift.
 * @return  The shifted Vector.
 */
inline static Vector4i operator<<(const Vector4i& vec, int32_t bits) {
    int32x4_t result ;
    int32x4_t* vecRaw = static_cast<int32x4_t*>(vec) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*vecRaw)[index] << bits ;
    }
    return result ;
}

/**
 * Shift left values of the Vector.
 * @param   vec     The Vector to shift.
 * @param   bits    Amount of bits to shift.
 * @return  The shifted Vector.
 */
inline static Vector4i& operator<<=(Vector4i& vec, int32_t bits) {
    vec = vec << bits ;
    return vec ;
}


/**
 * Shift right values of the Vector.
 * @param   vec     The Vector to shift.
 * @param   bits    Amount of bits to shift.
 * @return  The shifted Vector.
 */
inline static Vector4i operator>>(const Vector4i& vec, int32_t bits) {
    int32x4_t result ;
    int32x4_t* vecRaw = static_cast<int32x4_t*>(vec) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*vecRaw)[index] >> bits ;
    }
    return result ;
}

/**
 * Shift right values of the Vector.
 * @param   vec     The Vector to shift.
 * @param   bits    Amount of bits to shift.
 * @return  The shifted Vector.
 */
inline static Vector4i& operator>>=(Vector4i& vec, int32_t bits) {
    vec = vec << bits ;
    return vec ;
}
