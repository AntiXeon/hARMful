/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Singleton.h                */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/31/2014                 */
/* UPDATE:      03/31/2014                 */
/*                                         */
/* Base class to create singletons.        */
/*******************************************/

#ifndef __DOOM__SINGLETON__
#define __DOOM__SINGLETON__


namespace Doom {

    /**
    * Class to create singletons.
    * @warning No copy into the subclasses.
    * @warning Private inheritage required.
    */
    class Singleton {
        private:
            /** @brief  Disable copy constructor. */
            Singleton(Singleton&) ;

            /** @brief  Disable affectation. */
            void operator= (const Singleton&) ;

        protected:
            /** @brief  Allowed default constructor, only for subclasses. */
            Singleton() throw() ;

            /** @brief  Destruction, only for subclasses. */
            virtual ~Singleton() throw() ;
    } ;

} ;

#endif
