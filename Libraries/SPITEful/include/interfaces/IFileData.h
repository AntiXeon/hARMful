#ifndef __SPITE_INTERFACE_FILE_DATA__
#define __SPITE_INTERFACE_FILE_DATA__


namespace Spite {

    /**
     * @brief   Interface for data in main memory.
     *
     * @author  Denis CARLUS
     * @version 1.0     03/09/2016
     */
    class IFileData {
        public:
            /**
             * @brief   Destruction of the IFileData.
             */
            virtual ~IFileData() {}


            /**
             * @brief   Get the file raw data.
             * @param   data    Output the raw data of the file.
             * @param   size    Output the size of the file @a data.
             */
            virtual void getData(void*& data, unsigned int& size) = 0 ;

            /**
             * @brief   Free data from memory.
             */
            virtual void freeData() = 0 ;
    } ;

} ;


#endif
