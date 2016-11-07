#include <transitions/interpolations/out_interpolations/SmoothOutInterpolation.h>
#include <Math.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    SmoothOutInterpolation::SmoothOutInterpolation() {}

    SmoothOutInterpolation::~SmoothOutInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar SmoothOutInterpolation::interpolate(
                                                     const int& last,
                                                     const int& now
                                                    ) {
        // Interpolation function is computed between 0 and 1.
        Mind::Scalar normalizedTime = now / last ;
        return ((-normalizedTime) * (normalizedTime - 2.f)) ;
    }

} ;
