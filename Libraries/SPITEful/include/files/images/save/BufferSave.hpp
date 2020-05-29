#ifndef __SPITE__IMAGE_BUFFER_SAVE__
#define __SPITE__IMAGE_BUFFER_SAVE__

#include <utils/Platform.hpp>
#include <files/images/data/RawImage.hpp>
#include <functional>
#include <vector>

namespace Spite::Image::BufferSave {
    using Functor = std::function<bool(RawImage&, std::vector<unsigned char>&)> ;

    /**
     * Save PNG file.
     * @return  true on success; false otherwise.
     */
    exported bool SavePNG(
        RawImage& image,
        std::vector<unsigned char>& buffer
    ) ;

    /**
     * Save JPEG file.
     * @return  true on success; false otherwise.
     */
    exported bool SaveJPEG(
        RawImage& image,
        std::vector<unsigned char>& buffer
    ) ;

    /**
     * Save TGA file.
     * @return  true on success; false otherwise.
     */
    exported bool SaveTGA(
        RawImage& image,
        std::vector<unsigned char>& buffer
    ) ;

    /**
     * Save BMP file.
     * @return  true on success; false otherwise.
     */
    exported bool SaveBMP(
        RawImage& image,
        std::vector<unsigned char>& buffer
    ) ;

    /**
     * Save HDR file.
     * @return  true on success; false otherwise.
     */
    exported bool SaveHDR(
        RawImage& image,
        std::vector<unsigned char>& buffer
    ) ;
}

#endif
