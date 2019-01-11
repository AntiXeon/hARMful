#include <files/images/data/RawImage.hpp>
#include <SPITEStrings.hpp>
#include <stdexcept>
#include <string.h>

using namespace Spite ;

RawImage::RawImage(ColorFormat* format)
    : m_pixelData(nullptr),
      m_format(format) {}

RawImage::~RawImage() {
    if (m_pixelData != nullptr) {
        delete[] m_pixelData ;
    }
}

void RawImage::freeData() {
    if (m_pixelData != nullptr) {
        delete[] m_pixelData ;
    }
}

void RawImage::setDimensions(
    const unsigned int& width,
    const unsigned int& height
) {
    if (m_format == nullptr) {
        throw std::runtime_error(RawImageMsg::Error::UndefinedColorFormatWhenSettingSize) ;
    }

    m_width = width ;
    m_height = height ;

    unsigned char amountOfComponents = m_format -> amountOfComponents() ;
    m_pixelData = new int[width * height * amountOfComponents] ;
}

bool RawImage::setFormat(ColorFormat* format) {
    if (m_format == nullptr) {
        m_format = format ;
        return true ;
    }

    return false ;
}

const ColorFormat* RawImage::format() const {
    return m_format ;
}

void RawImage::data(void*& data, unsigned int& size) {
    const unsigned char AmountOfComponents = m_format -> amountOfComponents() ;
    const unsigned int TotalBufferSize = m_width * m_height * AmountOfComponents ;
    data = m_pixelData ;
    size = TotalBufferSize ;
}

unsigned int RawImage::width() const {
    return m_width ;
}

unsigned int RawImage::height() const {
    return m_height ;
}
