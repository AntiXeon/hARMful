#ifndef __SPITE_FILE_READER__
#define __SPITE_FILE_READER__


#include <fstream>


namespace Spite {

    /**
     * @brief   A FileReader is used to read the content of a File.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/23/2015
     */
    class FileReader {
        protected:
            /** @brief  The filestream used to parse a file. */
            std::fstream* m_stream ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /** @brief  Creation of a FileReader. */
            FileReader() ;

            /** @brief  Destruction of a FileReader. */
            virtual ~FileReader() ;


                                                               /*** SETTERS ***/
            /**
             * @brief   Set the stream of the FileReader.
             * @param   stream  The stream to use.
             */
            void setFileStream(const std::fstream* stream) ;
    } ;

} ;


#endif
