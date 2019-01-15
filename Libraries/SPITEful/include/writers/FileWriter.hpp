#ifndef __SPITE__FILE_WRITER__
#define __SPITE__FILE_WRITER__

#include <utils/Platform.hpp>
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
             * Create a FileWriter.
             */
            exported FileWriter() = default ;

            /**
             * Destruction of the FileWriter.
             */
            exported virtual ~FileWriter() = default ;

            /**
             * Set the stream of the FileWriter.
             * @param   stream  The stream to use.
             */
            exported void setFileStream(std::fstream* stream) {
                m_stream = stream ;
            }

            // Remove copy/move operations.
            exported FileWriter(const FileWriter& copied) = default;
            exported FileWriter(FileWriter&& moved) = default;
            exported FileWriter& operator=(const FileWriter& copied) = default;
            exported FileWriter& operator=(FileWriter&& moved) = default;
    } ;
}

#endif
