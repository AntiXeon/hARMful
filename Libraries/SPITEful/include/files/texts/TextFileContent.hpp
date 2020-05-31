#ifndef __SPITE__BASE_FILE__
#define __SPITE__BASE_FILE__

#include <utils/Platform.hpp>
#include <readers/TextFileReader.hpp>
#include <writers/TextFileWriter.hpp>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem ;

namespace Spite {

    /**
     * Read and write text content from disk.
     */
    class TextFileContent {
        private:
            /**
             * Path to the file.
             */
            fs::path m_path ;

            /**
             * Inner TextFile stream to read and/or write data on disk.
             */
            std::fstream m_fs ;

            /**
             * The TextFileReader used to read informations from the opened
             * file.
             */
            TextFileReader m_reader ;

            /**
             * The TextFileWriter used to write into the file.
             */
            TextFileWriter m_writer ;

            /**
             * Mode in which the file has been opened.
             */
            std::ios_base::openmode m_stdOpenMode;

        public:
            /**
             * Creation a TextFileContent.
             * @param   filepath    Path to the file to open.
             */
            exported TextFileContent(const std::string& filepath) ;

            /**
             * Destroy the TextFileContent.
             */
            exported virtual ~TextFileContent() ;

            /**
             * Save a data at a given place on disk.
             * @param text  Text to save in the file.
             */
            exported void save(const std::string& text) ;

            /**
             * Load a data at a given place on disk.
             * @return Content of the file.
             */
            exported std::string load() ;

        protected:
            /**
             * Open the TextFile.
             * @param   mode    Mode to open the TextFile.
             */
            exported void open_fs(std::ios_base::openmode mode) ;

        private:
            // Remove copy/move operations.
            TextFileContent(const TextFileContent& copied) = delete ;
            TextFileContent(TextFileContent&& moved) = delete ;
            TextFileContent& operator=(const TextFileContent& copied) = delete ;
            TextFileContent& operator=(TextFileContent&& moved) = delete ;
    } ;
}

#endif
