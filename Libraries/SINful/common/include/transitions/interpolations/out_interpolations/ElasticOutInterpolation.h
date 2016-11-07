#ifndef __SIN_ELASTIC_OUT_INTERPOLATION__
#define __SIN_ELASTIC_OUT_INTERPOLATION__


#include <transitions/interpolations/IInterpolation.h>


namespace Sin {

    /**
     * @brief   Elastic interpolation of values.
     *          It follows the formula
     *          <b>y(x) = pow(2, -10) * sin((x * (2 * PI / 0.3)))</b> for x in [0;1].
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class ElasticOutInterpolation : public IInterpolation {
        public:
            /**
             * @brief   Create a ElasticOutInterpolation.
             */
            ElasticOutInterpolation() ;

            /**
             * @brief   Destruction of the ElasticOutInterpolation.
             */
            virtual ~ElasticOutInterpolation() ;

            /**
             * @brief   Interpolate values to get the current value factor.
             * @param   last    Last of the animation to compute the
             *                  interpolation at the wanted moment.
             * @param   now     Current time in the animation to determine the
             *                  factor value.
             * @return  The factor to compute the current transition value.
             */
            Mind::Scalar interpolate(const int& last, const int& now) ;
    } ;

} ;


#endif
