#include <transitions/interpolations/in_interpolations/ConstantInInterpolation.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ConstantInInterpolation::ConstantInInterpolation() {}

    ConstantInInterpolation::~ConstantInInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar ConstantInInterpolation::interpolate(
                                                      const int&,
                                                      const int&
                                                     ) {
        return 1.f ;
    }

} ;
