#ifndef __HOPE__GL_CAPABILITY_COLOR_MASK__
#define __HOPE__GL_CAPABILITY_COLOR_MASK__

#include <utils/Platform.hpp>

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
             * Create a new ColorMask instance.
             */
            exported ColorMask() : Capability(CapabilityType::ColorMask) {}

            /**
             * Specify whether red is to be written into the frame buffer.
             */
            exported void setRedMask(const bool masked) {
                m_channels[Color::Channels::Red] = masked ;
            }

            /**
             * Specify whether green is to be written into the frame buffer.
             */
            exported void setGreenMask(const bool masked) {
                m_channels[Color::Channels::Green] = masked ;
            }

            /**
             * Specify whether blue is to be written into the frame buffer.
             */
            exported void setBlueMask(const bool masked) {
                m_channels[Color::Channels::Blue] = masked ;
            }

            /**
             * Specify whether alpha is to be written into the frame buffer.
             */
            exported void setAlphaMask(const bool masked) {
                m_channels[Color::Channels::Alpha] = masked ;
            }

        protected:
            /**
             * Apply the capability.
             */
            exported void apply() override ;

            /**
             * Remove the capability.
             */
            exported void remove() override ;
    } ;
}

#endif
