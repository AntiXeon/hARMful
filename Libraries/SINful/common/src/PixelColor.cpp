#include <PixelColor.h>
#include <utils/Processor.h>


namespace Sin {
                                              /** CONSTRUCTION / DESTRUCTION **/
    PixelColor::PixelColor(int red, int green, int blue) {
            m_red = red ;
            m_green = green ;
            m_blue = blue ;
            setHexadecimalRepresentation() ;
    }

    PixelColor::~PixelColor() {}

                                                     /*** SETTERS / GETTERS ***/
    int PixelColor::getRed() const {
        int red = m_red ;
        return red ;
    }

    int PixelColor::getGreen() const {
        int green = m_green ;
        return green ;
    }

    int PixelColor::getBlue() const {
        int blue = m_blue ;
        return blue ;
    }

    PixelColor::operator int() const {
        int hexa = m_hexadecimal ;
        return hexa ;
    }

    void PixelColor::setRed(const int& red) {
        m_red = red ;
        setHexadecimalRepresentation() ;
    }

    void PixelColor::setGreen(const int& green) {
        m_green = green ;
        setHexadecimalRepresentation() ;
    }

    void PixelColor::setBlue(const int& blue) {
        m_blue = blue ;
        setHexadecimalRepresentation() ;
    }

    void PixelColor::setColor(
                              const int& red,
                              const int& green,
                              const int& blue
                             ) {
        m_red = red ;
        m_green = green ;
        m_blue = blue ;
        setHexadecimalRepresentation() ;
    }


    void PixelColor::setHexadecimalRepresentation() {
        const unsigned char Alpha = 255 ;

        if (Doom::Processor::GetEndianness() == Doom::Processor::BigEndian) {
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

} ;
