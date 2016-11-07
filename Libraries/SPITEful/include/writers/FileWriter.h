#ifndef __SPITE_FILE_WRITER__
#define __SPITE_FILE_WRITER__


#include <fstream>


namespace Spite {

    /**
     * @brief   A FileWriter is used to write the content of a File.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/25/2015
     */
    class FileWriter {
        protected:
            /** @brief  The filestream used to parse a file. */
            std::fstream* m_stream ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /** @brief  Creation of a FileWriter. */
            FileWriter() ;

            /** @brief  Destruction of a FileWriter. */
            virtual ~FileWriter() ;


                                                               /*** SETTERS ***/
            /**
             * @brief   Set the stream of the FileWriter.
             * @param   stream  The stream to use.
             */
            void setFileStream(const std::fstream* stream) ;
    } ;

} ;


#endif
