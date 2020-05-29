#include <files/images/save/FileSave.hpp>
#include <third_party/stb_image_write.h>

using namespace Spite::Image ;

bool FileSave::SavePNG(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto pixelSize = image.format().pixelSizeInBytes() ;
    auto& imageBytes = image.data() ;

    return stbi_write_png(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data(),
        pixelSize * image.width()
    ) ;
}

bool FileSave::SaveJPEG(
    RawImage& image,
    const std::string& path
) {
    static const int JPEGQuality = 100 ;
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_jpg(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data(),
        JPEGQuality
    ) ;
}

bool FileSave::SaveTGA(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_tga(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data()
    ) ;
}

bool FileSave::SaveBMP(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;

    return stbi_write_bmp(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageBytes.data()
    ) ;
}

bool FileSave::SaveHDR(
    RawImage& image,
    const std::string& path
) {
    auto amountComponents = image.format().amountOfComponents() ;
    auto& imageBytes = image.data() ;
    auto* imageFloat = reinterpret_cast<float*>(imageBytes.data()) ;

    return stbi_write_hdr(
        path.c_str(),
        image.width(),
        image.height(),
        amountComponents,
        imageFloat
    ) ;
}
