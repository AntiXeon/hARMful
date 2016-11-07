/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Iterator.h                 */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	04/08/2014                 */
/* UPDATE:      04/08/2014                 */
/*                                         */
/* Iterator interface to easily access     */
/* collections.                            */
/*******************************************/

#ifndef __DOOM__ITERATOR__
#define __DOOM__ITERATOR__

#include <patterns/Iterator/Iterable.h>
#include <utils/Mutex.h>


namespace Doom {

    /**
     * @brief   Class to create iterators.
     */
    class Iterator {
        protected:
            /** @brief  The collection the iterator is applied to. */
            Iterable* m_collection ;

            /** @brief  Limit concurrent access to the iterator. */
            Mutex m_accessIterator ;


        public:
            /** @brief  Create an iterator on an iterable collection. */
            Iterator(Iterable* collection) ;

            /** @brief  Destruction of the iterator. */
            virtual ~Iterator() ;


            /** @brief  To know if the collection has new element next. */
            virtual bool hasNext() = 0 ;
    } ;

} ;


#endif
