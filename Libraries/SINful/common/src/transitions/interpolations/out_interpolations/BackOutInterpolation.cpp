#include <transitions/interpolations/out_interpolations/BackOutInterpolation.h>
#include <Math.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    BackOutInterpolation::BackOutInterpolation(const Mind::Scalar& overshoot) : m_overshoot(overshoot) {}

    BackOutInterpolation::~BackOutInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar BackOutInterpolation::interpolate(
                                                     const int& last,
                                                     const int& now
                                                    ) {
        // Interpolation function is computed between 0 and 1.
        Mind::Scalar normalizedTime = now / last ;

        return 1.f - ((normalizedTime * normalizedTime)
                    * ((m_overshoot + 1.f) * normalizedTime - m_overshoot)) ;
    }

} ;
