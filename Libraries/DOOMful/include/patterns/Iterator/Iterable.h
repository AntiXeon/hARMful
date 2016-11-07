/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Iterable.h                 */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	04/08/2014                 */
/* UPDATE:      04/08/2014                 */
/*                                         */
/* Iterable collections can be used with   */
/* an Iterator object.                     */
/*******************************************/

#ifndef __DOOM__ITERABLE__
#define __DOOM__ITERABLE__


#include <utils/Mutex.h>


namespace Doom {

    /**
     * @brief   Class to create iterable collections.
     */
    class Iterable {
        protected:
            /** @brief  Limit concurrent access to the collection. */
            Mutex m_accessCollection ;


        public:
            /** @brief  Create an iterable collection. */
            Iterable() ;

            /** @brief  Destruction of the collection. */
            virtual ~Iterable() ;
    } ;

} ;


#endif
