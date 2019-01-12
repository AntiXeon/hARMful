#ifndef __SPITE__IMAGE_FILE__
#define __SPITE__IMAGE_FILE__

#include <File.hpp>
#include <interfaces/IFileData.hpp>

namespace Spite {
    /**
     * Base class for a file containing an image.
     */
    class ImageFile : public File {
        private:
            /**
             * File descriptor.
             */
            FILE* m_file ;

            /**
             * Position of the data to read/write in the data buffer.
             */
            unsigned int m_dataPosition ;

        protected:
            /**
             * Create a new ImageFile.
             * @param   path    Path of the file to open.
             * @param   format  Color format used by the image file.
             */
            ImageFile(const std::string& path) ;

            /**
             * Destruction of the ImageFile.
             */
            virtual ~ImageFile() ;

        public:
            /**
             * Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             */
            bool load(IFileData* filedata) ;

            /**
             * Save a data at a given place on disk.
             * @param   output      Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path        Path to the location on filesystem.
             */
            bool save(
                IFileData* output,
                const std::string& path
            ) ;

            // Remove copy/move operations.
            ImageFile(const ImageFile& copied) = delete;
            ImageFile(ImageFile&& moved) = delete;
            ImageFile& operator=(const ImageFile& copied) = delete;
            ImageFile& operator=(ImageFile&& moved) = delete;

        protected:
            /**
             * Open the JPEGFile in the given mode.
             * @param   mode    Mode to access BaseFile and perform some
             *                  operations on it.
             */
            void open(OpenMode mode) ;

            /** @brief  Close the JPEGFile. */
            void close() ;

            /**
             * Parse the image file and store raw data in the @a output data.
             * @param   output  Output the raw data from the image file.
             */
            virtual bool parse(IFileData* output) = 0 ;

        protected:
            /**
             * Get the file descriptor.
             * @return  The descriptor of the file.
             */
            FILE* descriptor() const ;
    } ;
}

#endif
