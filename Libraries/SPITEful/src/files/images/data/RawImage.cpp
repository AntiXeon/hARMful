#include <files/images/data/RawImage.hpp>
#include <SPITEStrings.hpp>
#include <stdexcept>
#include <string.h>

using namespace Spite ;

RawImage::RawImage(
    const ColorFormat::ID format,
    const ColorFormat::ComponentType type
)
    : m_format(format),
      m_type(type) {}

void RawImage::setDimensions(
    const unsigned int& width,
    const unsigned int& height
) {
    if (m_format == ColorFormat::UnknownID || m_type == ColorFormat::UnknownType) {
        throw std::runtime_error(RawImageMsg::Error::UndefinedColorFormatWhenSettingSize) ;
    }

    m_width = width ;
    m_height = height ;
    m_pixelData.clear();
}

void RawImage::setFormat(
    const ColorFormat::ID format,
    const ColorFormat::ComponentType type
) {
    m_format = format ;
    m_type = type ;
    m_pixelData.clear();
}

const ColorFormat& RawImage::format() {
    return ColorFormat::Get(m_format, m_type) ;
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
