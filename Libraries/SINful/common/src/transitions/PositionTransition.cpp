#include <transitions/PositionTransition.h>
#include <geometry/points/Point2Df.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    PositionTransition::PositionTransition(
                                           const int& last,
                                           IInterpolation* interpolation
                                          ) : AbstractTransition(last, interpolation) {}

    PositionTransition::~PositionTransition() {}


                                                             /*** UTILITIES ***/
    void PositionTransition::compute(
                                     const void* start,
                                     const void* end,
                                     void* result
                                    ) {
        Mind::Scalar transitionFactorStart = getInterpolation() ;
        Mind::Scalar transitionFactorEnd = 1.f - transitionFactorStart ;

        Mind::Point2Df* startPosition = (Mind::Point2Df*) start ;
        Mind::Point2Df* endPosition = (Mind::Point2Df*) end ;

        Mind::Point2Df* resultingPosition = (Mind::Point2Df*) result ;
        resultingPosition -> set((*startPosition * transitionFactorStart)
                                    + (*endPosition * transitionFactorEnd)) ;
    }

} ;
