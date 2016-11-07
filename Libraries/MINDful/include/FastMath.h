#ifndef __MIND_FAST_MATH__
#define __MIND_FAST_MATH__


#include <MINDTypes.h>
#include <Math.h>


namespace Mind {

    /**
    * @brief    Fast math are speed-up mathematic operations, by caching values
    *           or some mystical yet really fast ways to get approximated
    *           results.
    * @author  CB (c) 2014
    * @version 0.1     2014/05/27
    */
    namespace FastMath {
        /**
        * @brief    Initialize the FastMath namespace.
        * @param    steps   FastMath can be initialized with a given amount of
        *                   steps to pre-compute some of the sinus, cosinus and
        *                   tangent values. It can then be adapted to the needs
        *                   of the application.
        *                   For convenient use, the default value is set to 360.
        *                   That way, you can use integer values as angle
        *                   expressed in degrees. For instance, you can call
        *                   later the function FastMath::sin(45) to get the
        *                   value of sin(45 degrees).
        */
        void init(unsigned int steps = 360) ;


        /**
        * @brief   Get the value of sinus for the cached value of sin(PI/x).
        * @param   x   Value of x in the sin(PI/x) equation (angle in degrees).
        * @return  The value of sin(PI/x).
        */
        float sin(unsigned int x) ;

        /**
        * @brief   Get the value of cosinus for the cached value of cos(PI/x).
        * @param   x   Value of x in the cos(PI/x) equation (angle in degrees).
        * @return  The value of cos(PI/x).
        */
        float cos(unsigned int x) ;

        /**
        * @brief   Get the value of cosinus for the cached value of tan(PI/x).
        * @param   x   Value of x in the tan(PI/x) equation (angle in degrees).
        * @return  The value of tan(PI/x).
        */
        float tan(unsigned int x) ;



        /**
        * @brief   Get a rounded value of the given one.
        * @param   value   Value to round.
        * @return  If value is smaller than x.5, x is returned. Otherwise, x+1 is
        *          returned.
        */
        int round(Scalar value) ;

        /**
        * @brief   Round a value upward.
        * @param   value   Value to round ceil.
        * @return  The smallest integer value that is not less than the given
        *          value.
        */
        int ceil(Scalar value) ;

        /**
        * @brief   Round a value downward.
        * @param   value   Value to round floor.
        * @return  The smallest integer value that is not greater than the given
        *          value.
        */
        int floor(Scalar value) ;

        /**
        * @brief   Compute value^exponent, with positive exponent only.
        * @param   value       The value to power.
        * @param   exponent    Exponent to compute the power of value. It can only
        *                      be integer positive value (if possible, lower than
        *                      15).
        * @return  The value of value^exponent.
        * @warning As the function uses integer values to optimize computational
        *          time, no result is insured for exponents greater or equal to 15.
        */
        long pow(int value, unsigned char exponent) ;

        /**
         * @brief   Compute the square root of the given value.
         * @param   value   Value for which the square root is wanted.
         * @return  Square root of the given value.
         */
        Scalar sqrt(Scalar value) ;
    } ;

} ;


#endif
