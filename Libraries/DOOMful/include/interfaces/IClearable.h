/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Clearable.h                */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	09/01/2015                 */
/* UPDATE:      09/01/2015                 */
/*                                         */
/* A Clearable is an object that can clear */
/* its inner data.                         */
/*******************************************/

#ifndef __DOOM__ICLEARABLE__
#define __DOOM__ICLEARABLE__


namespace Doom {

    /**
     * @brief   Object that can clear its inner data.
     */
    class IClearable {
        public:
            /** @brief  Make the object clear its inner data. */
            virtual void clearInnerData() = 0 ;
    } ;

} ;


#endif
