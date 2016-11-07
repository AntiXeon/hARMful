/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Random.h                   */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/13/2016                 */
/* UPDATE:      01/13/2016                 */
/*                                         */
/* Utilities for random numbers.           */
/*******************************************/

#ifndef __DOOM__RANDOM__
#define __DOOM__RANDOM__

namespace Doom {

    namespace Random {

        /**
         * @brief   Initialize random numbers.
         * @param   force   Force reinitialization of the random generator.
         */
        void Initialize(bool force = false) ;

        /**
         * @brief   Get a value from the random generator.
         * @return  Random value.
         */
        int GetValue() ;

        /**
         * @brief   Get a random value in the given interval.
         * @param   min     Minimal value the random one can have.
         * @param   max     Maximal value the random one can have.
         * @return  Random value in the given interval. Returns 0 if min >= max.
         */
        int GetRangedValue(const int& min, const int& max) ;

    } ;

} ;

#endif
