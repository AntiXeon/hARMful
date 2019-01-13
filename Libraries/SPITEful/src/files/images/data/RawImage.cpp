#include <files/images/data/RawImage.hpp>
#include <SPITEStrings.hpp>
#include <stdexcept>
#include <string.h>

using namespace Spite ;

RawImage::RawImage(ColorFormat::ID format)
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
    if (m_format == ColorFormat::Unknown) {
        throw std::runtime_error(RawImageMsg::Error::UndefinedColorFormatWhenSettingSize) ;
    }

    m_width = width ;
    m_height = height ;

    if (m_pixelData != nullptr) {
        delete[] m_pixelData ;
    }

    unsigned char amountOfComponents = ColorFormat::Get(m_format).amountOfComponents() ;
    m_pixelData = new unsigned char[m_width * m_height * amountOfComponents] ;
}

void RawImage::setFormat(ColorFormat::ID format) {
    m_format = format ;

    if (m_pixelData != nullptr) {
        delete[] m_pixelData ;
    }

    unsigned char amountOfComponents = ColorFormat::Get(m_format).amountOfComponents() ;
    m_pixelData = new unsigned char[m_width * m_height * amountOfComponents] ;
}

ColorFormat::ID RawImage::format() {
    return m_format ;
}

void RawImage::data(unsigned char*& data, unsigned int& size) {
    unsigned char amountOfComponents = ColorFormat::Get(m_format).amountOfComponents() ;
    unsigned int totalBufferSize = m_width * m_height * amountOfComponents ;
    data = m_pixelData ;
    size = totalBufferSize ;
}

unsigned int RawImage::width() const {
    return m_width ;
}

unsigned int RawImage::height() const {
    return m_height ;
}
