#include <transitions/interpolations/in_interpolations/BackInInterpolation.h>
#include <Math.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    BackInInterpolation::BackInInterpolation(const Mind::Scalar& overshoot) : m_overshoot(overshoot) {}

    BackInInterpolation::~BackInInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar BackInInterpolation::interpolate(
                                                    const int& last,
                                                    const int& now
                                                   ) {
        // Interpolation function is computed between 0 and 1.
        Mind::Scalar normalizedTime = now / last ;

        return (normalizedTime * normalizedTime)
                    * ((m_overshoot + 1.f) * normalizedTime - m_overshoot) ;
    }

} ;
