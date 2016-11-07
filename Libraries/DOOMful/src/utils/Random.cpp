/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Random.cpp                 */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/13/2016                 */
/* UPDATE:      01/13/2016                 */
/*                                         */
/* Utilities for random numbers.           */
/*******************************************/

#include <utils/Random.h>
#include <stdlib.h>
#include <time.h>


namespace Doom {

    namespace Random {

        /** @brief  Avoid reinitializing  */
        static bool IsInitialized = false ;


        void Initialize(bool force) {
            if (!IsInitialized || force) {
                srand(time(NULL)) ;
                IsInitialized = true ;
            }
        }

        int GetValue() {
            return rand() ;
        }

        int GetRangedValue(const int& min, const int& max) {
            if (min >= max) {
                return 0 ;
            }

            int diff = max - min ;
            int random = (rand() % diff) + min ;
            return random ;
        }

    } ;

} ;
