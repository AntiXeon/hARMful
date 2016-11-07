#include <transitions/SizeTransition.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    SizeTransition::SizeTransition(
                                   const int& last,
                                   IInterpolation* interpolation
                                  ) : AbstractTransition(last, interpolation) {}

    SizeTransition::~SizeTransition() {}


                                                             /*** UTILITIES ***/
    void SizeTransition::compute(
                                 const void* start,
                                 const void* end,
                                 void* result
                                ) {
        Mind::Scalar transitionFactorStart = getInterpolation() ;
        Mind::Scalar transitionFactorEnd = 1.f - transitionFactorStart ;

        Mind::Scalar startSize = *((Mind::Scalar*) start) ;
        Mind::Scalar endSize = *((Mind::Scalar*) end) ;

        Mind::Scalar* resultingSize = (Mind::Scalar*) result ;
        *resultingSize = (startSize * transitionFactorStart)
                            + (endSize * transitionFactorEnd) ;
    }

} ;
