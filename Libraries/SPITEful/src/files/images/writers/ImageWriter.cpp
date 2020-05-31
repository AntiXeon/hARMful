#include <files/images/writers/ImageWriter.hpp>
#include <debug/ErrorsManagement.hpp>
#include <utils/StringExt.hpp>
#include <SPITEStrings.hpp>
#include <utils/LogSystem.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <third_party/stb_image_write.h>

using namespace Spite ;
namespace fs = std::filesystem ;

const std::string ImageWriter::HDRFileExtension = ".hdr" ;
const std::string ImageWriter::PNGFileExtension = ".png" ;
const std::string ImageWriter::JPEGFileExtension = ".jpeg" ;
const std::string ImageWriter::JPGFileExtension = ".jpg" ;
const std::string ImageWriter::BMPFileExtension = ".bmp" ;
const std::string ImageWriter::RLEFileExtension = ".rle" ;
const std::string ImageWriter::DIBFileExtension = ".dib" ;
const std::string ImageWriter::TGAFileExtension = ".tga" ;
const std::string ImageWriter::TPICFileExtension = ".tpic" ;

int ImageWriter::JPEGQuality = 90 ;

ImageWriter::ImageWriter(
    RawImage& data,
    const bool verticalFlip
) : m_data(data),
    m_verticalFlip(verticalFlip)
{}

bool ImageWriter::process() {
    bool cachedFlipBefore = stbi__flip_vertically_on_write ;
    stbi_flip_vertically_on_write(m_verticalFlip) ;
    bool success = processSpecific() ;
    stbi_flip_vertically_on_write(cachedFlipBefore) ;
    return success ;
}

void ImageWriter::SetPNGCompressionLevel(const int level) {
    const int MinLevel = 0 ;
    const int MaxLevel = 9 ;
    int clampedLevel = std::clamp(level, MinLevel, MaxLevel) ;
    stbi_write_png_compression_level = clampedLevel ;
}

void ImageWriter::SetPNGFilter(const PNGFilter filter) {
    stbi_write_force_png_filter = filter ;
}

void ImageWriter::SetCompressTGAWithRLE(const bool rleEnabled) {
    stbi_write_tga_with_rle = rleEnabled ;
}
