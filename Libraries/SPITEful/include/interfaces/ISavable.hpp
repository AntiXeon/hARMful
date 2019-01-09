#ifndef __SPITE__ISAVABLE__
#define __SPITE__ISAVABLE__

#include <interfaces/IFileData.hpp>
#include <exceptions/IOException.hpp>

namespace Spite {

    /**
     * A Savable element can be saved on disk as a file.
     */
    class ISavable {
        public:
            /**
             * Save a data at a given place on disk.
             * @param   filedata    Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path        Path to the location on filesystem.
             * @return  TRUE on success, FALSE on failure.
             */
            virtual bool save(
                IFileData* filedata,
                const std::string& path
            ) = 0 ;
    } ;

} ;


#endif
