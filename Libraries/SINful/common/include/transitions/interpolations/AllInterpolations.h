#ifndef __SIN_ALL_INTERPOLATIONS__
#define __SIN_ALL_INTERPOLATIONS__


#include <vector>

#include <transitions/interpolations/in_interpolations/BackInInterpolation.h>
#include <transitions/interpolations/in_interpolations/BounceInInterpolation.h>
#include <transitions/interpolations/in_interpolations/ConstantInInterpolation.h>
#include <transitions/interpolations/in_interpolations/ElasticInInterpolation.h>
#include <transitions/interpolations/in_interpolations/LinearInInterpolation.h>
#include <transitions/interpolations/in_interpolations/SmoothInInterpolation.h>

#include <transitions/interpolations/out_interpolations/BackOutInterpolation.h>
#include <transitions/interpolations/out_interpolations/BounceOutInterpolation.h>
#include <transitions/interpolations/out_interpolations/ConstantOutInterpolation.h>
#include <transitions/interpolations/out_interpolations/ElasticOutInterpolation.h>
#include <transitions/interpolations/out_interpolations/LinearOutInterpolation.h>
#include <transitions/interpolations/out_interpolations/SmoothOutInterpolation.h>


namespace Sin {

    /**
     * @brief   Aggregation of all the available interpolations for transitions.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/22
     */
    class AllInterpolations {
        public:
            /** @brief  Interpolations for entering animation. */
            enum InterpolationType {
                // IN interpolations
                IN_Back,
                IN_Bounce,
                IN_Constant,
                IN_Elastic,
                IN_Linear,
                IN_Smooth,
                // OUT interpolations
                OUT_Back,
                OUT_Bounce,
                OUT_Constant,
                OUT_Elastic,
                OUT_Linear,
                OUT_Smooth,
                TotalInterpolationTypes
            } ;

        private:
            /**
             * @brief   List of all available interpolations.
             */
            std::vector<IInterpolation*> m_interpolations ;

        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of an aggregation of interpolations.
             */
            AllInterpolations() ;

            /**
             * @brief   Destruction of all the interpolations.
             */
            virtual ~AllInterpolations() ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the wanted interpolation.
             */
            IInterpolation* get(const InterpolationType& type) const ;
    } ;

} ;


#endif
