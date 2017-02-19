                                                                     /** AND **/
/**
 * Bitwise AND operator on two Masks.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE if they are TRUE if both parameters.
 *          They are FALSE if at least one operand has FALSE at that position.
 */
static inline Vector4f::Mask operator&(
    const Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t aBinary = (*(uint32_t*) &valueA) ;
        uint32_t bBinary = (*(uint32_t*) &valueB) ;
        uint32_t comparison = aBinary & bBinary ;
        result[index] = *((Scalar*) &comparison) ;
    }
    return result ;
}

/**
 * Bitwise AND operator on two Masks. The result is affected to the first
 * operand.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE if they are TRUE if both parameters.
 *          They are FALSE if at least one operand has FALSE at that position.
 */
static inline Vector4f::Mask& operator&=(
    Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    a = a & b ;
    return a ;
}


                                                                      /** OR **/
/**
 * Bitwise OR operator on two Masks.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are FALSE if they are FALSE if both
 *          parameters. They are TRUE if at least one operand has TRUE at that
 *          position.
 */
static inline Vector4f::Mask operator|(
    const Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t aBinary = (*(uint32_t*) &valueA) ;
        uint32_t bBinary = (*(uint32_t*) &valueB) ;
        uint32_t comparison = aBinary | bBinary ;
        result[index] = *((Scalar*) &comparison) ;
    }
    return result ;
}

/**
 * Bitwise OR operator on two Masks. The result is affected to the first
 * operand.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are FALSE if they are FALSE if both
 *          parameters. They are TRUE if at least one operand has TRUE at that
 *          position.
 */
static inline Vector4f::Mask& operator|=(
    Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    a = a | b ;
    return a ;
}


                                                                     /** XOR **/
/**
 * Bitwise XOR operator on two Masks.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE only when the two operands have
 *          different values at a same given position.
 */
static inline Vector4f::Mask operator^(
    const Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    float32x4_t result ;
    for (unsigned int index = 0 ; index < Vector4f::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        Scalar valueB = (*(float32x4_t*) b)[index] ;

        uint32_t aBinary = (*(uint32_t*) &valueA) ;
        uint32_t bBinary = (*(uint32_t*) &valueB) ;
        uint32_t comparison = aBinary ^ bBinary ;
        result[index] = *((Scalar*) &comparison) ;
    }
    return result ;
}

/**
 * Bitwise XOR operator on two Masks. The result is affected to the
 *          first operand.
 * @param   a   First operand.
 * @param   b   Second operand.
 * @return  A Mask in which values are TRUE only when the two operands have
 *          different values at a same given position.
 */
static inline Vector4f::Mask& operator^=(
    Vector4f::Mask& a,
    const Vector4f::Mask& b
) {
    a = a ^ b ;
    return a ;
}


                                                                     /** NOT **/
/**
 * Reverse each boolean value.
 * @param   a   The Mask for which bits must be reversed.
 * @return  The result Mask, for which bit are reversed compared to input.
 */
static inline Vector4f::Mask operator~(const Vector4f::Mask& a) {
    float32x4_t mask ;
    for (unsigned int index = 0 ; index < Vector4f::Mask::size() ; ++index) {
        Scalar valueA = (*(float32x4_t*) a)[index] ;
        uint32_t tmp = ~(*(uint32_t*) &valueA) ;
        mask[index] = *((float*) &tmp) ;
    }
    return mask ;
}
