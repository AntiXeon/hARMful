#ifndef __SPITE__JPEG_FILE__
#define __SPITE__JPEG_FILE__

extern "C" {
    #include <stdio.h>
    #include <stddef.h>
    #include <jpeglib.h>
}

#include <utils/Platform.hpp>
#include <files/images/ImageFile.hpp>

namespace Spite {

    /**
     * Load a JPEG file using libjpeg.
     */
    class JPEGFile final : public ImageFile {
        private:
            /**
             * true to read the picture in bottom-up order; false otherwise.
             */
            bool m_bottomUp = false ;

        public:
            /**
             * Create a new JPEGFile.
             * @param   path    Path of the file to open.
             */
            exported JPEGFile(const std::string& path) ;

            /**
             * Destruction of the JPEGFile.
             */
            exported virtual ~JPEGFile() = default ;

            // Remove copy/move operations.
            JPEGFile(const JPEGFile& copied) = delete;
            JPEGFile(JPEGFile&& moved) = delete;
            JPEGFile& operator=(const JPEGFile& copied) = delete;
            JPEGFile& operator=(JPEGFile&& moved) = delete;

        private:
            /**
             * Parse the JPEG file and store raw data in the RawImage.
             * @param   output  Output the raw data from the JPEG file.
             */
            bool parse(RawImage* output) override ;

            /**
             * Initialize the decompression data.
             * @param   cinfo   Informations required for decompressing the
             *                  @input file.
             * @param   input   Input file to decompress.
             * @return  TRUE on success, FALSE on error.
             */
            bool initializeDecompressionData(
                jpeg_decompress_struct& cinfo,
                FILE* input
            ) ;

            /**
             * Start the decompression of the file.
             * @param   cinfo       Informations required for decompressing the
             *                      file.
             * @param   rowStride   Length of a row in the image.
             * @param   output      Output the raw data contained in the file.
             */
            bool startDecompression(
                jpeg_decompress_struct& cinfo,
                int& rowStride,
                RawImage* output
            ) ;

            /**
             * Finish the decompression of the file.
             * @param   cinfo   Decompression data to release from main memory.
             */
            void finishDecompression(jpeg_decompress_struct& cinfo) ;

            /**
             * End parsing the file.
             * @param   cinfo   Decompression data to release from main memory.
             */
            void endParsing(jpeg_decompress_struct& cinfo) ;
    } ;
}

#endif
