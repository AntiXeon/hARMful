#ifndef __SPITE__BINARY_FILE__
#define __SPITE__BINARY_FILE__

#include <files/BaseFile.hpp>

namespace Spite {

    class BinaryFileReader ;
    class BinaryFileWriter ;

    /**
     * A BinaryFile is used to read and/or write binary data stored on disk.
     */
    class BinaryFile : public BaseFile {
        protected:
            /**
             * Reader used to parse the BinaryFile.
             */
            BinaryFileReader* m_reader = nullptr ;

            /**
             * Writer used to write into the BinaryFile.
             */
            BinaryFileWriter* m_writer = nullptr ;


        public:
            /**
             * Creation of a BinaryFile from a string.
             * @param   filepath    Path to the file to open.
             * @param   isCPUEndian Indicate by TRUE that the file has the same
             *                      endianness than the CPU, FALSE if it is the
             *                      reversed endianness.
             */
            BinaryFile(const std::string& filepath, const bool isCPUEndian) ;

            /**
             * Destroy the BinaryFile.
             */
            virtual ~BinaryFile() ;

        protected:
            /**
             * Specific mode to the type of File.
             * @param   mode    A specific openmode for a type of File.
             * @return  TRUE if the File has a specific openmode, FALSE else.
             */
            bool hasSpecificMode(std::ios_base::openmode& mode) ;

            /**
             * Make the subclasses return the FileReader they use.
             * It is then activated with the inner file stream.
             * @return  The FileReader used by subclasses of File.
             */
            FileReader* defineFileReader() ;

            /**
             * Make the subclasses return the FileWriter they use.
             * It is then activated with the inner file stream.
             * @return  The FileWriter used by subclasses of File.
             */
            FileWriter* defineFileWriter() ;

        public:
            /**
             * Check if the File instance is valid and can be used.
             * @return  TRUE if the File instance can be used. FALSE else.
             */
            bool isValid() const ;

    } ;
}

#endif
