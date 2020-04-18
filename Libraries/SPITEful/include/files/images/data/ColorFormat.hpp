#ifndef __SPITE__COLOR_FORMAT__
#define __SPITE__COLOR_FORMAT__

#include <utils/Platform.hpp>
#include <string>
#include <map>

namespace Spite {

    /**
     * Class to contain informations on color format used by pictures.
     */
    class ColorFormat final {
        public:
            /**
             * Format to identity the supported color formats.
             */
            enum ID {
                UnknownID 	= 0x00,
                Gray 		= 0x01,
                GrayAlpha 	= 0x02,
                RGB 		= 0x03,
                RGBA 		= 0x04
            } ;

			/**
			 * Format of data storage in the picture for each component.
			 */
			enum ComponentType {
				UnknownType   = 0x10,
				Byte		  = 0x20,
				FloatingPoint = 0x30
			} ;

        private:
			static const unsigned char AmountOfIDs = 5 ;
			static const unsigned char AmountOfTypes = 2 ;

			/**
			 * Amount of available IDs.
			 */
			static const unsigned char AmountOfFormats = AmountOfIDs * AmountOfTypes ;

			/**
			 * All the available ColorFormat to describe the organization of
			 * data inside the raw images.
			 */
			static std::map<int, ColorFormat> ColorFormats ;

            /**
             * ID of the color format.
             */
            ID m_id ;

            /**
             * Name of the ColorFormat.
             */
            std::string m_name ;

			/**
			 * Amount components.
			 */
			unsigned char m_amountComponents = 0 ;

            /**
             * Size of each component in bytes.
             */
            unsigned char m_componentSize = 0 ;

            /**
             * Total size of each pixel information in bytes.
             */
            unsigned char m_pixelSize = 0 ;

            /**
             * Color depth of the ColorFormat.
             */
            unsigned char m_colorDepth = 0 ;

			/**
			 * Format of data storage in the picture for each component.
			 */
			ComponentType m_type ;

            /**
             * To check if a ColorFormat has been initialized.
             */
            bool m_isInitialized = false ;


        public:
            /**
             * Empty constructor, just for optimization.
             */
            exported ColorFormat() = default ;

            /**
             * Create a new ColorFormat.
             * @param   id                  ID of the ColorFormat.
             * @param   name                Name of the ColorFormat.
             * @param   amountComponents 	Amount of components.
             * @param   componentSize       Size of each component in bytes.
			 * @param 	type				Format of data storage.
             */
            exported ColorFormat(
				const ColorFormat::ID id,
			    const std::string& name,
			    const unsigned char amountComponents,
			    const unsigned char componentSize,
				const ColorFormat::ComponentType type
            ) ;

            /**
             * Create a ColorFormat.
             * @param   id  	ID of the ColorFormat.
			 * @param 	type	Data type.
             */
            exported static void Create(
				const ColorFormat::ID id,
				const ColorFormat::ComponentType type
			) ;

            /**
             * Clear all ColorFormat instances.
             */
            exported static void Clear() ;

            /**
             * Get the wanted ColorFormat.
             * @param   id  	ID of the ColorFormat.
			 * @param 	type	Data type.
             * @return  The wanted ColorFormat.
             */
            exported static const ColorFormat& Get(
                const ColorFormat::ID id,
				const ColorFormat::ComponentType type
            ) ;

            /**
             * Get the ID of the ColorFormat.
             * @return  ID of the ColorFormat.
             */
            exported ID id() const ;

            /**
             * Get the name of the ColorFormat.
             * @return  Name of the ColorFormat.
             */
            exported const std::string& name() const ;

            /**
             * Get the amount of components used in the ColorFormat.
             * @return  Amount of components in the ColorFormat.
             */
            exported unsigned char amountOfComponents() const ;

            /**
             * Get the total size in bytes of each pixel information.
             * @return  Amount of bytes used to represent each pixel of an image.
             */
            exported unsigned char pixelSizeInBytes() const ;

            /**
             * Get the color depth of the ColorFormat.
             * @return  Color depth in bits.
             */
            exported unsigned char colorDepth() const ;

            /**
             * Get the size of each component in bytes.
             * @return  Size of a component in bytes.
             */
            exported unsigned char componentSize() const ;

			/**
			 * Format of data storage in the picture for each component.
			 * @return 	Format of data storage.
			 */
			exported ComponentType type() const ;

        private:
            /**
             * Check if a ColorFormat has been initialized.
             * @return  TRUE if initialized, FALSE else.
             */
            bool isInitialized() const ;

            /**
             * Set the data for the given ID of color format.
			 * @param   id                  ID of the ColorFormat.
             * @param 	type				Format of data storage.
             * @param   name                Name of the ColorFormat.
             * @param   amountComponents 	Amount of components.
             * @param   componentSize       Size of each component in bytes.
             */
            static void SetDataForFormat(
				const ColorFormat::ID& id,
                const ColorFormat::ComponentType& type,
			    std::string& name,
			    unsigned char& amountComponents,
			    unsigned char& componentSize
            ) ;
    } ;
}

#endif
