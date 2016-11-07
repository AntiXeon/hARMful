#include <transitions/TransparencyTransition.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    TransparencyTransition::TransparencyTransition(
                                                   const int& last,
                                                   IInterpolation* interpolation
                                                  ) : AbstractTransition(last, interpolation) {}

    TransparencyTransition::~TransparencyTransition() {}


                                                             /*** UTILITIES ***/
    void TransparencyTransition::compute(
                                         const void* start,
                                         const void* end,
                                         void* result
                                        ) {
        Mind::Scalar transitionFactorStart = getInterpolation() ;
        Mind::Scalar transitionFactorEnd = 1.f - transitionFactorStart ;

        int startTransp = *((int*) start) ;
        int endTransp = *((int*) end) ;

        int* resultingTransp = (int*) result ;
        *resultingTransp = (startTransp * transitionFactorStart)
                            + (endTransp * transitionFactorEnd) ;
    }

} ;
