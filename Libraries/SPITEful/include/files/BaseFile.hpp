#ifndef __SPITE__BASE_FILE__
#define __SPITE__BASE_FILE__

#include <utils/Platform.hpp>
#include <fstream>
#include <readers/FileReader.hpp>
#include <writers/FileWriter.hpp>
#include <File.hpp>

namespace Spite {

    /**
     * A BaseFile is the representation of a file in file system.
     * A BaseFile can be saved and loaded.
     * BaseFile class allows the implementation of reading / saving algorithms.
     */
    class BaseFile : public File {
        private:
            /**
             * Inner BaseFile stream to read and/or write data on disk.
             */
            std::fstream m_fs ;

            /**
             * Mode in which the file has been opened.
             */
            std::ios_base::openmode m_openMode;

        public:
            /**
             * Creation a BaseFile from a string.
             * @param   filepath    Path to the file to open.
             */
            exported BaseFile(const std::string& filepath) ;

            /**
             * Destroy the BaseFile.
             */
            exported virtual ~BaseFile() ;

            /**
             * Open the BaseFile in the given mode.
             * @param   mode    Mode to access BaseFile and perform some
             *                  operations on it.
             */
            exported void open(File::OpenMode mode) ;

            /**
             * Close the BaseFile.
             */
            exported void close() ;

            /**
             * Save a data at a given place on disk.
             * @param   filedata    Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path        Path to the location on filesystem.
             */
            exported bool save(
                IFileData* filedata,
                const std::string& path
            ) ;

            /**
             * Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             */
            exported bool load(IFileData* filedata) ;

            // Remove copy/move operations.
            BaseFile(const BaseFile& copied) = delete;
            BaseFile(BaseFile&& moved) = delete;
            BaseFile& operator=(const BaseFile& copied) = delete;
            BaseFile& operator=(BaseFile&& moved) = delete;

        protected:
            /**
             * Open the BaseFile.
             * @param   mode    Mode to open the BaseFile.
             */
            exported void open(std::ios_base::openmode mode) ;

            /**
             * Save a data at a given place on disk.
             * @param   filedata    Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path    Path to the location on filesystem.
             */
            exported virtual bool saveSpecific(
                IFileData* filedata,
                const std::string& path
            ) = 0 ;

            /**
             * Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             */
            exported virtual bool loadSpecific(IFileData* filedata) = 0 ;

            /**
             * Specific mode to the type of BaseFile.
             * @param   mode    A specific openmode for a type of BaseFile.
             * @return  TRUE if the BaseFile has a specific openmode, FALSE
             *          else.
             */
            exported virtual bool hasSpecificMode(std::ios_base::openmode& mode) = 0 ;

            /**
             * Make the subclasses return the FileReader they use.
             * It is then activated with the inner file stream.
             * @return  The FileReader used by subclasses of File.
             */
            exported virtual FileReader* defineFileReader() = 0 ;

            /**
             * Make the subclasses return the FileWriter they use.
             * It is then activated with the inner file stream.
             * @return  The FileWriter used by subclasses of File.
             */
            exported virtual FileWriter* defineFileWriter() = 0 ;

        private:
            /**
             * Convert BaseFile::OpenMode to std::ios_base::openmode.
             * @param   mode    The BaseFile::OpenMode to be converted.
             * @return  The corresponding std::ios_base::openmode.
             */
            std::ios_base::openmode defineOpenMode(File::OpenMode mode) ;

        public:
            /**
             * Check if the BaseFile instance is valid and can be used.
             * @return  TRUE if the BaseFile instance can be used. FALSE else.
             */
            exported virtual bool isValid() const = 0 ;

            /**
             * Check if the BaseFile is open.
             * @return  TRUE if the BaseFile is already open, FALSE else.
             */
            exported bool isOpen() const ;

            /**
             * Get the mode in which the BaseFile has been opened on last time.
             * @return  The access mode of the BaseFile.
             */
            exported std::ios_base::openmode openMode() const ;

    } ;
}

#endif
