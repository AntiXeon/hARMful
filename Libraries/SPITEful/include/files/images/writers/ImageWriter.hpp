#ifndef __SPITE__IMAGE_WRITER__
#define __SPITE__IMAGE_WRITER__

#include <utils/Platform.hpp>
#include <files/images/data/RawImage.hpp>
#include <functional>

namespace Spite {
    /**
     * Dedicated class to store compressed images.
     */
    class ImageWriter {
        public:
            /** Extension of HDR files. */
            static const std::string HDRFileExtension ;

            /** Extension of PNG files. */
            static const std::string PNGFileExtension ;

            /** Extension of JPEG files. */
            static const std::string JPEGFileExtension ;

            /** Extension of JPG files. */
            static const std::string JPGFileExtension ;

            /** Extension of BMP files. */
            static const std::string BMPFileExtension ;

            /** Extension of RLE files. */
            static const std::string RLEFileExtension ;

            /** Extension of SIB files. */
            static const std::string DIBFileExtension ;

            /** Extension of TGA files. */
            static const std::string TGAFileExtension ;

            /** Extension of TPIC files. */
            static const std::string TPICFileExtension ;

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

        protected:
            /**
             * JPEG quality.
             */
            static int JPEGQuality ;

        private:
            /**
             * Data to save.
             */
            std::reference_wrapper<RawImage> m_data ;

            /**
             * true to flip vertically on save; false otherwise.
             */
            bool m_verticalFlip = false ;

        public:
            /**
             * Create a new ImageWriter to write compressed data in a file.
             * @param   data         Binary data containing raw picture data.
             * @param   verticalFlip true to flip vertically; false otherwise.
             */
            exported ImageWriter(
                RawImage& data,
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

        protected:
            /**
             * Perform save.
             */
            virtual exported bool processSpecific() = 0 ;

            /**
             * Get the data to write.
             */
            exported RawImage& data() {
                return m_data.get() ;
            }

            /**
             * true to flip vertically on save; false otherwise.
             */
            exported bool verticalFlip() {
                return m_verticalFlip ;
            }
    } ;
}

#endif
