#ifndef __SPITE__PNG_FILE__
#define __SPITE__PNG_FILE__

extern "C" {
    #include <stdio.h>
    #include <stddef.h>
    #include <png.h>
}

#include <utils/Platform.hpp>
#include <files/images/ImageFile.hpp>

namespace Spite {

    class RawImage ;

    /**
     * Load a PNG file.
     */
    class PNGFile final : public ImageFile {
        private:
            /**
             * Length of a PNG header.
             */
            static const unsigned char HeaderLength = 8 ;

        public:
            /**
             * Create a new PNGFile.
             * @param   path    Path of the file to open.
             */
            exported PNGFile(const std::string& path) ;

            /**
             * Destruction of the PNGFile.
             */
            exported virtual ~PNGFile() = default ;

            // Remove copy/move operations.
            PNGFile(const PNGFile& copied) = delete;
            PNGFile(PNGFile&& moved) = delete;
            PNGFile& operator=(const PNGFile& copied) = delete;
            PNGFile& operator=(PNGFile&& moved) = delete;

        private:
            /**
             * Parse the JPEG file and store raw data in the RawImage.
             * @param   output  Output the raw data from the JPEG file.
             */
            bool parse(RawImage* output) ;

            /**
             * Initialize the decompression data.
             * @param   pngStruct   Structure used for pure file management
             *                      (inputs, outputs, etc).
             * @param   pngInfo     Structure containing picture informations.
             * @param   filepath    Path to the read file.
             * @return  TRUE on success, FALSE on error.
             */
            bool initializeDecompressionData(
                png_structp& pngStruct,
                png_infop& pngInfo,
                const char* filepath
            ) ;

            /**
             * Start the decompression of the file.
             * @param   pngStruct   Structure used for pure file management
             *                      (inputs, outputs, etc).
             * @param   pngInfo     Structure containing picture informations.
             * @param   output      Output the raw data contained in the file.
             */
            void startDecompression(
                png_structp& pngStruct,
                png_infop& pngInfo,
                RawImage* output
            ) ;

            /**
             * End parsing the file.
             * @param   pngStruct   Structure used for pure file management
             *                      (inputs, outputs, etc).
             * @param   pngInfo     Structure containing picture informations.
             */
            void endParsing(
                png_structp pngStruct,
                png_infop pngInfo
            ) ;

            /**
             * Convert the color type from libPNG to a SPITE ColorFormat object.
             * @param   pngStruct   Structure used for pure file management
             *                      (inputs, outputs, etc).
             * @param   pngInfo     Structure containing picture informations.
             * @param   colorType   Color type value returned by libPNG.
             * @param   output      The output raw image data containing the
             *                      color format.
             * @return  When a conversion is required to output a PNG file with
             *          a RGB or RGBA color format, a factor is returned.
             *          This is the factor of size between original format data
             *          size and output data size.
             *          For example, a gray picture has pixels encoded on
             *          8 bits.
             *          It is converted to a 24-bit pixels picture. So, the
             *          output picture size has pixels encoded on 3 times higher
             *          size than the original pixel size.
             *          The conversion outputs 3.
             * @warning It only handles color types for RGB and RGBA files.
             */
            unsigned int setAndConvertColorFormat(
                png_structp& pngStruct,
                png_infop& pngInfo,
                png_byte& colorType,
                RawImage* output
            ) ;
    } ;
}

#endif
