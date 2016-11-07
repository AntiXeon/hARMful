#include <Math.h>


namespace Mind {

    const Scalar DEGREE_RADIAN = Math::PI / Math::STRAIGHT_ANGLE_DEGREE ;
    const Scalar RADIAN_DEGREE = Math::STRAIGHT_ANGLE_DEGREE / Math::PI ;


    namespace Math {
                                                                                /*** ANGLES ***/
        Scalar to_radian(Scalar degrees) {
            return degrees * DEGREE_RADIAN ;
        }


        Scalar to_degree(Scalar radians) {
            return radians * RADIAN_DEGREE ;
        }


        bool is_negative(const Scalar& value) {
            // Float structure :
            // [ S | EEEEEEEE | FFFFFFFFFFFFFFFFFFFFFFF ]
            // -> 1 bit for Sign (S)
            // -> 8 bits for Exponent (E)
            // -> 23 bits for Fraction (F)
            // Convert the extended sign vector to a Mask (containing either 0x00000000
            // or 0xFFFFFFFF).
            return (*((uint32_t*) &value) >> 31) & 1 ;
        }

        bool is_nan(const Scalar& value) {
            // Float structure :
            // [ S | EEEEEEEE | FFFFFFFFFFFFFFFFFFFFFFF ]
            // -> 1 bit for Sign (S)
            // -> 8 bits for Exponent (E)
            // -> 23 bits for Fraction (F)
            const uint32_t MaskExponent = 0xFF000000 ;
            const uint32_t MaskFraction = ~MaskExponent ;

            uint32_t removedSignBit = (*((uint32_t*) &value)) << 1 ;
            uint32_t extractedExponent = removedSignBit & MaskExponent ;
            uint32_t extractedFraction = removedSignBit & MaskFraction ;
            return ((extractedExponent == MaskExponent) & (extractedFraction != 0)) ;
        }
        
        bool is_inf(const Scalar& value) {
            // Float structure :
            // [ S | EEEEEEEE | FFFFFFFFFFFFFFFFFFFFFFF ]
            // -> 1 bit for Sign (S)
            // -> 8 bits for Exponent (E)
            // -> 23 bits for Fraction (F)
            const uint32_t MaskInfiniteExponent = 0xFF000000 ;
    
            uint32_t removedSignBit = (*((uint32_t*) &value)) << 1 ;
            return (removedSignBit == MaskInfiniteExponent) ;
        }
    } ;

} ;
