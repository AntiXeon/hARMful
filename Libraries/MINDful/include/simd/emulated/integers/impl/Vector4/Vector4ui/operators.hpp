                                                                /** ADDITION **/
/**
 * Add two Vector4ui, each element of a Vector4ui to its corresponding one in
 * the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4ui operator+(const Vector4ui& a, const Vector4ui b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
         result[index] = (*aRaw)[index] + (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Add a Vector4ui to a float. The float is converted to a Vector4ui where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4ui operator+(const Vector4ui& a, const float b) {
    return a + Vector4ui(b) ;
}

/**
 * Add a Vector4ui to a float. The float is converted to a Vector4ui where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4ui operator+(const float a, const Vector4ui& b) {
    return Vector4ui(a) + b ;
}

/**
 * Add a Vector4ui to a float. The float is converted to a Vector4ui where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition stored in the first operand.
 */
static inline Vector4ui& operator+=(Vector4ui& a, const Vector4ui& b) {
    a = a + b ;
    return a ;
}

/**
 * Add two Vector4ui, each element of a Vector4ui to its corresponding one in
 * the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition stored in the first operand.
 */
static inline Vector4ui& operator+=(Vector4ui& a, const float b) {
    a = a + Vector4ui(b) ;
    return a ;
}


                                                               /** INCREMENT **/
/**
 * Postfix incrementation.
 * @param   a   Vector4ui for which each component is increased of +1.
 * @warning Quite slower than prefix incrementation.
 */
static inline Vector4ui operator++(Vector4ui& a, int) {
    Vector4ui previous = a ;
    a = a + 1.f ;
    return previous ;
}

/**
 * Prefix incrementation.
 * @param   a   Vector4ui for which each component is increased of +1.
 */
static inline Vector4ui& operator++(Vector4ui& a) {
    a = a + 1.f ;
    return a ;
}


                                                              /** DIFFERENCE **/
/**
 * Substract two Vector4ui, each element of a Vector4ui to its corresponding one
 * in the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4ui operator-(const Vector4ui& a, const Vector4ui b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] - (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Substract a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4ui operator-(const Vector4ui& a, const float b) {
    return a - Vector4ui(b) ;
}

/**
 * Substract a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4ui operator-(const float a, const Vector4ui& b) {
    return Vector4ui(a) - b ;
}

/**
 * Substract two Vector4ui, each element of a Vector4ui to its corresponding one
 * in the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference stored in the first operand.
 */
static inline Vector4ui& operator-=(Vector4ui& a, const Vector4ui& b) {
    a = a - b ;
    return a ;
}

/**
 * Substract a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference stored in the first operand.
 */
static inline Vector4ui& operator-=(Vector4ui& a, const float b) {
    a = a - Vector4ui(b) ;
    return a ;
}


                                                                  /** NEGATE **/
/**
 * Negate a Vector4.
 * @param   a   The Vector4 to negate.
 * @return  The negated Vector4.
 */
static inline Vector4ui operator-(const Vector4ui& a) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = -(*aRaw)[index] ;
    }
    return result ;
}


                                                               /** DECREMENT **/
/**
 * Postfix decrementation.
 * @param   a   Vector4ui for which each component is decreased of -1.
 * @warning Quite slower than prefix decrementation.
 */
static inline Vector4ui operator--(Vector4ui& a, int) {
    Vector4ui previous = a ;
    a = a - 1.f ;
    return previous ;
}

/**
 * Prefix decrementation.
 * @param   a   Vector4ui for which each component is decreased of -1.
 */
static inline Vector4ui& operator--(Vector4ui& a) {
    a = a - 1.f ;
    return a ;
}


                                                                /** MULTIPLY **/
/**
 * Multiply two Vector4ui, each element of a Vector4ui to its corresponding one
 * in the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4ui operator*(const Vector4ui& a, const Vector4ui b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] * (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Multiply a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4ui operator*(const Vector4ui& a, const float b) {
    return a * Vector4ui(b) ;
}

/**
 * Multiply a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4ui operator*(const float a, const Vector4ui& b) {
    return Vector4ui(a) * b ;
}

/**
 * Multiply two Vector4ui, each element of a Vector4ui to its corresponding one
 * in the other Vector4ui.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product stored in the first operand.
 */
static inline Vector4ui& operator*=(Vector4ui& a, const Vector4ui& b) {
    a = a * b ;
    return a ;
}

/**
 * Multiply a Vector4ui to a float. The float is converted to a Vector4ui where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product stored in the first operand.
 */
static inline Vector4ui& operator*=(Vector4ui& a, const float b) {
    a = a * Vector4ui(b) ;
    return a ;
}


                                                  /*** COMPARISON OPERATORS ***/
/**
 * Check if two Vector4ui objects contain the same values. The positions for
 * which the values are equal are set to TRUE.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values
 *          are equal, FALSE for different values in the Vector4ui parameters.
 */
static inline Vector4ui::Mask operator==(const Vector4ui& a, const Vector4ui& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] == (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Check if two Vector4ui objects contain different values. The positions for
 * which the values are different are set to TRUE.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values
 *          are different, FALSE for different values in the Vector4ui
 *          parameters.
 */
static inline Vector4ui::Mask operator!=(const Vector4ui& a, const Vector4ui& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] != (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Check positions <i>p</i> in Vector4ui objects at which
 * @a a[<i>p</i>] < @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values of
 *          @a a are lower than values of @a b.
 */
static inline Vector4ui::Mask operator<(const Vector4ui& a, const Vector4ui& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] < (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Check positions <i>p</i> in Vector4ui objects at which
 * @a a[<i>p</i>] > @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values of
 *          @a a are greater than values of @a b.
 */
static inline Vector4ui::Mask operator>(const Vector4ui& a, const Vector4ui& b) {
    return b < a ;
}

/**
 * Check positions <i>p</i> in Vector4ui objects at which
 * @a a[<i>p</i>] >= @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values of
 *          @a a are greater or equal to values of @a b.
 */
static inline Vector4ui::Mask operator>=(const Vector4ui& a, const Vector4ui& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
    for (unsigned int index = 0 ; index < Vector4i::size() ; ++index) {
        result[index] = (*aRaw)[index] >= (*bRaw)[index] ;
    }
    return result ;
}

/**
 * Check positions <i>p</i> in Vector4ui objects at which
 * @a a[<i>p</i>] <= @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4ui::Mask in which TRUE is set for positions where values of
 *          @a a are lower or equal to values of @a b.
 */
static inline Vector4ui::Mask operator<=(const Vector4ui& a, const Vector4ui& b) {
    return b >= a ;
}

                                             /*** BITWISE LOGICAL OPERATORS ***/
/**
 * Reverse bits of a Vector4ui.
 * @param   a   Vector for which the bits have to be reversed.
 * @return  A Vector4ui corresponding the the @a a reversed at bit level.
 */
static inline Vector4ui operator~(const Vector4ui& a) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
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
static inline Vector4ui operator&(const Vector4ui& a, const Vector4ui& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
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
static inline Vector4ui& operator&=(Vector4ui& a, const Vector4ui& b) {
    a = a & b ;
    return a ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4ui operator&(const Vector4ui& a, const Vector4ui::Mask& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
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
static inline Vector4ui& operator&=(Vector4ui& a, const Vector4ui::Mask& b) {
    a = a & b ;
    return a ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4ui operator&(const Vector4ui::Mask& a, const Vector4ui& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
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
static inline Vector4ui operator|(const Vector4ui& a, const Vector4ui& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
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
static inline Vector4ui& operator|=(Vector4ui& a, const Vector4ui& b) {
    a = a | b ;
    return a ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4ui operator|(const Vector4ui& a, const Vector4ui::Mask& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
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
static inline Vector4ui& operator|=(Vector4ui& a, const Vector4ui::Mask& b) {
    a = a | b ;
    return a ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4ui operator|(const Vector4ui::Mask& a, const Vector4ui& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
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
static inline Vector4ui operator^(const Vector4ui& a, const Vector4ui& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
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
static inline Vector4ui& operator^=(Vector4ui& a, const Vector4ui& b) {
    a = a ^ b ;
    return a ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4ui operator^(const Vector4ui& a, const Vector4ui::Mask& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
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
static inline Vector4ui& operator^=(Vector4ui& a, const Vector4ui::Mask& b) {
    a = a ^ b ;
    return a ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4ui operator^(const Vector4ui::Mask& a, const Vector4ui& b) {
    uint32x4_t result ;
    uint32x4_t* aRaw = static_cast<uint32x4_t*>(a) ;
    uint32x4_t* bRaw = static_cast<uint32x4_t*>(b) ;
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
inline static Vector4ui operator<<(const Vector4ui& vec, int32_t bits) {
    uint32x4_t result ;
    uint32x4_t* vecRaw = static_cast<uint32x4_t*>(vec) ;
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
inline static Vector4ui& operator<<=(Vector4ui& vec, int32_t bits) {
    vec = vec << bits ;
    return vec ;
}


/**
 * Shift right values of the Vector.
 * @param   vec     The Vector to shift.
 * @param   bits    Amount of bits to shift.
 * @return  The shifted Vector.
 */
inline static Vector4ui operator>>(const Vector4ui& vec, int32_t bits) {
    uint32x4_t result ;
    uint32x4_t* vecRaw = static_cast<uint32x4_t*>(vec) ;
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
inline static Vector4ui& operator>>=(Vector4ui& vec, int32_t bits) {
    vec = vec << bits ;
    return vec ;
}
