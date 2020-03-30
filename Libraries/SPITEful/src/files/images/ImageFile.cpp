#include <files/images/ImageFile.hpp>
#include <debug/ErrorsManagement.hpp>
#include <utils/StringExt.hpp>
#include <filesystem>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <third_party/stb_image.h>

using namespace Spite ;
namespace fs = std::filesystem ;

ImageFile::ImageFile(const std::string& path, const bool flip)
    : File(path),
      m_flip(flip) {}

bool ImageFile::load(IFileData* filedata) {
    stbi_set_flip_vertically_on_load(m_flip) ;
    std::string filepath = path().string() ;

    int width = 0 ;
    int height = 0 ; 
    int amountComponents = 0 ;
    stbi_info(filepath.c_str(), &width, &height, &amountComponents) ;

    RawImage* rawImage = dynamic_cast<RawImage*>(filedata) ;
    rawImage -> setFormat(static_cast<ColorFormat::ID>(amountComponents)) ;
    rawImage -> setDimensions(width, height) ;
    auto& rawPixelData = rawImage -> data() ;

    unsigned char* imageData = stbi_load(filepath.c_str(), &width, &height, &amountComponents, 0) ;

    size_t width_64 = width ;
    size_t height_64 = height ;
    size_t amountComponents_64 = amountComponents ;
    size_t imageDataSize = width_64 * height_64 * amountComponents_64 ;
    rawPixelData.insert(rawPixelData.begin(), imageData, imageData + imageDataSize) ;
    stbi_image_free(imageData) ;

    return (rawPixelData.size()) > 0 ;
}

bool ImageFile::save(
    IFileData*,
    const std::string&
) {
    // Needs implementation!
    return false ;
}