#include <Fractals/graphics/PixelColor.h>
#include <DOOMful/utils/Processor.h>

PixelColor::PixelColor(int red, int green, int blue) {
    // m_mutex.lock() ;
        m_red = red ;
        m_green = green ;
        m_blue = blue ;
        setHexadecimalRepresentation() ;
    // m_mutex.unlock() ;
}

PixelColor::~PixelColor() {}


int PixelColor::getRed() const {
    // m_mutex.lock() ;
        int red = m_red ;
    // m_mutex.unlock() ;
    return red ;
}

int PixelColor::getGreen() const {
    // m_mutex.lock() ;
        int green = m_green ;
    // m_mutex.unlock() ;
    return green ;
}

int PixelColor::getBlue() const {
    // m_mutex.lock() ;
        int blue = m_blue ;
    // m_mutex.unlock() ;
    return blue ;
}

PixelColor::operator int() const {
    // m_mutex.lock() ;
        int hexa = m_hexadecimal ;
    // m_mutex.unlock() ;
    return hexa ;
}

void PixelColor::setHexadecimalRepresentation() {
    const unsigned char Alpha = 255 ;

    if (CPU_Endianness() == BigEndian) {
        m_hexadecimal = (m_red << 24) |
                            (m_green << 16) |
                            (m_blue << 8) |
                            Alpha ;
    }
    else {
        m_hexadecimal = (Alpha << 24) |
                            (m_blue << 16) |
                            (m_green << 8) |
                            m_red ;
    }
}
