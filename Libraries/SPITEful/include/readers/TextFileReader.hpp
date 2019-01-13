#ifndef __SPITE__TEXT_FILE_READER__
#define __SPITE__TEXT_FILE_READER__

#include <string>
#include <readers/FileReader.hpp>

namespace Spite {

    /**
     * A TextFileReader is used to read text files.
     */
    class TextFileReader : public FileReader {
        public:
            /**
             * Read a line into the file.
             * @param   text    The line that is read.
             * @return  The line that is read.
             */
            std::string& readLine(std::string& readLine) {
                getline(*m_stream, readLine) ;
                return readLine ;
            }

            /**
             * Read the whole content of a text at once.
             * @param   content Output the whole content of the file.
             */
            void readAll(std::string& content) ;
    } ;
}

#endif
