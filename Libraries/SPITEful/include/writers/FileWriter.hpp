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
             * Create a FileWriter.
             */
            FileWriter() = default ;

            /**
             * Destruction of the FileWriter.
             */
            virtual ~FileWriter() = default ;

            /**
             * Set the stream of the FileWriter.
             * @param   stream  The stream to use.
             */
            void setFileStream(std::fstream* stream) {
                m_stream = stream ;
            }

            // Remove copy/move operations.
            FileWriter(const FileWriter& copied) = default;
            FileWriter(FileWriter&& moved) = default;
            FileWriter& operator=(const FileWriter& copied) = default;
            FileWriter& operator=(FileWriter&& moved) = default;
    } ;
}

#endif
