#ifndef __SPITE_COLOR_FORMAT__
#define __SPITE_COLOR_FORMAT__


#include <string>
#include <vector>
#include <exceptions/UnexpectedValueException.h>


namespace Spite {

    /**
     * @brief   Class to contain informations on color format used by pictures.
     *
     * @author  Denis CARLUS
     * @version 1.0     03/10/2016
     */
    class ColorFormat {
        public:
            /**
             * @brief   IDs to identity the supported color formats.
             */
            enum ID {
                     RGB = 0,
                     BGR,
                     RGBA,
                     ARGB,
                     YUV,
                     AmountOfIDs
                    } ;

        private:
            /**
             * @brief   All the available ColorFormat to describe the
             *          organization of data inside the raw images.
             */
            static std::vector<ColorFormat> ColorFormats ;


            /**
             * @brief   Name of the ColorFormat.
             */
            std::string m_name ;

            /**
             * @brief   Mask of the components.
             */
            std::vector<unsigned int> m_componentMasks ;

            /**
             * @brief   Size of each component in bytes.
             */
            unsigned char m_componentSize ;

            /**
             * @brief   Total size of each pixel information in bytes.
             */
            unsigned char m_pixelSize ;

            /**
             * @brief   Color depth of the ColorFormat.
             */
            unsigned char m_colorDepth ;

            /**
             * @brief   To check if a ColorFormat has been initialized.
             */
            bool m_isInitialized ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Empty constructor, just for optimization.
             */
            ColorFormat() ;

            /**
             * @brief   Create a new ColorFormat.
             * @param   name                Name of the ColorFormat.
             * @param   components          Components in the ColorFormat.
             * @param   componentSize       Size of each component in bytes.
             */
            ColorFormat(
                        const std::string& name,
                        const std::vector<unsigned int>& components,
                        const unsigned char& componentSize
                       ) ;

            /**
             * @brief   Destruction of the ColorFormat.
             */
            virtual ~ColorFormat() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Initialize the class for standard color formats.
             */
            static void Initialize() ;

            /**
             * @brief   Create a ColorFormat.
             * @param   id  ID of the ColorFormat.
             */
            static void Create(const ColorFormat::ID& id) throw (Doom::UnexpectedValueException) ;

            /**
             * @brief   Clear all ColorFormat instances.
             */
            static void Clear() ;

                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the wanted ColorFormat.
             * @param   id  ID of the ColorFormat to get.
             * @return  The wanted ColorFormat.
             */
            static ColorFormat& Get(const ColorFormat::ID& id) ;


            /**
             * @brief   Get the name of the ColorFormat.
             * @return  Name of the ColorFormat.
             */
            const std::string& getName() const ;

            /**
             * @brief   Get the amount of components used in the ColorFormat.
             * @return  Amount of components in the ColorFormat.
             */
            unsigned char getAmountOfComponents() const ;

            /**
             * @brief   Get the total size in bytes of each pixel information.
             * @return  Amount of bytes used to represent each pixel of an image.
             */
            unsigned char getPixelSizeInBytes() const ;

            /**
             * @brief   Get the color depth of the ColorFormat.
             * @return  Color depth in bits.
             */
            unsigned char getColorDepth() const ;

            /**
             * @brief   Get the size of each component in bytes.
             * @return  Size of a component in bytes.
             */
            unsigned char getComponentSize() const ;

            /**
             * @brief   Get the mask of the wanted component.
             * @param   componentID ID of the component for which the mask is
             *                      wanted.
             * @return  The mask for the given @a componentID.
             */
            unsigned int getMask(const unsigned int& componentID) const ;


        private:
            /**
             * @brief   Check if a ColorFormat has been initialized.
             * @return  TRUE if initialized, FALSE else.
             */
            bool isInitialized() const ;

            /**
             * @brief   Set the data for the given ID of color format.
             * @param   id                  ID of the ColorFormat.
             * @param   name                Name of the ColorFormat.
             * @param   components          Components in the ColorFormat.
             * @param   componentSize       Size of each component in bytes.
             */
            static void SetDataForFormat(
                                         const ColorFormat::ID& id,
                                         std::string& name,
                                         std::vector<unsigned int>& components,
                                         unsigned char& componentSize
                                        ) throw(Doom::UnexpectedValueException) ;
    } ;

} ;

#endif
