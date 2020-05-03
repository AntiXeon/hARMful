#ifndef __SPITE__IMAGE_FILE__
#define __SPITE__IMAGE_FILE__

#include <utils/Platform.hpp>
#include <File.hpp>
#include <files/images/data/RawImage.hpp>

namespace Spite {
    /**
     * Base class for a file containing an image.
     */
    class ImageFile final : public File {
        private:
            static const float GammaCorrection ;
            static const float HDRScale ;

            /**
             * true to flip the texture on load; false otherwise.
             */
            bool m_flip = false ;

        public:
            /**
             * Create a new ImageFile.
             * @param   path    Path of the file to open.
             * @param   flip    true to flip the texture on load;
             *                  false otherwise.
             */
            exported ImageFile(
                const std::string& path,
                const bool flip = true
            ) ;

            /**
             * Load a data at a given place on disk.
             * @param   filedata        File data to store data in.
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

            /**
             * Resize a picture to the wanted size.
             * @param   original    Original picture data.
             * @param   width       Width of th output resized picture.
             * @param   height      Height of th output resized picture.
             * @return  Resized picture.
             */
            exported static RawImage Resize(
                RawImage& original,
                const unsigned int width,
                const unsigned int height
            ) ;

        private:
            /**
             * Check if the file must be flipped on load,
             * based on file extension name.
             */
            exported void checkFlipOnLoad();

            /**
             * Open the File in the given mode.
             * @param   mode    Mode to access File and perform some
             *                  operations on it.
             */
            exported void open(OpenMode) override {}

            /**
             * Close the File.
             */
            exported void close() override {}
    } ;
}

#endif
