#ifndef __SPITE__IMAGE_FILE_SAVE__
#define __SPITE__IMAGE_FILE_SAVE__

#include <utils/Platform.hpp>
#include <files/images/data/RawImage.hpp>
#include <functional>
#include <string>

namespace Spite::Image::FileSave {
    using Functor = std::function<bool(RawImage&, const std::string&)> ;

    /**
     * Save PNG file.
     * @return  true on success; false otherwise.
     */
    exported bool SavePNG(
        RawImage& image,
        const std::string& path
    ) ;

    /**
     * Save JPEG file.
     * @return  true on success; false otherwise.
     */
    exported bool SaveJPEG(
        RawImage& image,
        const std::string& path
    ) ;

    /**
     * Save TGA file.
     * @return  true on success; false otherwise.
     */
    exported bool SaveTGA(
        RawImage& image,
        const std::string& path
    ) ;

    /**
     * Save BMP file.
     * @return  true on success; false otherwise.
     */
    exported bool SaveBMP(
        RawImage& image,
        const std::string& path
    ) ;

    /**
     * Save HDR file.
     * @return  true on success; false otherwise.
     */
    exported bool SaveHDR(
        RawImage& image,
        const std::string& path
    ) ;
}

#endif
