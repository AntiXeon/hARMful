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
    } ;
}

#endif
