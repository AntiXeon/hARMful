#include <transitions/RotationTransition.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    RotationTransition::RotationTransition(
                                           const int& last,
                                           IInterpolation* interpolation
                                          ) : AbstractTransition(last, interpolation) {}

    RotationTransition::~RotationTransition() {}


                                                             /*** UTILITIES ***/
    void RotationTransition::compute(
                                     const void* start,
                                     const void* end,
                                     void* result
                                    ) {
        Mind::Scalar transitionFactorStart = getInterpolation() ;
        Mind::Scalar transitionFactorEnd = 1.f - transitionFactorStart ;

        Mind::Scalar startRotation = *((Mind::Scalar*) start) ;
        Mind::Scalar endRotation = *((Mind::Scalar*) end) ;

        Mind::Scalar* resultingRotation = (Mind::Scalar*) result ;
        *resultingRotation = (startRotation * transitionFactorStart)
                                + (endRotation * transitionFactorEnd) ;
    }

} ;
