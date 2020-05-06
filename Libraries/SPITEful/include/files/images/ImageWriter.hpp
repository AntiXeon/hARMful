#ifndef __SPITE__IMAGE_WRITER__
#define __SPITE__IMAGE_WRITER__

#include <utils/Platform.hpp>
#include <files/images/data/RawImage.hpp>
#include <filesystem>
#include <functional>
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

        private:
            using SaveFunctor = std::function<bool(RawImage&, const std::string&)> ;

            /**
             * Extension of HDR files.
             */
            static const std::string HDRFileExtension ;

            /**
             * Bind extensions to their functor to save file on disk.
             */
            static const std::map<std::string, SaveFunctor> ExtensionSave ;

            /**
             * JPEG quality.
             */
            static int JPEGQuality ;

            /**
             * Data to save.
             */
            std::reference_wrapper<RawImage> m_data ;

            /**
             * Path to save the file to.
             */
            std::filesystem::path m_path ;

            /**
             * true to flip vertically on save; false otherwise.
             */
            bool m_verticalFlip = false ;

        public:
            /**
             * Create a new ImageWriter.
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

        private:
            /**
             * Save PNG file.
             * @return  true on success; false otherwise.
             */
            exported static bool SavePNG(
                RawImage& image,
                const std::string& path
            ) ;

            /**
             * Save JPEG file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveJPEG(
                RawImage& image,
                const std::string& path
            ) ;

            /**
             * Save TGA file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveTGA(
                RawImage& image,
                const std::string& path
            ) ;

            /**
             * Save BMP file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveBMP(
                RawImage& image,
                const std::string& path
            ) ;

            /**
             * Save HDR file.
             * @return  true on success; false otherwise.
             */
            exported static bool SaveHDR(
                RawImage& image,
                const std::string& path
            ) ;
    } ;
}

#endif
