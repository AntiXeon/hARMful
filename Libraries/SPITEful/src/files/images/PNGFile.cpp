#include <files/images/PNGFile.h>
#include <SPITEStrings.h>
#include <debug/Log.h>


#define CHECK_SUCCESS(success, message, path) {                                 \
    if (!success) {                                                             \
        endParsing(pngStruct, pngInfo) ;                                        \
        std::cerr <<                                                            \
                     message <<                                                 \
                     path <<                                                    \
                     std::endl ;                                                \
        return false ;                                                          \
    }                                                                           \
}


namespace Spite {
                                              /** CONSTRUCTION / DESTRUCTION **/
    PNGFile::PNGFile(const std::string& path) : ImageFile(path) {}

    PNGFile::~PNGFile() {}

                                                             /*** UTILITIES ***/
    bool PNGFile::parse(IFileData* filedata) {
        char* filepath = (char*) getPath().getAbsolutePath().c_str() ;

        // Header of the PNG file. It is used to check if it is really a PNG
        // file.
        unsigned char pngHeader[HeaderLength] ;
        fread(pngHeader, sizeof(char), HeaderLength, getDescriptor()) ;

        bool isPNG = (png_sig_cmp(pngHeader, 0, HeaderLength) == 0) ;
        if (!isPNG) {
            Doom::Log::Write(
                             Doom::Log::LogDebug,
                             PNGMsg::Error::NotPNGFile,
                             filepath
                            ) ;
            return false ;
        }

        // It is used for pure file management (inputs, outputs, etc).
        png_structp pngStruct ;
        // It stores informations on the PNG picture.
        png_infop pngInfo ;
        if (!initializeDecompressionData(pngStruct, pngInfo, filepath)) {
            return false ;
        }

        startDecompression(pngStruct, pngInfo, filedata) ;
        endParsing(pngStruct, pngInfo) ;
        return true ;
    }


                                                             /*** READ DATA ***/
    bool PNGFile::initializeDecompressionData(
                                              png_structp& pngStruct,
                                              png_infop& pngInfo,
                                              const char* filepath
                                             ) {
        // Allocate and initialize the PNG structure. It is used for pure file
        // management (inputs, outputs, etc).
        // It is possible to define functions for handling errors and warnings.
        pngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL) ;
        CHECK_SUCCESS((pngStruct != NULL), PNGMsg::Error::InitializationStructureFailed, filepath) ;

        // Allocate and initialize the PNG informations.
        // It stores informations on the PNG picture.
        pngInfo = png_create_info_struct(pngStruct) ;
        CHECK_SUCCESS((pngInfo != NULL), PNGMsg::Error::InitializationInfosFailed, filepath) ;

        // Initialize inputs/outputs for the PNG file.
        png_init_io(pngStruct, getDescriptor()) ;
        // Set the amount of already bytes read from the PNG file (header).
        png_set_sig_bytes(pngStruct, HeaderLength) ;
        // Read some informations on the picture.
        png_read_info(pngStruct, pngInfo) ;
        return true ;
    }

    void PNGFile::startDecompression(
                                     png_structp& pngStruct,
                                     png_infop& pngInfo,
                                     IFileData* output
                                    ) {
        RawImage* rawImage = ((RawImage*) output) ;


        // Get the color type and set the corresponding color format to the raw
        // picture.
        png_byte colorType = png_get_color_type(pngStruct, pngInfo) ;
        unsigned int sizeFactor = setAndConvertColorFormat(
                                                           pngStruct,
                                                           pngInfo,
                                                           colorType,
                                                           rawImage
                                                          ) ;

        unsigned int width = png_get_image_width(pngStruct, pngInfo) ;
        unsigned int height = png_get_image_height(pngStruct, pngInfo) ;
        // Set the dimensions of the output image raw data.
        rawImage -> setDimensions(width, height) ;

        // Get the image allocated buffer.
        void* imageData ;
        unsigned int imageDataSize ;
        output -> getData(imageData, imageDataSize) ;
        unsigned char* imageDataBuffer = (unsigned char*) imageData ;
        // The size of each row from the image is necessary to store data.
        unsigned int rowSize = png_get_rowbytes(pngStruct, pngInfo) * 4 * sizeFactor ;

        // Read each row of the image and store the data.
        for (unsigned int rowIndex = 0 ; rowIndex < height ; ++rowIndex) {
            unsigned int offset = rowIndex * rowSize ;
            unsigned char* imageDataBufferOffset = imageDataBuffer + offset ;
            png_read_row(pngStruct, imageDataBufferOffset, NULL) ;
        }
    }

    void PNGFile::endParsing(
                             png_structp& pngStruct,
                             png_infop& pngInfo
                            ) {
        png_destroy_read_struct(&pngStruct, &pngInfo, NULL) ;
        close() ;
    }

    unsigned int PNGFile::setAndConvertColorFormat(
                                                   png_structp& pngStruct,
                                                   png_infop& pngInfo,
                                                   png_byte& colorType,
                                                   RawImage* output
                                                  ) {
        // At the moment, only RGB and RGBA files are handled.
        // Other color types are considered as RGB color format as their data
        // are expanded to match this format.
        switch(colorType) {
            case PNG_COLOR_TYPE_RGB:
                output -> setFormat(&ColorFormat::Get(ColorFormat::RGB)) ;
                return 1 ;

            case PNG_COLOR_TYPE_RGBA:
                output -> setFormat(&ColorFormat::Get(ColorFormat::RGBA)) ;
                return 1 ;

            case PNG_COLOR_TYPE_PALETTE:
            {
                png_set_palette_to_rgb(pngStruct) ;

                if (png_get_valid(pngStruct, pngInfo, PNG_INFO_tRNS)) {
                    output -> setFormat(&ColorFormat::Get(ColorFormat::RGBA)) ;
                    return 4 ;
                }
                else {
                    output -> setFormat(&ColorFormat::Get(ColorFormat::RGB)) ;
                    return 3 ;
                }
            }

            case PNG_COLOR_TYPE_GRAY:
                // Try expansion of raw data as they are not fully supported.
                png_set_gray_to_rgb(pngStruct) ;
                output -> setFormat(&ColorFormat::Get(ColorFormat::RGB)) ;
                return 4 ;

            case PNG_COLOR_TYPE_GRAY_ALPHA:
                // Try expansion of raw data as they are not fully supported.
                png_set_gray_to_rgb(pngStruct) ;
                output -> setFormat(&ColorFormat::Get(ColorFormat::RGBA)) ;
                return 2 ;

            default:
                // Try expansion of raw data as they are not fully supported.
                png_set_expand(pngStruct) ;
                output -> setFormat(&ColorFormat::Get(ColorFormat::RGB)) ;
                return 1 ;
        }
    }
} ;
