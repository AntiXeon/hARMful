                                                                /** ADDITION **/
/**
 * Add two Vector4f, each element of a Vector4f to its corresponding one in the
 * other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4f operator+(const Vector4f& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        result[index] = (*(float32x4_t*) a)[index] + (*(float32x4_t*) b)[index] ;
    }
    return result ;
}

/**
 * Add a Vector4f to a float. The float is converted to a Vector4f where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4f operator+(const Vector4f& a, const float b) {
    return a + Vector4f(b) ;
}

/**
 * Add a Vector4f to a float. The float is converted to a Vector4f where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition.
 */
static inline Vector4f operator+(const float a, const Vector4f& b) {
    return Vector4f(a) + b ;
}

/**
 * Add a Vector4f to a float. The float is converted to a Vector4f where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition stored in the first operand.
 */
static inline Vector4f& operator+=(Vector4f& a, const Vector4f& b) {
    a = a + b ;
    return a ;
}

/**
 * Add two Vector4f, each element of a Vector4f to its corresponding one in the
 * other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the addition stored in the first operand.
 */
static inline Vector4f& operator+=(Vector4f& a, const float b) {
    a = a + Vector4f(b) ;
    return a ;
}


                                                               /** INCREMENT **/
/**
 * Postfix incrementation.
 * @param   a   Vector4f for which each component is increased of +1.
 * @warning Quite slower than prefix incrementation.
 */
static inline Vector4f operator++(Vector4f& a, int) {
    Vector4f previous = a ;
    a = a + 1.f ;
    return previous ;
}

/**
 * Prefix incrementation.
 * @param   a   Vector4f for which each component is increased of +1.
 */
static inline Vector4f& operator++(Vector4f& a) {
    a = a + 1.f ;
    return a ;
}


                                                              /** DIFFERENCE **/
/**
 * Substract two Vector4f, each element of a Vector4f to its corresponding one
 * in the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4f operator-(const Vector4f& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        result[index] = (*(float32x4_t*) a)[index] - (*(float32x4_t*) b)[index] ;
    }
    return result ;
}

/**
 * Substract a Vector4f to a float. The float is converted to a Vector4f where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4f operator-(const Vector4f& a, const float b) {
    return a - Vector4f(b) ;
}

/**
 * Substract a Vector4f to a float. The float is converted to a Vector4f where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference.
 */
static inline Vector4f operator-(const float a, const Vector4f& b) {
    return Vector4f(a) - b ;
}

/**
 * Substract two Vector4f, each element of a Vector4f to its corresponding one
 * in the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference stored in the first operand.
 */
static inline Vector4f& operator-=(Vector4f& a, const Vector4f& b) {
    a = a - b ;
    return a ;
}

/**
 * Substract a Vector4f to a float. The float is converted to a Vector4f where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the difference stored in the first operand.
 */
static inline Vector4f& operator-=(Vector4f& a, const float b) {
    a = a - Vector4f(b) ;
    return a ;
}


                                                                  /** NEGATE **/
static inline Vector4f operator-(Vector4f& a) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        result[index] = -(*(float32x4_t*) a)[index] ;
    }
    return result ;
}


                                                               /** DECREMENT **/
/**
 * Postfix decrementation.
 * @param   a   Vector4f for which each component is decreased of -1.
 * @warning Quite slower than prefix decrementation.
 */
static inline Vector4f operator--(Vector4f& a, int) {
    Vector4f previous = a ;
    a = a - 1.f ;
    return previous ;
}

/**
 * Prefix decrementation.
 * @param   a   Vector4f for which each component is decreased of -1.

 */
static inline Vector4f& operator--(Vector4f& a) {
    a = a - 1.f ;
    return a ;
}


                                                                /** MULTIPLY **/
/**
 * Multiply two Vector4f, each element of a Vector4f to its corresponding one in
 * the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4f operator*(const Vector4f& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        result[index] = (*(float32x4_t*) a)[index] * (*(float32x4_t*) b)[index] ;
    }
    return result ;
}

/**
 * Multiply a Vector4f to a float. The float is converted to a Vector4f where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4f operator*(const Vector4f& a, const float b) {
    return a * Vector4f(b) ;
}

/**
 * Multiply a Vector4f to a float. The float is converted to a Vector4f where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product.
 */
static inline Vector4f operator*(const float a, const Vector4f& b) {
    return Vector4f(a) * b ;
}

/**
 * Multiply two Vector4f, each element of a Vector4f to its corresponding one in
 * the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product stored in the first operand.
 */
static inline Vector4f& operator*=(Vector4f& a, const Vector4f& b) {
    a = a * b ;
    return a ;
}

/**
 * Multiply a Vector4f to a float. The float is converted to a Vector4f where
 * all values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the product stored in the first operand.
 */
static inline Vector4f& operator*=(Vector4f& a, const float b) {
    a = a * Vector4f(b) ;
    return a ;
}


                                                                  /** DIVIDE **/
/**
 * Divide two Vector4f, each element of a Vector4f to its corresponding one in
 * the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the division.
 */
static inline Vector4f operator/(const Vector4f& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        result[index] = (*(float32x4_t*) a)[index] / (*(float32x4_t*) b)[index] ;
    }
    return result ;
}

/**
 * Divide a Vector4f to a float. The float is converted to a Vector4f where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the division.
 */
static inline Vector4f operator/(const Vector4f& a, const float b) {
    return a / Vector4f(b) ;
}

/**
 * Divide a Vector4f to a float. The float is converted to a Vector4f where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the division.
 */
static inline Vector4f operator/(const float a, const Vector4f& b) {
    return Vector4f(a) / b ;
}

/**
 * Divide two Vector4f, each element of a Vector4f to its corresponding one in
 * the other Vector4f.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the division stored in the first operand.
 */
static inline Vector4f& operator/=(Vector4f& a, const Vector4f& b) {
    a = a / b ;
    return a ;
}

/**
 * Divide a Vector4f to a float. The float is converted to a Vector4f where all
 * values are equal to the given float.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the division stored in the first operand.
 */
static inline Vector4f& operator/=(Vector4f& a, const float b) {
    a = a / Vector4f(b) ;
    return a ;
}

                                                  /*** COMPARISON OPERATORS ***/
/**
 * Check if two Vector4f objects contain the same values. The positions for
 * which the values are equal are set to TRUE.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values are
 *          equal, FALSE for different values in the Vector4f parameters.
 */
static inline Vector4f::Mask operator==(const Vector4f& a, const Vector4f& b) {
    float32x4_t mask ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;
        bool areEqual = (valueA == valueB) ;
        mask[index] = -uint32_t(areEqual) ;
    }
    return mask ;
}

/**
 * Check if two Vector4f objects contain the different values.
 * The positions for which the values are different are set to TRUE.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values are
 *          different, FALSE for equal values in the Vector4f parameters.
 */
static inline Vector4f::Mask operator!=(const Vector4f& a, const Vector4f& b) {
    float32x4_t mask ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;
        bool areNotEqual = (valueA != valueB) ;
        mask[index] = -uint32_t(areNotEqual) ;
    }
    return mask ;
}

/**
 * Check positions <i>p</i> in Vector4f objects at which
 * @a a[<i>p</i>] < @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values of
 *          @a a are lower than values of @a b.
 */
static inline Vector4f::Mask operator<(const Vector4f& a, const Vector4f& b) {
    float32x4_t mask ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;
        bool isALowerB = (valueA < valueB) ;
        mask[index] = -uint32_t(isALowerB) ;
    }
    return mask ;
}

/**
 * Check positions <i>p</i> in Vector4f objects at which
 * @a a[<i>p</i>] <= @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values of
 *          @a a are lower or equal to values of @a b.
 */
static inline Vector4f::Mask operator<=(const Vector4f& a, const Vector4f& b) {
    float32x4_t mask ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;
        bool isALowerEqualB = (valueA <= valueB) ;
        mask[index] = -uint32_t(isALowerEqualB) ;
    }
    return mask ;
}

/**
 * Check positions <i>p</i> in Vector4f objects at which
 * @a a[<i>p</i>] > @a b[<i>p</i>].
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Vector4f::Mask in which TRUE is set for positions where values of
 *          @a a are greater than values of @a b.
 */
static inline Vector4f::Mask operator>(const Vector4f& a, const Vector4f& b) {
    return b < a ;
}

/**
 * Check positions <i>p</i> in Vector4f objects at which
 * @a a[<i>p</i>] >= @a b[<i>p</i>].
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
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4f operator&(const Vector4f& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t* aBinary = reinterpret_cast<uint32_t*>(&valueA) ;
        uint32_t* bBinary = reinterpret_cast<uint32_t*>(&valueB) ;
        uint32_t comparison = (*aBinary) & (*bBinary) ;
        Scalar* result = reinterpret_cast<Scalar*>(&comparison) ;
        result[index] = *result ;
    }
    return result ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4f& operator&=(Vector4f& a, const Vector4f& b) {
    a = a & b ;
    return a ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4f operator&(const Vector4f& a, const Vector4f::Mask& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t* aBinary = reinterpret_cast<uint32_t*>(&valueA) ;
        uint32_t* bBinary = reinterpret_cast<uint32_t*>(&valueB) ;
        uint32_t comparison = (*aBinary) & (*bBinary) ;
        Scalar* result = reinterpret_cast<Scalar*>(&comparison) ;
        result[index] = *result ;
    }
    return result ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4f& operator&=(Vector4f& a, const Vector4f::Mask& b) {
    a = a & b ;
    return a ;
}

/**
 * Compute the bitwise AND of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise AND.
 */
static inline Vector4f operator&(const Vector4f::Mask& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t* aBinary = reinterpret_cast<uint32_t*>(&valueA) ;
        uint32_t* bBinary = reinterpret_cast<uint32_t*>(&valueB) ;
        uint32_t comparison = (*aBinary) & (*bBinary) ;
        Scalar* result = reinterpret_cast<Scalar*>(&comparison) ;
        result[index] = *result ;
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
static inline Vector4f operator|(const Vector4f& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t* aBinary = reinterpret_cast<uint32_t*>(&valueA) ;
        uint32_t* bBinary = reinterpret_cast<uint32_t*>(&valueB) ;
        uint32_t comparison = (*aBinary) | (*bBinary) ;
        Scalar* result = reinterpret_cast<Scalar*>(&comparison) ;
        result[index] = *result ;
    }
    return result ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4f& operator|=(Vector4f& a, const Vector4f& b) {
    a = a | b ;
    return a ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4f operator|(const Vector4f& a, const Vector4f::Mask& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t* aBinary = reinterpret_cast<uint32_t*>(&valueA) ;
        uint32_t* bBinary = reinterpret_cast<uint32_t*>(&valueB) ;
        uint32_t comparison = (*aBinary) | (*bBinary) ;
        Scalar* result = reinterpret_cast<Scalar*>(&comparison) ;
        result[index] = *result ;
    }
    return result ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4f& operator|=(Vector4f& a, const Vector4f::Mask& b) {
    a = a | b ;
    return a ;
}

/**
 * Compute the bitwise OR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise OR.
 */
static inline Vector4f operator|(const Vector4f::Mask& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t* aBinary = reinterpret_cast<uint32_t*>(&valueA) ;
        uint32_t* bBinary = reinterpret_cast<uint32_t*>(&valueB) ;
        uint32_t comparison = (*aBinary) | (*bBinary) ;
        Scalar* result = reinterpret_cast<Scalar*>(&comparison) ;
        result[index] = *result ;
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
static inline Vector4f operator^(const Vector4f& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t* aBinary = reinterpret_cast<uint32_t*>(&valueA) ;
        uint32_t* bBinary = reinterpret_cast<uint32_t*>(&valueB) ;
        uint32_t comparison = (*aBinary) ^ (*bBinary) ;
        Scalar* result = reinterpret_cast<Scalar*>(&comparison) ;
        result[index] = *result ;
    }
    return result ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4f& operator^=(Vector4f& a, const Vector4f& b) {
    a = a ^ b ;
    return a ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4f operator^(const Vector4f& a, const Vector4f::Mask& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t* aBinary = reinterpret_cast<uint32_t*>(&valueA) ;
        uint32_t* bBinary = reinterpret_cast<uint32_t*>(&valueB) ;
        uint32_t comparison = (*aBinary) ^ (*bBinary) ;
        Scalar* result = reinterpret_cast<Scalar*>(&comparison) ;
        result[index] = *result ;
    }
    return result ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4f& operator^=(Vector4f& a, const Vector4f::Mask& b) {
    a = a ^ b ;
    return a ;
}

/**
 * Compute the bitwise XOR of elements in @a a and @a b.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  Result of the bitwise XOR.
 */
static inline Vector4f operator^(const Vector4f::Mask& a, const Vector4f& b) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t* aBinary = reinterpret_cast<uint32_t*>(&valueA) ;
        uint32_t* bBinary = reinterpret_cast<uint32_t*>(&valueB) ;
        uint32_t comparison = (*aBinary) ^ (*bBinary) ;
        Scalar* result = reinterpret_cast<Scalar*>(&comparison) ;
        result[index] = *result ;
    }
    return result ;
}
