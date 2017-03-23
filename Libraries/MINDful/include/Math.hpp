#ifndef __MIND__MATH__
#define __MIND__MATH__

#include <utility>
#include <vector>
#include <cstdint>
#include <cmath>

#include <MINDTypes.hpp>

namespace Mind {
    /**
     * Additional math operations for convenient use.
     */
    namespace Math {
        /** Perigon angle is a 360° angle. */
        constexpr Scalar PerigonAngleDegrees     = 360.f ;
        /** Straight angle is a 180° angle. */
        constexpr Scalar StraightAngleDegrees    = Math::PerigonAngleDegrees / 2.f ;
        /** Right is a 90° angle. */
        constexpr Scalar RightAngleDegrees       = Math::PerigonAngleDegrees / 4.f ;

        /** Approximation of PI value. */
        constexpr Scalar Pi                      = 4.f * atan(1.f) ;
        /** Approximation of PI/2 value. */
        constexpr Scalar HalfPi                  = Math::Pi / 2.f ;
        /** Approximation of PI/4 value. */
        constexpr Scalar QuartPi                 = Math::Pi / 4.f ;
        /** Approximation of PI*2 value. */
        constexpr Scalar PiTwice                 = Math::Pi * 2.f ;
        /** Computation of PI / 360. */
        constexpr Scalar PiOver360               = Math::Pi / Math::PerigonAngleDegrees ;
        /** Approximation of PI^2 value. */
        constexpr Scalar SquaredPi               = Math::Pi * Math::Pi ;

        /** Value used to convert degrees to radians. */
        constexpr Scalar DegreesToRadians = Math::Pi / Math::StraightAngleDegrees ;
        /** Value used to convert radians to degrees. */
        constexpr Scalar RadiansToDegrees = Math::StraightAngleDegrees / Math::Pi ;

                                                                /*** ANGLES ***/
        /**
         * Convert degrees to radians.
         * @param   degrees Value of the angle in degrees.
         * @return  Value of the angle in radians.
         */
        inline Scalar toRadians(const Scalar degrees) ;

        /**
         * Convert radians to degrees.
         * @param   radians Value of the angle in radians.
         * @return  Value of the angle in degrees.
         */
        inline Scalar toDegrees(const Scalar radians) ;

                                                            /*** ALGORITHMS ***/
        /**
         * Returns sqrt(x^2 + y^2) without intermediate overflow or underflow.
         * @param   value   Value whose absolute one is wanted.
         * @return  The absolute value.
         */
        template <class T>
        Scalar hypot(const T x, const T y) ;

        /**
         * Check if a Scalar value is negative.
         * @param   value   Value to check.
         * @return  TRUE if @a value is negative, FALSE otherwise.
         */
        bool isNegative(const Scalar value) ;

        /**
         * Check if a Scalar value is not a number.
         * @param   value   Value to check.
         * @return  TRUE if @a value is NaN, FALSE otherwise.
         */
        bool isNaN(const Scalar value) ;

        /**
         * Check if a Scalar value is infinite.
         * @param   value   Value to check.
         * @return  TRUE if @a value is infinite, FALSE otherwise.
         */
        bool isInf(const Scalar value) ;
    } ;

    /**************************** IMPLEMENTATIONS *****************************/
                                                                /*** ANGLES ***/
    Scalar Math::toRadians(const Scalar degrees) {
        return degrees * Math::DegreesToRadians ;
    }


    Scalar Math::toDegrees(const Scalar radians) {
        return radians * Math::RadiansToDegrees ;
    }

                                                            /*** ALGORITHMS ***/
    template <class T>
    Scalar Math::hypot(const T x, const T y) {
        return sqrt((x * x) + (y * y)) ;
    }


    /**
     * Convert degrees to radians.
     * @param   degrees Value of the angle in degrees.
     * @return  Value of the angle in radians.
     */
    constexpr Scalar operator"" _deg(const long double degrees) {
        return degrees * Math::DegreesToRadians ;
    }

    /**
     * Convert radians to degrees.
     * @param   radians Value of the angle in radians.
     * @return  Value of the angle in degrees.
     */
    constexpr Scalar operator"" _rad(const long double radians) {
        return radians * Math::RadiansToDegrees ;
    }
} ;

#endif
