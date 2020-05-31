#ifndef __SPITE__IMAGE_UTILS__
#define __SPITE__IMAGE_UTILS__

#include <utils/Platform.hpp>
#include <files/images/data/RawImage.hpp>

namespace Spite::ImageUtils {
    /**
     * Resize a picture to the wanted size.
     * @param   original    Original picture data.
     * @param   width       Width of th output resized picture.
     * @param   height      Height of th output resized picture.
     * @return  Resized picture.
     */
    [[maybe_unused]]
    exported static RawImage Resize(
        RawImage& original,
        const unsigned int width,
        const unsigned int height
    ) ;
}

#endif
