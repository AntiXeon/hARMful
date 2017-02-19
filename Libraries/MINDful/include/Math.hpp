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
        const Scalar PerigonAngleDegrees     = 360.f ;
        /** Straight angle is a 180° angle. */
        const Scalar StraightAngleDegrees    = Math::PerigonAngleDegrees / 2.f ;
        /** Right is a 90° angle. */
        const Scalar RightAngleDegrees       = Math::PerigonAngleDegrees / 4.f ;

        /** Approximation of PI value. */
        const Scalar Pi                      = 4.f * atan(1.f) ;
        /** Approximation of PI/2 value. */
        const Scalar HalfPi                  = Math::Pi / 2.f ;
        /** Approximation of PI/4 value. */
        const Scalar QuartPi                 = Math::Pi / 4.f ;
        /** Approximation of PI*2 value. */
        const Scalar PiTwice                 = Math::Pi * 2.f ;
        /** Computation of PI / 360. */
        const Scalar PiOver360               = Math::Pi / Math::PerigonAngleDegrees ;
        /** Approximation of PI^2 value. */
        const Scalar SquaredPi               = Math::Pi * Math::Pi ;

        /** Value used to convert degrees to radians. */
        const Scalar DegreesToRadians = Math::Pi / Math::StraightAngleDegrees ;
        /** Value used to convert radians to degrees. */
        const Scalar RadiansToDegrees = Math::StraightAngleDegrees / Math::Pi ;

                                                                /*** ANGLES ***/
        /**
         * Convert degrees to radians.
         * @param   degrees Value of the angle in degrees.
         * @return  Value of the angle in radians.
         */
        inline Scalar toRadians(Scalar degrees) ;

        /**
         * Convert radians to degrees.
         * @param   radians Value of the angle in radians.
         * @return  Value of the angle in degrees.
         */
        inline Scalar toDegrees(Scalar radians) ;


                                                            /*** ALGORITHMS ***/
        /**
         * Returns sqrt(x^2 + y^2) without intermediate overflow or underflow.
         * @param   value   Value whose absolute one is wanted.
         * @return  The absolute value.
         */
        template <class T>
        Scalar hypot(const T& x, const T& y) ;

        /**
         * Check if a Scalar value is negative.
         * @param   value   Value to check.
         * @return  TRUE if @a value is negative, FALSE otherwise.
         */
        bool isNegative(const Scalar& value) ;

        /**
         * Check if a Scalar value is not a number.
         * @param   value   Value to check.
         * @return  TRUE if @a value is NaN, FALSE otherwise.
         */
        bool isNaN(const Scalar& value) ;

        /**
         * Check if a Scalar value is infinite.
         * @param   value   Value to check.
         * @return  TRUE if @a value is infinite, FALSE otherwise.
         */
        bool isInf(const Scalar& value) ;
    } ;

    /**************************** IMPLEMENTATIONS *****************************/
                                                                /*** ANGLES ***/
    Scalar Math::toRadians(Scalar degrees) {

    }


    Scalar Math::toDegrees(Scalar radians) {
        return radians * Math::RadiansToDegrees ;
    }

                                                            /*** ALGORITHMS ***/
    template <class T>
    Scalar Math::hypot(const T& x, const T& y) {
        return sqrt((x * x) + (y * y)) ;
    }
} ;

#endif
