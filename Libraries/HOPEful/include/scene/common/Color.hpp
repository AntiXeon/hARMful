#ifndef __HOPE__COLOR__
#define __HOPE__COLOR__

#include <algorithm>
#include <array>
#include <cstdint>

namespace Hope {
    /**
     * Represent a color in RGBA color space.
     */
    class Color final {
        public:
            /**
             * Color channels (RGBA).
             */
            enum Channels : char {
                Red,
                Green,
                Blue,
                Alpha,
                AmountChannels
            } ;

        private:
            /**
             * Red channel.
             */
            float m_red ;

            /**
             * Green channel.
             */
            float m_green ;

            /**
             * Blue channel.
             */
            float m_blue ;

            /**
             * Alpha channel (transparency).
             */
            float m_alpha ;

        public:
            /**
             * Create a new Color.
             * @param   red     Red channel.
             * @param   green   Green channel.
             * @param   blue    Blue channel.
             * @param   alpha   Alpha channel.
             */
            Color(
                const float red = 0.f,
                const float green = 0.f,
                const float blue = 0.f,
                const float alpha = 1.f
            ) {
                m_red = std::clamp(red, 0.f, 1.f) ;
                m_green = std::clamp(green, 0.f, 1.f) ;
                m_blue = std::clamp(blue, 0.f, 1.f) ;
                m_alpha = std::clamp(alpha, 0.f, 1.f) ;
            }

            /**
             * Create a new Color.
             * @param   color   Hexadecimal representation of a RGBA color.
             */
            Color(const int32_t color) {
                uint8_t red = (color & 0xFF000000) >> 24 ;
                uint8_t green = (color & 0x00FF0000) >> 16 ;
                uint8_t blue = (color & 0x0000FF00) >> 8 ;
                uint8_t alpha = (color & 0x000000FF) >> 0 ;
                convertFromUInt8(red, green, blue, alpha) ;
            }

            /**
             * Create a new Color.
             * @param   red     Red channel.
             * @param   green   Green channel.
             * @param   blue    Blue channel.
             * @param   alpha   Alpha channel.
             */
            Color(
                const uint8_t red,
                const uint8_t green,
                const uint8_t blue,
                const uint8_t alpha = 255
            ) {
                convertFromUInt8(red, green, blue, alpha) ;
            }

            /**
             * Get the red channel value.
             */
            float red() const {
                return m_red ;
            }

            /**
             * Get the red channel value.
             */
            float green() const {
                return m_green ;
            }

            /**
             * Get the red channel value.
             */
            float blue() const {
                return m_blue ;
            }

            /**
             * Get the red channel value.
             */
            float alpha() const {
                return m_alpha ;
            }

            /**
             * Export the color to a RGB value array.
             */
            std::array<float, 3> toRGB() const {
                return { m_red, m_green, m_blue } ;
            }

            /**
             * Export the color to a RGBA value array.
             */
            std::array<float, 4> toRGBA() const {
                return { m_red, m_green, m_blue, m_alpha } ;
            }

        private:
            /**
             * Convert a color given as UInt8 values
             */
            void convertFromUInt8(
                const uint8_t red,
                const uint8_t green,
                const uint8_t blue,
                const uint8_t alpha
            ) {
                const float MaxValue = static_cast<float>(UINT8_MAX) ;
                m_red = static_cast<float>(red) / MaxValue ;
                m_green = static_cast<float>(green) / MaxValue ;
                m_blue = static_cast<float>(blue) / MaxValue ;
                m_alpha = static_cast<float>(alpha) / MaxValue ;
            }
    } ;
}

#endif
