#ifndef __SPITE__TEXT_FILE__
#define __SPITE__TEXT_FILE__

#include <utils/Platform.hpp>
#include <files/BaseFile.hpp>
#include <readers/TextFileReader.hpp>
#include <writers/TextFileWriter.hpp>

namespace Spite {

    /**
     * A TextFile is used to read and/or write ASCII data stored on disk.
     */
    class TextFile : public BaseFile {
        private:
            /**
             * The TextFileReader used to read informations from the opened
             * file.
             */
            TextFileReader m_reader ;

            /**
             * The TextFileWriter used to write into the file.
             */
            TextFileWriter m_writer ;

        public:
            /**
             * Creation of a TextFile from a string.
             * @param   filepath    Path to the file to open.
             */
            exported TextFile(const std::string& filepath) ;

            /**
             * Destroy the TextFile.
             */
            exported virtual ~TextFile() = default ;

            /**
             * Check if the File instance is valid and can be used.
             * @return  TRUE if the File instance can be used. FALSE else.
             */
            exported bool isValid() const ;

            // Remove copy/move operations.
            TextFile(const TextFile& copied) = delete;
            TextFile(TextFile&& moved) = delete;
            TextFile& operator=(const TextFile& copied) = delete;
            TextFile& operator=(TextFile&& moved) = delete;

        protected:
            /**
             * Specific mode to the type of File.
             * @param   mode    A specific openmode for a type of File.
             * @return  TRUE if the File has a specific openmode, FALSE else.
             */
            exported bool hasSpecificMode(std::ios_base::openmode& mode) ;

            /**
             * Make the subclasses return the FileReader they use.
             * It is then activated with the inner file stream.
             * @return  The FileReader used by subclasses of File.
             */
            exported FileReader* defineFileReader() ;

            /**
             * Make the subclasses return the FileWriter they use.
             * It is then activated with the inner file stream.
             * @return  The FileWriter used by subclasses of File.
             */
            exported FileWriter* defineFileWriter() ;
    } ;
}

#endif
