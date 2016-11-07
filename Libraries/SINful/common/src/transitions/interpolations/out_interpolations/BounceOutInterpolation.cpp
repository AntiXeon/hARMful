#include <transitions/interpolations/out_interpolations/BounceOutInterpolation.h>
#include <Math.h>


namespace Sin {
    const Mind::Scalar BounceOutInterpolation::BounceMagic[10] = {
                                                                  4.f/11.f,
                                                                  6.f/11.f,
                                                                  8.f/11.f,
                                                                  3.f/4.f,
                                                                  9.f/11.f,
                                                                  10.f/11.f,
                                                                  15.f/16.f,
                                                                  21.f/22.f,
                                                                  63.f/64.f
                                                                 } ;


                                              /** CONSTRUCTION / DESTRUCTION **/
    BounceOutInterpolation::BounceOutInterpolation() {}

    BounceOutInterpolation::~BounceOutInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar BounceOutInterpolation::interpolate(
                                                     const int& last,
                                                     const int& now
                                                    ) {
        const Mind::Scalar MagicFactor = 1.f/BounceMagic[0]/BounceMagic[0] ;

        // Interpolation function is computed between 0 and 1.
        Mind::Scalar normalizedTime = now / last ;

        if (normalizedTime < BounceMagic[0]) {
            return MagicFactor * normalizedTime * normalizedTime ;
        }
        else if (normalizedTime < BounceMagic[2]) {
            normalizedTime = normalizedTime - BounceMagic[1] ;
            return MagicFactor * normalizedTime * normalizedTime + BounceMagic[3] ;
        }
        else if (normalizedTime < BounceMagic[5]) {
            normalizedTime = normalizedTime - BounceMagic[4] ;
            return MagicFactor * normalizedTime * normalizedTime + BounceMagic[6] ;
        }
        else {
            normalizedTime = normalizedTime - BounceMagic[7] ;
            return normalizedTime * normalizedTime + BounceMagic[8] ;
        }
    }

} ;
