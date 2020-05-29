#include <files/images/save/BufferSave.hpp>
#include <third_party/stb_image_write.h>
#include <array>
#include <limits>

using namespace Spite::Image ;

void write_bytes_func(void* context, void* data, int size) {
    auto* contextBuffer = reinterpret_cast<std::vector<unsigned char>*>(context) ;
    auto* byteData = reinterpret_cast<unsigned char*>(data) ;
    (*contextBuffer).insert((*contextBuffer).end(), byteData, byteData + size) ;
}

bool BufferSave::SavePNG(
    RawImage& image,
    std::vector<unsigned char>& buffer
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto pixelSize = image.format().pixelSizeInBytes() ;
    auto& imageBytes = image.data() ;

    return stbi_write_png_to_func(
        &write_bytes_func,
        reinterpret_cast<void*>(&buffer),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data(),
        pixelSize * image.width()
    ) ;
}

bool BufferSave::SaveJPEG(
    RawImage& image,
    std::vector<unsigned char>& buffer
) {
    static const int JPEGQuality = 100 ;
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_jpg_to_func(
        &write_bytes_func,
        reinterpret_cast<void*>(&buffer),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data(),
        JPEGQuality
    ) ;
}

bool BufferSave::SaveTGA(
    RawImage& image,
    std::vector<unsigned char>& buffer
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_tga_to_func(
        &write_bytes_func,
        reinterpret_cast<void*>(&buffer),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data()
    ) ;
}

bool BufferSave::SaveBMP(
    RawImage& image,
    std::vector<unsigned char>& buffer
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_bmp_to_func(
        &write_bytes_func,
        reinterpret_cast<void*>(&buffer),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data()
    ) ;
}

bool BufferSave::SaveHDR(
    RawImage& image,
    std::vector<unsigned char>& buffer
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;
    auto* imageFloat = reinterpret_cast<float*>(imageBytes.data()) ;

    return stbi_write_hdr_to_func(
        &write_bytes_func,
        reinterpret_cast<void*>(&buffer),
        image.width(),
        image.height(),
        amountComponents,
        imageFloat
    ) ;
}
