#include <files/images/data/RawImage.hpp>
#include <SPITEStrings.hpp>
#include <stdexcept>
#include <string.h>

using namespace Spite ;

RawImage::RawImage(ColorFormat::ID format)
    : m_format(format) {}

void RawImage::setDimensions(
    const unsigned int& width,
    const unsigned int& height
) {
    if (m_format == ColorFormat::Unknown) {
        throw std::runtime_error(RawImageMsg::Error::UndefinedColorFormatWhenSettingSize) ;
    }

    m_width = width ;
    m_height = height ;
    m_pixelData.clear();
}

void RawImage::setFormat(ColorFormat::ID format) {
    m_format = format ;
    m_pixelData.clear();
}

ColorFormat::ID RawImage::format() {
    return m_format ;
}

std::vector<unsigned char>& RawImage::data() {
    return m_pixelData ;
}

unsigned int RawImage::width() const {
    return m_width ;
}

unsigned int RawImage::height() const {
    return m_height ;
}
