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

#include <patterns/Iterator/Iterator.h>
#include <debug/Test.h>


namespace Doom {

    Iterator::Iterator(Iterable* collection) {
        m_collection = collection ;
    }

    Iterator::~Iterator() {}

} ;
