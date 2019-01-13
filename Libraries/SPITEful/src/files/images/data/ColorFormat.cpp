#include <files/images/data/ColorFormat.hpp>
#include <SPITEStrings.hpp>
#include <stdexcept>

#define ByteSizeInBits  8

using namespace Spite ;

std::vector<ColorFormat> ColorFormat::ColorFormats ;

ColorFormat::ColorFormat(
    const std::string& name,
    const std::vector<unsigned int>& components,
    const unsigned char& componentSize
) : m_name(name),
    m_componentMasks(components),
    m_componentSize(componentSize),
    m_pixelSize(components.size()),
    m_colorDepth(components.size() * ByteSizeInBits),
    m_isInitialized(true) {}


void ColorFormat::Initialize() {
    ColorFormats.resize(ColorFormat::AmountOfIDs, ColorFormat()) ;
}

void ColorFormat::Create(const ColorFormat::ID& id) {
    if (ColorFormats.size() == 0) {
        Initialize() ;
    }

    if (!ColorFormats[id].isInitialized()) {
        // Get the data on the wanted color format.
        std::string name ;
        std::vector<unsigned int> components ;
        unsigned char componentSize ;
        SetDataForFormat(id, name, components, componentSize) ;

        // Apply the data to the color format.
        ColorFormats[id] = ColorFormat(
            name,
            components,
            componentSize
        ) ;
    }
}

void ColorFormat::Clear() {
    ColorFormats.clear() ;
}

ColorFormat& ColorFormat::Get(const ColorFormat::ID& id) {
    Create(id) ;
    return ColorFormats[id] ;
}


const std::string& ColorFormat::name() const {
    return m_name ;
}

unsigned char ColorFormat::amountOfComponents() const {
    return m_componentMasks.size() ;
}

unsigned char ColorFormat::pixelSizeInBytes() const {
    return m_pixelSize ;
}

unsigned char ColorFormat::colorDepth() const {
    return m_colorDepth ;
}

unsigned char ColorFormat::componentSize() const {
    return m_componentSize ;
}

unsigned int ColorFormat::mask(const unsigned int& componentID) const {
    if (componentID < m_componentMasks.size()) {
        return m_componentMasks[componentID] ;
    }
    else {
        return 0 ;
    }
}

bool ColorFormat::isInitialized() const {
    return m_isInitialized ;
}


void ColorFormat::SetDataForFormat(
    const ColorFormat::ID& id,
    std::string& name,
    std::vector<unsigned int>& components,
    unsigned char& componentSize
) {
    switch (id) {
        case RGB:
            name = "RGB" ;
            components.resize(3) ;
            components[0] = 0x000000FF ;
            components[1] = 0x0000FF00 ;
            components[2] = 0x00FF0000 ;
            componentSize = sizeof(unsigned int) ;
            break ;

        case BGR:
            name = "BGR" ;
            components.resize(3) ;
            components[0] = 0xFF000000 ;
            components[1] = 0x00FF0000 ;
            components[2] = 0x0000FF00 ;
            componentSize = sizeof(unsigned int) ;
            break ;

        case RGBA:
            name = "RGBA" ;
            components.resize(4) ;
            components[0] = 0x000000FF ;
            components[1] = 0x0000FF00 ;
            components[2] = 0x00FF0000 ;
            components[3] = 0xFF000000 ;
            componentSize = sizeof(unsigned int) ;
            break ;

        case ARGB:
            name = "ARGB" ;
            components.resize(4) ;
            components[0] = 0xFF000000 ;
            components[1] = 0x00FF0000 ;
            components[2] = 0x0000FF00 ;
            components[3] = 0x000000FF ;
            componentSize = sizeof(unsigned int) ;
            break ;

        case YUV:
            name = "YUV" ;
            components.resize(3) ;
            components[0] = 0xFF000000 ;
            components[1] = 0x00FF0000 ;
            components[2] = 0x0000FF00 ;
            componentSize = sizeof(unsigned int) ;
            break ;

        case YCbCr:
            name = "YCbCr" ;
            components.resize(3) ;
            components[0] = 0xFF000000 ;
            components[1] = 0x00FF0000 ;
            components[2] = 0x0000FF00 ;
            componentSize = sizeof(unsigned int) ;
            break ;

        case CMYK:
            name = "CMYK" ;
            components.resize(4) ;
            components[0] = 0xFF000000 ;
            components[1] = 0x00FF0000 ;
            components[2] = 0x0000FF00 ;
            components[3] = 0x000000FF ;
            componentSize = sizeof(unsigned int) ;
            break ;

        case YCCK:
            name = "YCCK" ;
            components.resize(4) ;
            components[0] = 0xFF000000 ;
            components[1] = 0x00FF0000 ;
            components[2] = 0x0000FF00 ;
            components[3] = 0x000000FF ;
            componentSize = sizeof(unsigned int) ;
            break ;

        case Gray:
            name = "Gray" ;
            components.resize(1) ;
            components[0] = 0xFF000000 ;
            componentSize = sizeof(unsigned int) ;
            break ;

        default:
            throw std::invalid_argument(ColorFormatMsg::Error::UnknownFormat) ;
            break ;
    }
}
