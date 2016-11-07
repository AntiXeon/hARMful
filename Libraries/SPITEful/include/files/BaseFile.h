#ifndef __SPITE_BASE_FILE__
#define __SPITE_BASE_FILE__


#include <fstream>
#include <exceptions/IOException.h>
#include <exceptions/UnexpectedValueException.h>
#include <readers/FileReader.h>
#include <writers/FileWriter.h>
#include <File.h>
#include <Path.h>


namespace Spite {

    /**
     * @brief   A BaseFile is the representation of a file in file system.
     *          A BaseFile can be saved and loaded.
     *          BaseFile class allows the implementation of reading / saving
     *          algorithms.
     *
     * @author  Denis CARLUS
     * @version 1.0     08/13/2015
     */
    class BaseFile : public File {
        private:
            /**
             * @brief   Inner BaseFile stream to read and/or write data on disk.
             */
            std::fstream m_fs ;

            /** @brief  Mode in which the file has been opened. */
            std::ios_base::openmode m_openMode;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation a BaseFile from a string.
             * @param   filepath    Path to the file to open.
             */
            BaseFile(const std::string& filepath) ;

            /** @brief  Destroy the BaseFile. */
            virtual ~BaseFile() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Open the BaseFile in the given mode.
             * @param   mode    Mode to access BaseFile and perform some
             *                  operations on it.
             */
            void open(File::OpenMode mode) ;

            /** @brief  Close the BaseFile. */
            void close() ;


            /**
             * @brief   Save a data at a given place on disk.
             * @param   filedata    Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path        Path to the location on filesystem.
             */
            bool save(
                      IFileData* filedata,
                      const std::string& path
                     ) throw(Doom::IOException) ;

            /**
             * @brief   Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             */
            bool load(IFileData* filedata) throw(Doom::IOException) ;


        protected:
            /**
             * @brief   Open the BaseFile.
             * @param   mode    Mode to open the BaseFile.
             */
            void open(std::ios_base::openmode mode) throw(Doom::IOException) ;

            /**
             * @brief   Save a data at a given place on disk.
             * @param   filedata    Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path    Path to the location on filesystem.
             */
            virtual bool saveSpecific(
                                      IFileData* filedata,
                                      const std::string& path
                                     ) throw(Doom::IOException) = 0 ;

            /**
             * @brief   Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             */
            virtual bool loadSpecific(IFileData* filedata) throw(Doom::IOException) = 0 ;

            /**
             * @brief   Specific mode to the type of BaseFile.
             * @param   mode    A specific openmode for a type of BaseFile.
             * @return  TRUE if the BaseFile has a specific openmode, FALSE
             *          else.
             */
            virtual bool hasSpecificMode(std::ios_base::openmode& mode) = 0 ;

            /**
             * @brief   Make the subclasses return the FileReader they use.
             *          It is then activated with the inner file stream.
             * @return  The FileReader used by subclasses of File.
             */
            virtual FileReader* defineFileReader() = 0 ;

            /**
             * @brief   Make the subclasses return the FileWriter they use.
             *          It is then activated with the inner file stream.
             * @return  The FileWriter used by subclasses of File.
             */
            virtual FileWriter* defineFileWriter() = 0 ;


        private:
            /**
             * @brief   Convert BaseFile::OpenMode to std::ios_base::openmode.
             * @param   mode    The BaseFile::OpenMode to be converted.
             * @return  The corresponding std::ios_base::openmode.
             */
            std::ios_base::openmode defineOpenMode(File::OpenMode mode) throw(Doom::UnexpectedValueException) ;


                                                     /*** SETTERS / GETTERS ***/
        public:
            /**
             * @brief   Check if the BaseFile instance is valid and can be used.
             * @return  TRUE if the BaseFile instance can be used. FALSE else.
             */
            virtual bool isValid() const = 0 ;

            /**
             * @brief   Check if the BaseFile is open.
             * @return  TRUE if the BaseFile is already open, FALSE else.
             */
            bool isOpen() const ;

            /**
             * @brief   Get the mode in which the BaseFile has been opened on
             *          last time.
             * @return  The access mode of the BaseFile.
             */
            std::ios_base::openmode getOpenMode() const ;

    } ;

} ;

#endif
