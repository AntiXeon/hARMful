#ifndef __SPITE__IMAGE_FILE__
#define __SPITE__IMAGE_FILE__

#include <utils/Platform.hpp>
#include <File.hpp>
#include <files/images/data/RawImage.hpp>

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
            exported ImageFile(const std::string& path) ;

            /**
             * Destruction of the ImageFile.
             */
            exported virtual ~ImageFile() ;

        public:
            /**
             * Open the JPEGFile in the given mode.
             * @param   mode    Mode to access BaseFile and perform some
             *                  operations on it.
             */
            exported void open(OpenMode mode) ;

            /**
             * Close the JPEGFile.
             */
            exported void close() ;

            /**
             * Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             */
            exported bool load(IFileData* filedata) ;

            /**
             * Save a data at a given place on disk.
             * @param   output      Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path        Path to the location on filesystem.
             */
            exported bool save(
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
             * Parse the image file and store raw data in the @a output data.
             * @param   output  Output the raw data from the image file.
             */
            exported virtual bool parse(RawImage* output) = 0 ;

            /**
             * Get the file descriptor.
             * @return  The descriptor of the file.
             */
            exported FILE* descriptor() const ;
    } ;
}

#endif
