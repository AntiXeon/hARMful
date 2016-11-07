#include <transitions/interpolations/in_interpolations/LinearInInterpolation.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    LinearInInterpolation::LinearInInterpolation() {}

    LinearInInterpolation::~LinearInInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar LinearInInterpolation::interpolate(
                                                    const int& last,
                                                    const int& now
                                                   ) {
        // Interpolation function is computed between 0 and 1.
        return now / last ;
    }

} ;
