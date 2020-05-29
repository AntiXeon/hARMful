#ifndef __SPITE__IMAGE_WRITER__
#define __SPITE__IMAGE_WRITER__

#include <utils/Platform.hpp>
#include <files/images/data/RawImage.hpp>
#include <files/images/save/FileSave.hpp>
#include <files/images/save/BufferSave.hpp>
#include <filesystem>
#include <map>
#include <string>

namespace Spite {
    /**
     * Dedicated class to save images on disk.
     */
    class ImageWriter final {
        public:
            /**
             * Filter algorithms on data for optimum compression.
             */
            enum PNGFilter {
                None,
                Sub,
                Up,
                Average,
                Paeth
            } ;

            /**
             * Output type.
             * - File to write compressed data on disk;
             * - Buffer to write compressed data in a memory buffer.
             */
            enum class Output {
                File,
                Buffer
            } ;

        private:
            /**
             * Extension of HDR files.
             */
            static const std::string HDRFileExtension ;

            /**
             * Bind extensions to their functor to save file on disk.
             */
            static const std::map<std::string, Image::FileSave::Functor> ExtensionFileSave ;

            /**
             * Bind extensions to their functor to store compressed image in
             * memory.
             */
            static const std::map<std::string, Image::BufferSave::Functor> ExtensionBufferSave ;

            /**
             * JPEG quality.
             */
            static int JPEGQuality ;

            /**
             * Output type.
             */
            Output m_output ;

            /**
             * Data to save.
             */
            std::reference_wrapper<RawImage> m_data ;

            /**
             * Path to save the file to.
             */
            std::filesystem::path m_path ;

            /**
             * Buffer to write data in memory.
             */
            std::vector<unsigned char>* m_buffer = nullptr ;

            /**
             * true to flip vertically on save; false otherwise.
             */
            bool m_verticalFlip = false ;

        public:
            /**
             * Create a new ImageWriter to write compressed data in a file.
             * @param   data         Binary data containing raw picture data.
             * @param   path         Path of the file to save to.
             * @param   verticalFlip true to flip vertically; false otherwise.
             */
            exported ImageWriter(
                RawImage& data,
                const std::filesystem::path& path,
                const bool verticalFlip = false
            ) ;

            /**
             * Create a new ImageWriter to write compressed data in memory.
             * @param   data         Binary data containing raw picture data.
             * @param   buffer       Buffer to write data in memory.
             * @param   verticalFlip true to flip vertically; false otherwise.
             */
            exported ImageWriter(
                RawImage& data,
                std::vector<unsigned char>& buffer,
                const bool verticalFlip = false
            ) ;

            /**
             * Perform save.
             */
            exported bool process() ;

            /**
             * Set the PNG compression level. Default is 8.
             * @param   level   Compression level between 0 (no compression) and
             *                  9 (highly compressed).
             */
            exported static void SetPNGCompressionLevel(const int level) ;

            /**
             * Set the PNG filter, applied before compression. Default is None.
             * @param   filter  Filter algorithms on data for optimum
             *                  compression.
             */
            exported static void SetPNGFilter(const PNGFilter filter) ;

            /**
             * Set the JPEG quality. Default is 90.
             * @param   quality     JPEG quality between 1 (highly compressed
             *                      but ugly) and 100 (nice image but heavier
             *                      on disk).
             */
            exported static void SetJPEGQuality(const int quality) ;

            /**
             * Write TGA files with RLE compression. Default is true.
             * @param   rleEnabled  true to enable; false otherwise.
             */
            exported static void SetCompressTGAWithRLE(const bool rleEnabled) ;
    } ;
}

#endif
