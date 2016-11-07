#include <transitions/interpolations/AllInterpolations.h>
#include <CommonSINStrings.h>
#include <debug/Test.h>
#include <debug/Log.h>
#include <stddef.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    AllInterpolations::AllInterpolations() {
        m_interpolations.resize(TotalInterpolationTypes) ;

        // IN interpolations
        m_interpolations[IN_Back]           = new BackInInterpolation() ;
        m_interpolations[IN_Bounce]         = new BounceInInterpolation() ;
        m_interpolations[IN_Constant]       = new ConstantInInterpolation() ;
        m_interpolations[IN_Elastic]        = new ElasticInInterpolation() ;
        m_interpolations[IN_Linear]         = new LinearInInterpolation() ;
        m_interpolations[IN_Smooth]         = new SmoothInInterpolation() ;
        // OUT interpolations
        m_interpolations[OUT_Back]          = new BackOutInterpolation() ;
        m_interpolations[OUT_Bounce]        = new BounceOutInterpolation() ;
        m_interpolations[OUT_Constant]      = new ConstantOutInterpolation() ;
        m_interpolations[OUT_Elastic]       = new ElasticOutInterpolation() ;
        m_interpolations[OUT_Linear]        = new LinearOutInterpolation() ;
        m_interpolations[OUT_Smooth]        = new SmoothOutInterpolation() ;
    }

    AllInterpolations::~AllInterpolations() {
        for (unsigned int index = 0 ; index < TotalInterpolationTypes ; ++index) {
            if (m_interpolations[index] != NULL) {
                delete m_interpolations[index] ;
            }
        }
        m_interpolations.clear() ;
    }


                                                     /*** SETTERS / GETTERS ***/
    IInterpolation* AllInterpolations::get(const InterpolationType& type) const {
        ABORT_CONDITION(
                        (type < TotalInterpolationTypes),
                        InterpolationMsg::Error::IndexOutOfBounds
                       ) ;

        return m_interpolations[type] ;
    }

} ;
