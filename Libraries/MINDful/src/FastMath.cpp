#include <FastMath.h>
#include <vector>


namespace Mind {

    namespace FastMath {
        /** @brief  Lookup table containing some sinus values. */
        static std::vector<Scalar> SinusCache ;
        /** @brief  Lookup table containing some cosinus values. */
        static std::vector<Scalar> CosinusCache ;
        /** @brief  Lookup table containing some tangent values. */
        static std::vector<Scalar> TangentCache ;


        void init(unsigned int steps) {
            Scalar stepValue = Math::PI / 180. ;

            SinusCache.clear() ;
            CosinusCache.clear() ;
            TangentCache.clear() ;


            SinusCache.reserve(steps) ;
            CosinusCache.reserve(steps) ;
            TangentCache.reserve(steps) ;


            // If access to index zero of the caches
            SinusCache.push_back(::sin(0.)) ;
            CosinusCache.push_back(::cos(0.)) ;
            TangentCache.push_back(::tan(0.)) ;

            SinusCache.push_back(::sin(stepValue)) ;
            CosinusCache.push_back(::cos(stepValue)) ;
            TangentCache.push_back(::tan(stepValue)) ;

            // Additionnal divisions
            for (unsigned int step = 2 ; step < steps ; step++) {
                SinusCache.push_back(::sin(stepValue * step)) ;
                CosinusCache.push_back(::cos(stepValue * step)) ;
                TangentCache.push_back(::tan(stepValue * step)) ;
            }
        }


        float sin(unsigned int x) {
            return SinusCache[x] ;
        }

        float cos(unsigned int x) {
            return CosinusCache[x] ;
        }

        float tan(unsigned int x) {
            return TangentCache[x] ;
        }



        int round(Scalar value) {
            int integer_value = value ;
            if (integer_value > 0) {
                if (value - integer_value < 0.5f)
                    return integer_value ;
                return integer_value + 1 ;
            }
            else {
                if (value - integer_value > -0.5f)
                    return integer_value ;
                return integer_value - 1 ;
            }
        }


        int ceil(Scalar value) {
            int integer_value = value ;
            return (value > 0) ? integer_value + 1 : integer_value ;
        }


        int floor(Scalar value) {
            int integer_value = value ;
            return (integer_value > 0) ? integer_value : integer_value - 1 ;
        }

        long pow(int value, unsigned char exponent) {
            if (exponent == 1) return value ;

            long acc = 1L ;
            for (unsigned char exp = 0 ; exp < exponent ; exp++)
                acc *= value ;
            return acc ;
        }

        Scalar sqrt(Scalar value) {
            #ifdef USE_SIMD
                SIMD::Vector4f valueVec4(value) ;
                valueVec4 = SIMD::Vector4f::fast_sqrt(valueVec4) ;
                AlignedArray4f valueArray ;
                valueVec4.get(valueArray) ;
                return valueArray[0] ;
            #else
                return ::sqrt(value) ;
            #endif
        }
    } ;

} ;
