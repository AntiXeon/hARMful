#ifndef __HOPE__GL_CAPABILITY_FRONT_FACE__
#define __HOPE__GL_CAPABILITY_FRONT_FACE__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the front face GL capability.
     * Default orientation is counter clock-wise.
     */
    class FrontFace final : public Capability {
        public:
            /**
             * Possible face orientations.
             */
            enum class Orientation : GLenum {
                ClockWise = GL_CW,
                CounterClockWise = GL_CCW
            } ;

        private:
            /**
             * Orientation of front-facing polygons.
             */
            Orientation m_orientation = Orientation::CounterClockWise ;

            /**
             * Store the previous orientation before changing it. Allows
             * restoration when the capability is removed.
             */
            GLint m_oldOrientation ;

        public:
            /**
             * Set the buffer index.
             */
            void setOrientation(const Orientation orientation) {
                m_orientation = orientation ;
            }

        protected:
            /**
             * Apply the capability.
             */
            virtual void apply() {
                glGetIntegerv(GL_FRONT_FACE, &m_oldOrientation) ;

                if (m_orientation != m_oldOrientation) {
                    glFrontFace(m_orientation) ;
                }
            }

            /**
             * Remove the capability.
             */
            virtual void remove() {
                if (m_orientation != m_oldOrientation) {
                    glFrontFace(m_oldOrientation) ;
                }
            }
    } ;
}

#endif
