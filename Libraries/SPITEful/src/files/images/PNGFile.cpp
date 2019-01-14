#include <files/images/PNGFile.hpp>
#include <files/images/data/ColorFormat.hpp>
#include <files/images/data/RawImage.hpp>
#include <SPITEStrings.hpp>
#include <utils/LogSystem.hpp>
#include <filesystem>
#include <algorithm>

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


using namespace Spite ;
namespace fs = std::filesystem ;

PNGFile::PNGFile(const std::string& path)
    : ImageFile(path) {
}

bool PNGFile::parse(RawImage* filedata) {
    std::string absolutePath = fs::absolute(m_path).string() ;
    char* filepath = const_cast<char*>(absolutePath.c_str()) ;

    // Header of the PNG file. It is used to check if it is really a PNG
    // file.
    unsigned char pngHeader[HeaderLength] ;
    fread(pngHeader, sizeof(char), HeaderLength, descriptor()) ;

    bool isPNG = (png_sig_cmp(pngHeader, 0, HeaderLength) == 0) ;

    if (!isPNG) {
        // Log debug info.
        std::weak_ptr<Doom::LogSystem> logWeakPtr = Doom::LogSystem::GetInstance() ;
        std::shared_ptr<Doom::LogSystem> logSystem = logWeakPtr.lock() ;

        if (!logSystem) {
            return false ;
        }

        logSystem -> writeLine(
            Doom::LogSystem::Gravity::Debug,
            PNGMsg::Error::NotPNGFile,
            filepath
         ) ;

        return false ;
    }

    // It is used for pure file management (inputs, outputs, etc).
    png_structp pngStruct = nullptr ;
    // It stores informations on the PNG picture.
    png_infop pngInfo = nullptr ;

    if (!initializeDecompressionData(pngStruct, pngInfo, filepath)) {
        return false ;
    }

    startDecompression(pngStruct, pngInfo, filedata) ;
    endParsing(pngStruct, pngInfo) ;
    return true ;
}

bool PNGFile::initializeDecompressionData(
    png_structp& pngStruct,
    png_infop& pngInfo,
    const char* filepath
) {
    // Allocate and initialize the PNG structure. It is used for pure file
    // management (inputs, outputs, etc).
    // It is possible to define functions for handling errors and warnings.
    pngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr) ;

    if (!pngStruct) {
        // Log debug info.
        std::weak_ptr<Doom::LogSystem> logWeakPtr = Doom::LogSystem::GetInstance() ;
        std::shared_ptr<Doom::LogSystem> logSystem = logWeakPtr.lock() ;

        if (!logSystem) {
            return false ;
        }

        logSystem -> writeLine(
            Doom::LogSystem::Gravity::Error,
            PNGMsg::Error::InitializationStructureFailed,
            filepath
         ) ;
    }

    // Allocate and initialize the PNG informations.
    // It stores informations on the PNG picture.
    pngInfo = png_create_info_struct(pngStruct) ;

    if (!pngInfo) {
        // Log debug info.
        std::weak_ptr<Doom::LogSystem> logWeakPtr = Doom::LogSystem::GetInstance() ;
        std::shared_ptr<Doom::LogSystem> logSystem = logWeakPtr.lock() ;

        if (!logSystem) {
            return false ;
        }

        logSystem -> writeLine(
            Doom::LogSystem::Gravity::Error,
            PNGMsg::Error::InitializationInfosFailed,
            filepath
         ) ;
    }

    // Initialize inputs/outputs for the PNG file.
    png_init_io(pngStruct, descriptor()) ;
    // Set the amount of already bytes read from the PNG file (header).
    png_set_sig_bytes(pngStruct, HeaderLength) ;
    // Read some informations on the picture.
    png_read_info(pngStruct, pngInfo) ;
    return true ;
}

void PNGFile::startDecompression(
    png_structp& pngStruct,
    png_infop& pngInfo,
    RawImage* output
) {
    png_byte colorType = png_get_color_type(pngStruct, pngInfo) ;
    png_byte bitDepth = png_get_bit_depth(pngStruct, pngInfo) ;

    if (bitDepth == 16) {
        png_set_strip_16(pngStruct) ;
    }

    // These color types don't have an alpha channel then fill it with 0xff.
    if (colorType == PNG_COLOR_TYPE_RGB ||
           colorType == PNG_COLOR_TYPE_GRAY ||
           colorType == PNG_COLOR_TYPE_PALETTE) {
        png_set_filler(pngStruct, 0xFF, PNG_FILLER_AFTER) ;
    }

    if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(pngStruct) ;
    }

    unsigned int width = png_get_image_width(pngStruct, pngInfo) ;
    unsigned int height = png_get_image_height(pngStruct, pngInfo) ;
    // Set the dimensions of the output image raw data.
    output -> setDimensions(width, height) ;
    output -> setFormat(ColorFormat::RGBA) ;

    png_read_update_info(pngStruct, pngInfo) ;

    unsigned char* imageDataBuffer ;
    unsigned int imageDataSize ;
    output -> data(imageDataBuffer, imageDataSize) ;

    // Get the image allocated buffer.
    unsigned int pngRowBytesLength = png_get_rowbytes(pngStruct, pngInfo) ;
    for (unsigned int y = 0; y < height; ++y) {
        unsigned char* rowBuffer = imageDataBuffer + (y * pngRowBytesLength) ;
        png_read_rows(pngStruct, &rowBuffer , nullptr, 1) ;
    }
}

void PNGFile::endParsing(
    png_structp pngStruct,
    png_infop pngInfo
) {
    close() ;
    png_destroy_read_struct(&pngStruct, &pngInfo, nullptr) ;
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
            output -> setFormat(ColorFormat::RGB) ;
            return 1 ;

        case PNG_COLOR_TYPE_RGBA:
            output -> setFormat(ColorFormat::RGBA) ;
            return 1 ;

        case PNG_COLOR_TYPE_PALETTE:
        {
            png_set_palette_to_rgb(pngStruct) ;

            if (png_get_valid(pngStruct, pngInfo, PNG_INFO_tRNS)) {
                output -> setFormat(ColorFormat::RGBA) ;
                return 4 ;
            }
            else {
                output -> setFormat(ColorFormat::RGB) ;
                return 3 ;
            }
        }

        case PNG_COLOR_TYPE_GRAY:
            // Try expansion of raw data as they are not fully supported.
            png_set_gray_to_rgb(pngStruct) ;
            output -> setFormat(ColorFormat::RGB) ;
            return 4 ;

        case PNG_COLOR_TYPE_GRAY_ALPHA:
            // Try expansion of raw data as they are not fully supported.
            png_set_gray_to_rgb(pngStruct) ;
            output -> setFormat(ColorFormat::RGBA) ;
            return 2 ;

        default:
            // Try expansion of raw data as they are not fully supported.
            png_set_expand(pngStruct) ;
            output -> setFormat(ColorFormat::RGB) ;
            return 1 ;
    }
}
