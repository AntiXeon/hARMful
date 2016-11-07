#include <transitions/interpolations/out_interpolations/ConstantOutInterpolation.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ConstantOutInterpolation::ConstantOutInterpolation() {}

    ConstantOutInterpolation::~ConstantOutInterpolation() {}


                                                             /*** UTILITIES ***/
    Mind::Scalar ConstantOutInterpolation::interpolate(
                                                     const int&,
                                                     const int&
                                                    ) {
        return 0.f ;
    }

} ;
