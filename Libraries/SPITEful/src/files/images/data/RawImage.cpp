#include <files/images/data/RawImage.h>
#include <SPITEStrings.h>
#include <debug/Test.h>
#include <string.h>


namespace Spite {
                                              /** CONSTRUCTION / DESTRUCTION **/
    RawImage::RawImage(ColorFormat* format) : m_pixelData(NULL),
                                              m_format(format) {}

    RawImage::~RawImage() {
        if (m_pixelData != NULL) {
            delete[] m_pixelData ;
            m_pixelData = NULL ;
        }
    }

                                                             /*** UTILITIES ***/
    void RawImage::freeData() {
        if (m_pixelData != NULL) {
            delete[] m_pixelData ;
            m_pixelData = NULL ;
        }
    }

                                                     /*** SETTERS / GETTERS ***/
    void RawImage::setDimensions(
                                 const unsigned int& width,
                                 const unsigned int& height
                                ) {
        ABORT_CONDITION(
                        (m_format != NULL),
                        RawImageMsg::Error::UndefinedColorFormatWhenSettingSize
                       ) ;

        m_width = width ;
        m_height = height ;

        unsigned char amountOfComponents = m_format -> getAmountOfComponents() ;
        m_pixelData = new int[width * height * amountOfComponents] ;
    }

    bool RawImage::setFormat(ColorFormat* format) {
        if (m_format == NULL) {
            m_format = format ;
            return true ;
        }

        return false ;
    }

    const ColorFormat* RawImage::getFormat() const {
        return m_format ;
    }

    void RawImage::getData(void*& data, unsigned int& size) {
        const unsigned char AmountOfComponents = m_format -> getAmountOfComponents() ;
        const unsigned int TotalBufferSize = m_width * m_height * AmountOfComponents ;
        data = m_pixelData ;
        size = TotalBufferSize ;
    }


    unsigned int RawImage::getWidth() const {
        return m_width ;
    }

    unsigned int RawImage::getHeight() const {
        return m_height ;
    }

} ;
