#include <transitions/interpolations/in_interpolations/BounceInInterpolation.h>
#include <Math.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    BounceInInterpolation::BounceInInterpolation() {}

    BounceInInterpolation::~BounceInInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar BounceInInterpolation::interpolate(
                                                    const int& last,
                                                    const int& now
                                                   ) {
        const Mind::Scalar MagicFactor = 1.f/BounceMagic[0]/BounceMagic[0] ;

        // Interpolation function is computed between 0 and 1.
        Mind::Scalar normalizedTime = 1.f - (now / last) ;
        Mind::Scalar returnedValue ;

        if (normalizedTime < BounceMagic[0]) {
            returnedValue = MagicFactor * normalizedTime * normalizedTime ;
        }
        else if (normalizedTime < BounceMagic[2]) {
            normalizedTime = normalizedTime - BounceMagic[1] ;
            returnedValue = MagicFactor * normalizedTime * normalizedTime + BounceMagic[3] ;
        }
        else if (normalizedTime < BounceMagic[5]) {
            normalizedTime = normalizedTime - BounceMagic[4] ;
            returnedValue = MagicFactor * normalizedTime * normalizedTime + BounceMagic[6] ;
        }
        else {
            normalizedTime = normalizedTime - BounceMagic[7] ;
            returnedValue = normalizedTime * normalizedTime + BounceMagic[8] ;
        }

        return 1.f - returnedValue ;
    }

} ;
