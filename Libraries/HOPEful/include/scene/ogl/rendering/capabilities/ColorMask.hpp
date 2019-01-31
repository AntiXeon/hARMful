#ifndef __HOPE__GL_CAPABILITY_COLOR_MASK__
#define __HOPE__GL_CAPABILITY_COLOR_MASK__

#include <scene/ogl/rendering/capabilities/Capability.hpp>
#include <scene/common/Color.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the color mask GL capability.
     */
    class ColorMask final : public Capability {
        private:
            /**
             * Channels are to be written into the frame buffer.
             */
            GLboolean m_channels[Color::Channels::AmountChannels] ;

            /**
             * Store the old channels for restore.
             */
            GLboolean m_oldChannels[Color::Channels::AmountChannels] ;

        public:
            /**
             * Specify whether red is to be written into the frame buffer.
             */
            void setRedMask(const bool masked) {
                m_channels[Color::Channels::Red] = masked ;
            }

            /**
             * Specify whether green is to be written into the frame buffer.
             */
            void setGreenMask(const bool masked) {
                m_channels[Color::Channels::Green] = masked ;
            }

            /**
             * Specify whether blue is to be written into the frame buffer.
             */
            void setBlueMask(const bool masked) {
                m_channels[Color::Channels::Blue] = masked ;
            }

            /**
             * Specify whether alpha is to be written into the frame buffer.
             */
            void setAlphaMask(const bool masked) {
                m_channels[Color::Channels::Alpha] = masked ;
            }

        protected:
            /**
             * Apply the capability.
             */
            void apply() override ;

            /**
             * Remove the capability.
             */
            void remove() override ;
    } ;
}

#endif
