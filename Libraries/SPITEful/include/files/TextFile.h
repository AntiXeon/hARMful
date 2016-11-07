#ifndef __SPITE_TEXT_FILE__
#define __SPITE_TEXT_FILE__


#include <files/BaseFile.h>
#include <readers/TextFileReader.h>
#include <writers/TextFileWriter.h>


namespace Spite {

    /**
     * @brief   A TextFile is used to read and/or write ASCII data stored on
     *          disk.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/23/2015
     */
    class TextFile : public BaseFile {
        private:
            /**
             * @brief   The TextFileReader used to read informations from the
             *          opened file.
             */
            TextFileReader m_reader ;

            /** @brief  The TextFileWriter used to write into the file. */
            TextFileWriter m_writer ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of a TextFile from a string.
             * @param   filepath    Path to the file to open.
             */
            TextFile(const std::string& filepath) ;

            /** @brief  Destroy the TextFile. */
            virtual ~TextFile() ;


                                                               /*** GETTERS ***/
            /**
             * @brief   Check if the File instance is valid and can be used.
             * @return  TRUE if the File instance can be used. FALSE else.
             */
            bool isValid() const ;


                                                             /*** UTILITIES ***/
        protected:
            /**
             * @brief   Specific mode to the type of File.
             * @param   mode    A specific openmode for a type of File.
             * @return  TRUE if the File has a specific openmode, FALSE else.
             */
            bool hasSpecificMode(std::ios_base::openmode& mode) ;

            /**
             * @brief   Make the subclasses return the FileReader they use.
             *          It is then activated with the inner file stream.
             * @return  The FileReader used by subclasses of File.
             */
            FileReader* defineFileReader() ;

            /**
             * @brief   Make the subclasses return the FileWriter they use.
             *          It is then activated with the inner file stream.
             * @return  The FileWriter used by subclasses of File.
             */
            FileWriter* defineFileWriter() ;
    } ;

} ;


#endif
