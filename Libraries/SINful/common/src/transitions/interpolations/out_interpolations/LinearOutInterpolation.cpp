#include <transitions/interpolations/out_interpolations/LinearOutInterpolation.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    LinearOutInterpolation::LinearOutInterpolation() {}

    LinearOutInterpolation::~LinearOutInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar LinearOutInterpolation::interpolate(
                                                     const int& last,
                                                     const int& now
                                                    ) {
        // Interpolation function is computed between 0 and 1.
        return now / last ;
    }

} ;
