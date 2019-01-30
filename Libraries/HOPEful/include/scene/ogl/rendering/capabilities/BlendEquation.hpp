#ifndef __HOPE__GL_CAPABILITY_BLEND_EQUATION__
#define __HOPE__GL_CAPABILITY_BLEND_EQUATION__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the blend equation GL capability.
     */
    class BlendEquation final : public Capability {
        public:
            /**
             * Possible blend modes.
             */
            enum class BlendMode : GLenum {
                Add = GL_FUNC_ADD,
                Substract = GL_FUNC_SUBTRACT,
                ReverseSubstract = GL_FUNC_REVERSE_SUBTRACT,
                Min = GL_MIN,
                Max = GL_MAX
            } ;

        private:
            /**
             * The blend mode that is used.
             */
            BlendMode m_mode = BlendMode::Add ;

        public:
            /**
             * Set the blend mode that is used.
             */
            void setBlendMode(const BlendMode& mode) {
                m_mode = mode ;
            }

        protected:
            /**
             * Apply the capability.
             */
            virtual void apply() {
                glEnable(GL_BLEND) ;
                glBlendEquation(m_mode) ;
            }

            /**
             * Remove the capability.
             */
            virtual void remove() {
                glDisable(GL_BLEND) ;
            }
    } ;
}

#endif
