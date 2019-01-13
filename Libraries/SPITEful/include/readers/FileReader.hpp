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
             * Create a FileReader.
             */
            FileReader() = default ;

            /**
             * Destruction of the FileReader.
             */
            virtual ~FileReader() = default ;

            /**
             * Set the stream of the FileReader.
             * @param   stream  The stream to use.
             */
            void setFileStream(std::fstream* stream) {
                m_stream = stream ;
            }

            // Remove copy/move operations.
            FileReader(const FileReader& copied) = default;
            FileReader(FileReader&& moved) = default;
            FileReader& operator=(const FileReader& copied) = default;
            FileReader& operator=(FileReader&& moved) = default;
    } ;
}

#endif
