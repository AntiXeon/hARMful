#include <transitions/interpolations/in_interpolations/SmoothInInterpolation.h>
#include <Math.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    SmoothInInterpolation::SmoothInInterpolation() {}

    SmoothInInterpolation::~SmoothInInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar SmoothInInterpolation::interpolate(
                                                    const int& last,
                                                    const int& now
                                                   ) {
        // Interpolation function is computed between 0 and 1.
        Mind::Scalar normalizedTime = now / last ;
        return (normalizedTime * normalizedTime) ;
    }

} ;
