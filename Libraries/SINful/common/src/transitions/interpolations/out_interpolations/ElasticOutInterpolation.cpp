#include <transitions/interpolations/out_interpolations/ElasticOutInterpolation.h>
#include <Math.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ElasticOutInterpolation::ElasticOutInterpolation() {}

    ElasticOutInterpolation::~ElasticOutInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar ElasticOutInterpolation::interpolate(
                                                     const int& last,
                                                     const int& now
                                                    ) {
        // Interpolation function is computed between 0 and 1.
        Mind::Scalar normalizedTime = now / last ;
        return pow(2.f, -10.f * normalizedTime) * sin((normalizedTime * (2.f * Mind::Math::PI / 0.3f))) ;
    }

} ;
