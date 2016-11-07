#ifndef __TEST_FLOAT__
#define __TEST_FLOAT__

const float EPSILON = 1e-2f ;

/**
 * @brief   Check if value is in the Epsilon interval.
 * @param   value_test      Value to test.
 * @param   compared        Center of the interval to check if the @a value_test
 *                          is (strictly) inside.
 * @return  TRUE if @a value_test is inside the Epsilon interval, FALSE else.
 */
static bool fclose_to(float value_test, float compared) {
    float tmpMinusEpsilon = compared - EPSILON ;
    float tmpPlusEpsilon = compared + EPSILON ;
    return ((tmpMinusEpsilon < value_test) && (value_test < tmpPlusEpsilon)) ;
}

#endif
