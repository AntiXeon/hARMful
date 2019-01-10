#ifndef __SPITE__ILOADABLE__
#define __SPITE__ILOADABLE__

#include <interfaces/IFileData.hpp>

namespace Spite {

    /**
     * A Loadable element can be loaded from disk to memory.
     */
    class ILoadable {
        public:
            /**
             * Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             * @return  TRUE on success, FALSE on failure.
             */
            virtual bool load(IFileData* filedata) = 0 ;
    } ;

} ;


#endif
