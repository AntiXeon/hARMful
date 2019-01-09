#ifndef __SPITE__IFILEDATA__
#define __SPITE__IFILEDATA__

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
            virtual void data(void*& data, unsigned int& size) = 0 ;

            /**
             * Free data from memory.
             */
            virtual void freeData() = 0 ;
    } ;

} ;


#endif
