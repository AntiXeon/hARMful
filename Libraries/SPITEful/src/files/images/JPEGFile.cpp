#include <files/images/JPEGFile.hpp>
#include <files/images/data/RawImage.hpp>
#include <SPITEStrings.hpp>
#include <utils/LogSystem.hpp>
#include <filesystem>

#define CHECK_SUCCESS(success, message, path) {                                 \
    if (!success) {                                                             \
        endParsing(cinfo) ;                                                     \
        std::cerr <<                                                            \
                     message <<                                                 \
                     path <<                                                    \
                     std::endl ;                                                \
        return false ;                                                          \
    }                                                                           \
}

using namespace Spite ;
namespace fs = std::filesystem ;

bool JPEGFile::parse(IFileData* filedata) {
    // Decompression parameters and pointers.
    jpeg_decompress_struct cinfo ;
    // Length of a row in the buffer.
    int rowStride ;
    // Error manager for libjpeg.
    jpeg_error_mgr m_errorManager ;
    cinfo.err = jpeg_std_error(&m_errorManager) ;

    char* filepath = const_cast<char*>(fs::absolute(path()).string().c_str()) ;
    bool success = initializeDecompressionData(cinfo, descriptor()) ;

    if (!success) {
        // Log debug info.
        std::weak_ptr<Doom::LogSystem> logWeakPtr = Doom::LogSystem::GetInstance() ;
        std::shared_ptr<Doom::LogSystem> logSystem = logWeakPtr.lock() ;

        if (!logSystem) {
            return false ;
        }

        logSystem -> writeLine(
            Doom::LogSystem::Gravity::Debug,
            JPEGMsg::Error::DecompressiongInitFailed,
            filepath
         ) ;

        return false ;
    }

    success = startDecompression(cinfo, rowStride, filedata) ;

    if (!success) {
        // Log debug info.
        std::weak_ptr<Doom::LogSystem> logWeakPtr = Doom::LogSystem::GetInstance() ;
        std::shared_ptr<Doom::LogSystem> logSystem = logWeakPtr.lock() ;

        if (!logSystem) {
            return false ;
        }

        logSystem -> writeLine(
            Doom::LogSystem::Gravity::Debug,
            JPEGMsg::Error::FailureWhileDecompressing,
            filepath
         ) ;

        return false ;
    }

    return true ;
}

bool JPEGFile::initializeDecompressionData(
    jpeg_decompress_struct& cinfo,
    FILE* info
) {
    // Instanciation of the cinfo data.
    jpeg_create_decompress(&cinfo) ;
    // Set the source file to decompress.
    jpeg_stdio_src(&cinfo, info) ;
    // Read header of the jpeg file to initialize decompression parameters
    // to default values.
    const bool requireImage = true ;
    int error = jpeg_read_header(&cinfo, requireImage) ;

    return (error == JPEG_HEADER_OK) ;
}

bool JPEGFile::startDecompression(
    jpeg_decompress_struct& cinfo,
    int& rowStride,
    IFileData* output
) {
    // Start the decompression.
    jpeg_start_decompress(&cinfo) ;
    // Amount of JSAMPLE per row in the output buffer.
    rowStride = cinfo.output_width * cinfo.output_components * 4 ;

    // Set the dimensions of the output image raw data.
    RawImage* raw = dynamic_cast<RawImage*>(output) ;
    raw -> setDimensions(cinfo.output_width, cinfo.output_height) ;

    // Get the image allocated buffer.
    unsigned char* imageDataBuffer = nullptr ;
    void* voidImageDataBuffer = static_cast<void*>(imageDataBuffer) ;
    unsigned int imageDataSize ;
    output -> data(voidImageDataBuffer, imageDataSize) ;

    // Read lines in the picture while the end of image is not reached
    // (using the libjpeg states).
    while (cinfo.output_scanline < cinfo.output_height) {
        // Read one scanline at a time, even if it is possible to ask for
        // more.
        unsigned int offset = cinfo.output_scanline * rowStride ;
        unsigned char* imageDataBufferOffset = imageDataBuffer + offset ;
        jpeg_read_scanlines(&cinfo, &imageDataBufferOffset, 1) ;
    }

    return true ;
}

void JPEGFile::finishDecompression(jpeg_decompress_struct& cinfo) {
    jpeg_finish_decompress(&cinfo) ;
    endParsing(cinfo) ;
}

void JPEGFile::endParsing(jpeg_decompress_struct& cinfo) {
    jpeg_destroy_decompress(&cinfo) ;
    close() ;
}
