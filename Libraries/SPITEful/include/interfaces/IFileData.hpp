#ifndef __SPITE__IFILEDATA__
#define __SPITE__IFILEDATA__

#include <utils/Platform.hpp>
#include <vector>

namespace Spite {

    /**
     * Interface for data in main memory.
     */
    class IFileData {
        public:
            /**
             * Get the file raw data.
             * @return  Output the raw data of the file.
             */
            exported virtual std::vector<unsigned char>& data() = 0 ;
    } ;

} ;


#endif
