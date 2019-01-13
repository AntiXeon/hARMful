#include <files/images/JPEGTurboFile.hpp>
#include <readers/CPUEndiannessBinaryFileReader.hpp>
#include <writers/CPUEndiannessBinaryFileWriter.hpp>
#include <utils/LogSystem.hpp>
#include <SPITEStrings.hpp>
#include <filesystem>

using namespace Spite ;
namespace fs = std::filesystem ;

JPEGTurboFile::JPEGTurboFile(const std::string& path)
    : BinaryFile(path, true) {
}

bool JPEGTurboFile::load(RawImage* filedata) {
    // Read all the bytes from the JPEG file.
    std::vector<unsigned char> fileBytes ;
    m_reader -> readAllBytes(fileBytes) ;

    // Initialize decompression.
    tjhandle jpegDecompressor = tjInitDecompress() ;

    if (jpegDecompressor == nullptr) {
        return false ;
    }

    // Get JPEG file informations in the header (no decompression yet).
    int width = 0 ;
    int height = 0 ;
    int chrominanceSubsampling = 0 ;
    int colorSpace = 0 ;
    tjDecompressHeader3(
        jpegDecompressor,
        fileBytes.data(),
        static_cast<unsigned long>(fileBytes.size()),
        &width,
        &height,
        &chrominanceSubsampling,
        &colorSpace
    ) ;

    const int Pitch = 0 ;
    unsigned char* rawImageBytes = nullptr ;
    unsigned int rawImageSize = 0 ;
    filedata -> setDimensions(width, height) ;
    filedata -> setFormat(convertColorFormat(colorSpace)) ;

    // Get the allocated buffer from the raw image to directly get
    // uncompressed picture inside.
    filedata -> data(rawImageBytes, rawImageSize) ;

    // Decompress the JPEG file data.
    tjDecompress2(
        jpegDecompressor,
        fileBytes.data(),
        fileBytes.size(),
        rawImageBytes,
        width,
        Pitch,
        height,
        TJPF_RGB,
        TJFLAG_FASTDCT
    ) ;

    // End of the decompression. Clear data.
    tjDestroy(jpegDecompressor) ;

    return true ;
}

bool JPEGTurboFile::save(
    RawImage*,
    const std::string&
) {
    // To be done...
    return false ;
}

ColorFormat::ID JPEGTurboFile::convertColorFormat(const int jpegColorSpace) {
    switch (jpegColorSpace) {
        case TJCS_RGB:
            return ColorFormat::RGB ;

        default:
            return ColorFormat::Unknown ;
    }
}
