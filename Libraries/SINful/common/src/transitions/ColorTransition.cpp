#include <transitions/ColorTransition.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    ColorTransition::ColorTransition(
                                     const int& last,
                                     IInterpolation* interpolation
                                    ) : AbstractTransition(last, interpolation) {}

    ColorTransition::~ColorTransition() {}


                                                             /*** UTILITIES ***/
    void ColorTransition::compute(
                                  const void* start,
                                  const void* end,
                                  void* result
                                 ) {
        Mind::Scalar transitionFactorStart = getInterpolation() ;
        Mind::Scalar transitionFactorEnd = 1.f - transitionFactorStart ;

        PixelColor* startColor = (PixelColor*) start ;
        PixelColor* endColor = (PixelColor*) end ;

        int redTransition = (startColor -> getRed() * transitionFactorStart) +
                                (endColor -> getRed() * transitionFactorEnd) ;
        int greenTransition = (startColor -> getGreen() * transitionFactorStart) +
                                (endColor -> getGreen() * transitionFactorEnd) ;
        int blueTransition = (startColor -> getBlue() * transitionFactorStart) +
                                (endColor -> getBlue() * transitionFactorEnd) ;

        PixelColor* resultingColor = (PixelColor*) result ;
        resultingColor -> setColor(
                                   redTransition,
                                   greenTransition,
                                   blueTransition
                                  ) ;
    }

} ;
