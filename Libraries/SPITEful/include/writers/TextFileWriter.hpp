#ifndef __SPITE__TEXT_FILE_WRITER__
#define __SPITE__TEXT_FILE_WRITER__

#include <utils/Platform.hpp>
#include <string>
#include <writers/FileWriter.hpp>

namespace Spite {

    /**
     * A TextFileWriter is used to write text files.
     */
    class TextFileWriter : public FileWriter {
        public:
            /**
             * Read a line from the file.
             * @param   text    The text to write.
             */
            exported void write(const std::string& text) {
                (*m_stream) << text ;
            }
    } ;
}

#endif
