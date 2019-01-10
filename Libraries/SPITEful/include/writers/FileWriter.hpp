#ifndef __SPITE__FILE_WRITER__
#define __SPITE__FILE_WRITER__

#include <fstream>

namespace Spite {

    /**
     * A FileWriter is used to write the content of a File.
     */
    class FileWriter {
        protected:
            /**
             * The filestream used to parse a file.
             */
            std::fstream* m_stream ;

        public:
            /**
             * Set the stream of the FileWriter.
             * @param   stream  The stream to use.
             */
            void setFileStream(std::fstream* stream) {
                m_stream = stream ;
            }
    } ;
}

#endif
