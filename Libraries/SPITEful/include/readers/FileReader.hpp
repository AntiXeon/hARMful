#ifndef __SPITE__FILE_READER__
#define __SPITE__FILE_READER__

#include <utils/Platform.hpp>
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
             * Create a FileReader.
             */
            exported FileReader() = default ;

            /**
             * Destruction of the FileReader.
             */
            exported virtual ~FileReader() = default ;

            /**
             * Set the stream of the FileReader.
             * @param   stream  The stream to use.
             */
            exported void setFileStream(std::fstream* stream) {
                m_stream = stream ;
            }

            // Remove copy/move operations.
            exported FileReader(const FileReader& copied) = default;
            exported FileReader(FileReader&& moved) = default;
            exported FileReader& operator=(const FileReader& copied) = default;
            exported FileReader& operator=(FileReader&& moved) = default;
    } ;
}

#endif
