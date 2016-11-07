#ifndef __SPITE_ISAVABLE__
#define __SPITE_ISAVABLE__


#include <interfaces/IFileData.h>
#include <exceptions/IOException.h>


namespace Spite {

    /**
     * @brief   A Savable element can be saved on disk as a file.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/13/2015
     */
    class ISavable {
        public:
            /**
             * @brief   Save a data at a given place on disk.
             * @param   filedata    Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path        Path to the location on filesystem.
             * @return  TRUE on success, FALSE on failure.
             */
            virtual bool save(
                              IFileData* filedata,
                              const std::string& path
                             ) throw(Doom::IOException) = 0 ;
    } ;

} ;


#endif
