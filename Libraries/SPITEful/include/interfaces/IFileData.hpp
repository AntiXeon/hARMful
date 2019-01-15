#ifndef __SPITE__IFILEDATA__
#define __SPITE__IFILEDATA__

#include <utils/Platform.hpp>

namespace Spite {

    /**
     * Interface for data in main memory.
     */
    class IFileData {
        public:
            /**
             * Get the file raw data.
             * @param   data    Output the raw data of the file.
             * @param   size    Output the size of the file @a data.
             */
            exported virtual void data(unsigned char*& data, unsigned int& size) = 0 ;

            /**
             * Free data from memory.
             */
            exported virtual void freeData() = 0 ;
    } ;

} ;


#endif
