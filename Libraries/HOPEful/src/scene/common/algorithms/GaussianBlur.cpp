#include <scene/common/algorithms/GaussianBlur.hpp>
#include <HOPEStrings.hpp>
#include <Math.hpp>
#include <stdexcept>
#include <iterator>

#include <iostream>

using namespace Hope ;

GaussianBlur::GaussianBlur(
    Spite::RawImage& original
) : m_original(original) {}


Spite::RawImage GaussianBlur::process(const float radius) {
    auto originalWidth = m_original.get().width() ;
    auto originalHeight = m_original.get().height() ;

    auto& format = m_original.get().format() ;
    Spite::RawImage blurred(format.id(), format.type()) ;
    blurred.setDimensions(originalWidth, originalHeight) ;
    std::copy(
        m_original.get().data().begin(),
        m_original.get().data().end(),
        std::back_inserter(blurred.data())
    ) ;

    switch (format.type()) {
        case Spite::ColorFormat::Byte:
            // processByte(m_original.get().data(), blurred.data(), radius) ;
            break ;

        case Spite::ColorFormat::FloatingPoint:
            processFloat(m_original.get().data(), blurred.data(), radius) ;
            break ;

        default:
            throw std::runtime_error(Hope::Texts::EnvironmentMap_UnknownFormat) ;
    }

    return blurred ;
}

void GaussianBlur::processFloat(
    std::vector<unsigned char>& sourceBytes,
    std::vector<unsigned char>& destinationBytes,
    const float radius
) {
    const int BoxSize = 3 ;
    auto&& boxes = boxesForGauss(radius, BoxSize) ;

    auto* sourceChannels = reinterpret_cast<HDRRGB*>(sourceBytes.data()) ;
    auto* destinationChannels = reinterpret_cast<HDRRGB*>(destinationBytes.data()) ;

    for (unsigned int channel = 0 ; channel < Hope::AmountRGBChannels ; ++channel) {
        boxBlur<HDRRGB>(sourceChannels, destinationChannels, channel, (boxes[0] - 1.f) / 2.f) ;
        boxBlur<HDRRGB>(destinationChannels, sourceChannels, channel, (boxes[1] - 1.f) / 2.f) ;
        boxBlur<HDRRGB>(sourceChannels, destinationChannels, channel, (boxes[2] - 1.f) / 2.f) ;
    }
}

std::vector<float> GaussianBlur::boxesForGauss(
    const float sigma,
    const int amountBoxes
) {
    float wIdeal = std::sqrt((12.f * sigma * sigma / amountBoxes) + 1) ;
    auto wl = static_cast<int>(std::floor(wIdeal)) ;

    if (wl % 2 == 0) {
        wl = wl - 1 ;
    }

    auto wu = wl + 2 ;

    float mIdeal = ((12.f * sigma * sigma) - (amountBoxes * wl * wl) - (4.f * amountBoxes * wl) - (3.f * amountBoxes)) / (-4.f * wl - 4.f) ;
    auto m = std::round(mIdeal) ;

    std::vector<float> sizes ;
    sizes.reserve(amountBoxes) ;

    for (int index = 0 ; index < amountBoxes ; ++index) {
        if (index < m) {
            sizes.push_back(wl) ;
        }
        else {
            sizes.push_back(wu) ;
        }
    }

    return sizes ;
}

template<typename PixelType>
void GaussianBlur::boxBlur(
    PixelType* sourceChannels,
    PixelType* destinationChannels,
    const unsigned int channel,
    const float radius
) {
    auto imageWidth = m_original.get().width() ;
    auto imageHeight = m_original.get().height() ;

    boxBlurHorizontal(
        destinationChannels,
        sourceChannels,
        imageWidth,
        imageHeight,
        channel,
        radius
    ) ;

    boxBlurVertical(
        sourceChannels,
        destinationChannels,
        imageWidth,
        imageHeight,
        channel,
        radius
    ) ;
}

template<typename PixelType>
void GaussianBlur::boxBlurHorizontal(
    PixelType* originalChannels,
    PixelType* blurredChannels,
    const unsigned int imageWidth,
    const unsigned int imageHeight,
    const unsigned int channel,
    const float radius
) {
    float iarr = 1.f / (radius + radius + 1.f) ;
    float maxWidthForBox = (imageWidth - radius) ;

    for (unsigned int y = 0 ; y < imageHeight ; ++y) {
        unsigned int ty = y * imageWidth ;
        unsigned int ly = ty ;
        unsigned int ry = ty + radius ;

        float fv = std::clamp(originalChannels[ty].array[channel], 0.f, 1.f) ;
        float lv = std::clamp(originalChannels[ty + imageWidth - 1].array[channel], 0.f, 1.f) ;
        float val = (radius + 1.f) * fv ;

        for (unsigned int offset = 0 ; offset < radius ; ++offset) {
            val += std::clamp(originalChannels[ty + offset].array[channel], 0.f, 1.f) ;
        }

        for (unsigned int offset = 0 ; offset <= radius ; ++offset) {
            val += std::clamp(originalChannels[ry++].array[channel], 0.f, 1.f) - fv ;
            blurredChannels[ty++].array[channel] = val * iarr ;
        }

        for (float offset = radius + 1.f ; offset < maxWidthForBox ; offset += 1.f) {
            val += std::clamp(originalChannels[ry++].array[channel], 0.f, 1.f) - std::clamp(originalChannels[ly++].array[channel], 0.f, 1.f) ;
            blurredChannels[ty++].array[channel] = val * iarr ;
        }

        for (float offset = maxWidthForBox ; offset < imageWidth ; offset += 1.f) {
            val += lv - std::clamp(originalChannels[ly++].array[channel], 0.f, 1.f) ;
            blurredChannels[ty++].array[channel] = val * iarr ;
        }
    }
}

template<typename PixelType>
void GaussianBlur::boxBlurVertical(
    PixelType* originalChannels,
    PixelType* blurredChannels,
    const unsigned int imageWidth,
    const unsigned int imageHeight,
    const unsigned int channel,
    const float radius
) {
    float iarr = 1.f / (radius + radius + 1.f) ;
    float maxHeightForBox = imageHeight - radius ;

    for (unsigned int x = 0 ; x < imageWidth ; ++x) {
        unsigned int tx = x ;
        unsigned int lx = tx ;
        unsigned int rx = tx + (radius * imageWidth) ;

        float fv = std::clamp(originalChannels[tx].array[channel], 0.f, 1.f) ;
        float lv = std::clamp(originalChannels[tx + imageWidth * (imageHeight - 1)].array[channel], 0.f, 1.f) ;
        float val = (radius + 1) * fv ;

        for (unsigned int offset = 0 ; offset < radius ; ++offset) {
            val += std::clamp(originalChannels[tx + offset * imageWidth].array[channel], 0.f, 1.f) ;
        }

        for (unsigned int offset = 0 ; offset <= radius ; ++offset) {
            val += std::clamp(originalChannels[rx].array[channel], 0.f, 1.f) - fv ;
            blurredChannels[tx].array[channel] = val * iarr ;
            rx += imageWidth ;
            tx += imageWidth ;
        }

        for (float offset = radius + 1.f ; offset < maxHeightForBox ; offset += 1.f) {
            val += std::clamp(originalChannels[rx].array[channel], 0.f, 1.f) - std::clamp(originalChannels[lx].array[channel], 0.f, 1.f) ;
            blurredChannels[tx].array[channel] = val * iarr ;
            lx += imageWidth ;
            rx += imageWidth ;
            tx += imageWidth ;
        }

        for (float offset = maxHeightForBox ; offset < imageHeight ; offset += 1.f) {
            val += lv - std::clamp(originalChannels[lx].array[channel], 0.f, 1.f) ;
            blurredChannels[tx].array[channel] = val * iarr ;
            lx += imageWidth ;
            tx += imageWidth ;
        }
    }
}
