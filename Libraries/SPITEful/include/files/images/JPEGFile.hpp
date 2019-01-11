#ifndef __SPITE__JPEG_FILE__
#define __SPITE__JPEG_FILE__

extern "C" {
    #include <stdio.h>
    #include <stddef.h>
    #include <jpeglib.h>
}

#include <files/images/ImageFile.hpp>

namespace Spite {

    /**
     * Load a JPEG file.
     */
    class JPEGFile final : public ImageFile {
        public:
            /**
             * Create a new JPEGFile.
             * @param   path    Path of the file to open.
             */
            JPEGFile(const std::string& path) ;

            /**
             * Destruction of the JPEGFile.
             */
            virtual ~JPEGFile() ;


        private:
            /**
             * Parse the JPEG file and store raw data in the RawImage.
             * @param   output  Output the raw data from the JPEG file.
             */
            bool parse(IFileData* output) ;

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
                IFileData* output
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
