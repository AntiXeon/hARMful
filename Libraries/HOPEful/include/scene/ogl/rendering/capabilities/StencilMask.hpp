#ifndef __HOPE__GL_CAPABILITY_STENCIL_MASK__
#define __HOPE__GL_CAPABILITY_STENCIL_MASK__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Control the front and/or back writing of individual bits in the stencil
     * planes.
     */
    class StencilMask final : public Capability {
        private:
            struct Parameters {
                /**
                 * Bit mask to enable and disable writing of individual bits in
                 * the stencil planes.
                 */
                GLuint front = 1 ;

                /**
                 * Bit mask to enable and disable writing of individual bits in
                 * the stencil planes.
                 */
                GLuint back = 1 ;
            } ;

            /**
             * Current parameters.
             */
            Parameters m_current ;

            /**
             * Store old parameters for restore.
             */
            Parameters m_old ;

        public:
            /**
             * Create a new StencilMask instance.
             */
            exported StencilMask() : Capability(CapabilityType::StencilMask) {}

            /**
             * Set the bit mask to enable and disable writing of individual bits
             * in the stencil planes.
             */
            exported void setFrontMask(const uint32_t mask) {
                m_current.front = mask ;
            }

            /**
             * Set the bit mask to enable and disable writing of individual bits
             * in the stencil planes.
             */
            exported void setBackMask(const uint32_t mask) {
                m_current.back = mask ;
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
