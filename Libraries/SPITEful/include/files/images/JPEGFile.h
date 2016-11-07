#ifndef __SPITE_JPEG_FILE__
#define __SPITE_JPEG_FILE__


extern "C" {
    #include <stdio.h>
    #include <stddef.h>
    #include <jpeglib.h>
}

#include <files/images/ImageFile.h>


namespace Spite {

    /**
     * @brief   Load a JPEG file.
     *
     * @author  Denis CARLUS
     * @version 1.0     03/10/2016
     */
    class JPEGFile : public ImageFile {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new JPEGFile.
             * @param   path    Path of the file to open.
             */
            JPEGFile(const std::string& path) ;

            /**
             * @brief   Destruction of the JPEGFile.
             */
            virtual ~JPEGFile() ;


        private:
                                                             /*** UTILITIES ***/
            /**
             * @brief   Parse the JPEG file and store raw data in the RawImage.
             * @param   output  Output the raw data from the JPEG file.
             */
            bool parse(IFileData* output) ;

                                                             /*** READ DATA ***/
            /**
             * @brief   Initialize the decompression data.
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
             * @brief   Start the decompression of the file.
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
             * @brief   Finish the decompression of the file.
             * @param   cinfo   Decompression data to release from main memory.
             */
            void finishDecompression(jpeg_decompress_struct& cinfo) ;

            /**
             * @brief   End parsing the file.
             * @param   cinfo   Decompression data to release from main memory.
             */
            void endParsing(jpeg_decompress_struct& cinfo) ;
    } ;

} ;


#endif
