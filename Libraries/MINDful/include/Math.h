#ifndef __MIND_MATH__
#define __MIND_MATH__


#include <Platform.h>
#include <utility>
#include <vector>
#include <stdint.h>
#include <math.h>

#include <MINDTypes.h>


namespace Mind {

    namespace Math {
        /** @brief  Approximation of PI value. */
        const Scalar PI                      = 4.f * atan(1.f) ;
        /** @brief  Approximation of PI/2 value. */
        const Scalar PI_HALF                 = Math::PI / 2.f ;
        /** @brief  Approximation of PI/4 value. */
        const Scalar PI_QUART                = Math::PI / 4.f ;
        /** @brief  Approximation of PI*2 value. */
        const Scalar PI_TWICE                = Math::PI * 2.f ;
        /** @brief  Computation of PI / 360. */
        const Scalar PI_ON_360               = Math::PI / 360.f ;
        /** @brief  Approximation of PI^2 value. */
        const Scalar PI_SQUARED              = Math::PI * Math::PI ;

        /** @brief  Perigon angle is a 360° angle. */
        const Scalar PERIGON_ANGLE_DEGREE    = 360.f ;
        /** @brief  Straight angle is a 180° angle. */
        const Scalar STRAIGHT_ANGLE_DEGREE   = Math::PERIGON_ANGLE_DEGREE / 2.f ;
        /** @brief  Right is a 90° angle. */
        const Scalar RIGHT_ANGLE_DEGREE      = Math::PERIGON_ANGLE_DEGREE / 4.f ;

                                                                                    /*** ANGLES ***/
        /**
        * @brief   Convert degrees to radians.
        * @param   degrees Value of the angle in degrees.
        * @return  Value of the angle in radians.
        */
        Scalar to_radian(Scalar degrees) ;

        /**
        * @brief   Convert radians to degrees.
        * @param   radians Value of the angle in radians.
        * @return  Value of the angle in degrees.
        */
        Scalar to_degree(Scalar radians) ;


                                                                                    /*** ALGORITHMS ***/
        /**
        * @brief   Returns sqrt(x^2 + y^2) without intermediate overflow or
        *          underflow.
        * @param   value   Value whose absolute one is wanted.
        * @return  The absolute value.
        */
        template <class T>
        Scalar hypot(const T& x, const T& y) ;

        /**
        * @brief   Get the absolute value of the given one.
        * @param   value   Value whose absolute one is wanted.
        * @return  The absolute value.
        */
        template <class T>
        T abs(const T& value) ;


        /**
        * @brief   Get the maximal value among the two given.
        * @param   a   First value to test.
        * @param   b   Second value to test.
        * @return  The maximal value.
        */
        template <class T>
        T max(const T& a, const T& b) ;

        /**
        * @brief   Get the minimal value among the two given.
        * @param   a   First value to test.
        * @param   b   Second value to test.
        * @return  The minimal value.
        */
        template <class T>
        T min(const T& a, const T& b) ;


        /**
        * @brief   Get the maximal value among a set of values.
        * @param   values  Set of values.
        * @param   count   Amount of values in the set.
        * @return  The maximal value.
        */
        template <class T>
        T max(T* values, unsigned int count) ;

        /**
        * @brief   Get the minimal value among a set of values.
        * @param   values  Set of values.
        * @param   count   Amount of values in the set.
        * @return  The minimal value.
        */
        template <class T>
        T min(T* values, unsigned int count) ;

        /**
        * @brief   Get the maximal value among a set of values.
        * @param   values  Set of values.
        * @return  The maximal value.
        */
        template <class T>
        T max(const std::vector<T>& values) ;

        /**
        * @brief   Get the minimal value among a set of values.
        * @param   values  Set of values.
        * @return  The minimal value.
        */
        template <class T>
        T min(const std::vector<T>& values) ;

       /**
        * @brief   Get the minimal and maximal values among a set of values.
        * @param   values  Set of values.
        * @return  The minimal and maximal values.
        */
        template <class T>
        std::pair<T,T> minmax(const std::vector<T>& values) ;


        /**
         * @brief   Check if a Scalar value is negative.
         * @param   value   Value to check.
         * @return  TRUE if @a value is negative, FALSE otherwise.
         */
        bool is_negative(const Scalar& value) ;

        /**
         * @brief   Check if a Scalar value is not a number.
         * @param   value   Value to check.
         * @return  TRUE if @a value is NaN, FALSE otherwise.
         */
        bool is_nan(const Scalar& value) ;

        /**
         * @brief   Check if a Scalar value is infinite.
         * @param   value   Value to check.
         * @return  TRUE if @a value is infinite, FALSE otherwise.
         */
        bool is_inf(const Scalar& value) ;


        /**
        * @brief   Test if all of the values return TRUE when being tested.
        * @param   values  Set of values to test.
        * @param   test    Test function.
        */
        template <class T>
        bool all_of(const std::vector<T>& values, bool (*test)(const T&)) ;

        /**
        * @brief   Test if any of the values return TRUE when being tested.
        * @param   values  Set of values to test.
        * @param   test    Test function.
        */
        template <class T>
        bool any_of(const std::vector<T>& values, bool (*test)(const T&)) ;

        /**
        * @brief   Test if none of the values return TRUE when being tested.
        * @param   values  Set of values to test.
        * @param   test    Test function.
        */
        template <class T>
        bool none_of(const std::vector<T>& values, bool (*test)(const T&)) ;

        /**
        * @brief   Apply a function for each element of the values set.
        * @param   values  Set of values to treat.
        * @param   apply   The function to apply to each element.
        */
        template <class T>
        void foreach(std::vector<T>& values, T (*apply)(const T&)) ;



    /****************************** IMPLEMENTATIONS ******************************/
                                                                                    /*** ALGORITHMS ***/
        template <class T>
        Scalar hypot(const T& x, const T& y) {
            return sqrt((x * x) + (y * y)) ;
        }

        template <class T>
        T abs(const T& value) {
            return (value < 0) ? -value : value ;
        }

        template <class T>
        T max(const T& a, const T& b) {
            return (a > b) ? a : b ;
        }

        template <class T>
        T min(const T& a, const T& b) {
            return (a < b) ? a : b ;
        }


        template <class T>
        T max(T* values, unsigned int count) {
            if (values == NULL || count == 0)
                return 0 ;

            T maxValue = values[0] ;
            for (unsigned int index = 1 ; index < count ; index++) {
                if (values[index] > maxValue)
                    maxValue = values[index] ;
            }

            return maxValue ;
        }

        template <class T>
        T min(T* values, unsigned int count) {
            if (values == NULL || count == 0)
                return 0 ;

            T minValue = values[0] ;
            for (unsigned int index = 1 ; index < count ; index++) {
                if (values[index] < minValue)
                    minValue = values[index] ;
            }

            return minValue ;
        }


        template <class T>
        T max(const std::vector<T>& values) {
            size_t count = values.size() ;
            if (count == 0)
                return 0 ;

            T maxValue = values[0] ;
            for (size_t index = 1 ; index < count ; index++) {
                if (values[index] > maxValue)
                    maxValue = values[index] ;
            }

            return maxValue ;
        }

        template <class T>
        T min(const std::vector<T>& values) {
            size_t count = values.size() ;
            if (count == 0)
                return 0 ;

            T minValue = values[0] ;
            for (size_t index = 1 ; index < count ; index++) {
                if (values[index] < minValue)
                    minValue = values[index] ;
            }

            return minValue ;
        }

        template <class T>
        std::pair<T,T> minmax(const std::vector<T>& values) {
            return std::pair<T,T>(min(values), max(values)) ;
        }

        template <class T>
        std::pair<T,T> minmax(const T& a, const T& b) {
            return std::pair<T,T>(min(a, b), max(a, b)) ;
        }


        template <class T>
        bool all_of(const std::vector<T>& values, bool (*test)(const T&)) {
            size_t count = values.size() ;
            for (size_t index = 0 ; index < count ; index++) {
                if (!test(values[index]))
                    return false ;
            }

            return true ;
        }

        template <class T>
        bool any_of(const std::vector<T>& values, bool (*test)(const T&)) {
            size_t count = values.size() ;
            for (size_t index = 0 ; index < count ; index++) {
                if (test(values[index]))
                    return true ;
            }

            return false ;
        }

        template <class T>
        bool none_of(std::vector<T>& values, bool (*test)(const T&)) {
            size_t count = values.size() ;
            for (size_t index = 0 ; index < count ; index++) {
                if (test(values[index]))
                    return false ;
            }

            return true ;
        }

        template <class T>
        void foreach(std::vector<T>& values, T (*apply)(const T&)) {
            size_t count = values.size() ;
            for (size_t index = 0 ; index < count ; index++) {
                values[index] = apply(values[index]) ;
            }
        }
    } ;

} ;


#endif
