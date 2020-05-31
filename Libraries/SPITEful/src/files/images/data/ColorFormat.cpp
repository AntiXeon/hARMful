#include <files/images/data/ColorFormat.hpp>
#include <SPITEStrings.hpp>
#include <stdexcept>
#include <iostream>

#define ByteSizeInBits  8

using namespace Spite ;

std::map<int, ColorFormat> ColorFormat::ColorFormats ;

ColorFormat::ColorFormat(
    const ColorFormat::ID id,
    const std::string& name,
    const unsigned char amountComponents,
    const unsigned char componentSize,
	const ColorFormat::ComponentType type
) : m_id(id),
    m_name(name),
    m_amountComponents(amountComponents),
    m_componentSize(componentSize),
    m_pixelSize(m_amountComponents * m_componentSize),
    m_colorDepth(amountComponents * ByteSizeInBits),
	m_type(type),
    m_isInitialized(true) {}


void ColorFormat::Create(
	const ColorFormat::ID id,
	const ColorFormat::ComponentType type
) {
    if (ColorFormats.count(id|type) == 0) {
        // Get the data on the wanted color format.
        std::string name ;
		unsigned char amountComponents ;
        unsigned char componentSize ;
        SetDataForFormat(id, type, name, amountComponents, componentSize) ;
        // Apply the data to the color format.
        ColorFormats[id|type] = ColorFormat(
            id,
            name,
            amountComponents,
            componentSize,
			type
        ) ;
    }
}

void ColorFormat::Clear() {
    ColorFormats.clear() ;
}

const ColorFormat& ColorFormat::Get(
    const ColorFormat::ID id,
	const ColorFormat::ComponentType type
) {
    Create(id, type) ;
    return ColorFormats.at(id|type) ;
}

ColorFormat::ID ColorFormat::id() const {
    return m_id ;
}

const std::string& ColorFormat::name() const {
    return m_name ;
}

unsigned char ColorFormat::amountOfComponents() const {
    return m_amountComponents ;
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

ColorFormat::ComponentType ColorFormat::type() const {
	return m_type ;
}

bool ColorFormat::isInitialized() const {
    return m_isInitialized ;
}


void ColorFormat::SetDataForFormat(
    const ColorFormat::ID& id,
    const ColorFormat::ComponentType& type,
    std::string& name,
    unsigned char& amountComponents,
    unsigned char& componentSize
) {
    switch (id) {
        case Gray:
            name = "Gray";
			amountComponents = 1 ;
            break;

        case GrayAlpha:
            name = "GrayAlpha";
            amountComponents = 2 ;
            break;

        case RGB:
            name = "RGB" ;
			amountComponents = 3 ;
            break ;

        case RGBA:
            name = "RGBA" ;
			amountComponents = 4 ;
            break ;

        default:
            throw std::invalid_argument(ColorFormatMsg::Error::UnknownFormat) ;
            break ;
    }

	switch (type) {
		case Byte:
			componentSize = static_cast<unsigned char>(sizeof(unsigned char)) ;
			break ;

        case Short:
			componentSize = static_cast<unsigned char>(sizeof(unsigned short)) ;
			break ;

		case FloatingPoint:
			componentSize = static_cast<unsigned char>(sizeof(float)) ;
			break ;

		default:
			throw std::invalid_argument(ColorFormatMsg::Error::UnknownFormat) ;
			break ;
	}
}
