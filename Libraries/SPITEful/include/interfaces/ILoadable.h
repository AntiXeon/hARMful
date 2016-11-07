#ifndef __SPITE_ILOADABLE__
#define __SPITE_ILOADABLE__


#include <interfaces/IFileData.h>
#include <exceptions/IOException.h>


namespace Spite {

    /**
     * @brief   A Loadable element can be loaded from disk to memory.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/13/2015
     */
    class ILoadable {
        public:
            /**
             * @brief   Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             * @return  TRUE on success, FALSE on failure.
             */
            virtual bool load(IFileData* filedata) throw(Doom::IOException) = 0 ;
    } ;

} ;


#endif
