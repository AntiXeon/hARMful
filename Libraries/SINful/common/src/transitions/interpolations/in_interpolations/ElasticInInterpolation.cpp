#include <transitions/interpolations/in_interpolations/ElasticInInterpolation.h>
#include <Math.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ElasticInInterpolation::ElasticInInterpolation() {}

    ElasticInInterpolation::~ElasticInInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar ElasticInInterpolation::interpolate(
                                                    const int& last,
                                                    const int& now
                                                   ) {
        // Interpolation function is computed between 0 and 1.
        Mind::Scalar normalizedTime = now / last ;
        return 1.1545f * (pow(2.f, 10.f * (normalizedTime - 1.f)) *
                                sin((normalizedTime * (2.f * Mind::Math::PI / 0.3f)))) ;
    }

} ;
