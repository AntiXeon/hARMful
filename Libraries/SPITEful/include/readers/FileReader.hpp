#ifndef __SPITE__FILE_READER__
#define __SPITE__FILE_READER__

#include <fstream>

namespace Spite {

    /**
     * A FileReader is used to read the content of a File.
     */
    class FileReader {
        protected:
            /**
             * The filestream used to parse a file.
             */
            std::fstream* m_stream ;

        public:
            /**
             * Destruction of the FileReader.
             */
            virtual ~FileReader() = default ;

            /**
             * Set the stream of the FileReader.
             * @param   stream  The stream to use.
             */
            void setFileStream(const std::fstream* stream) ;
    } ;
}

#endif
