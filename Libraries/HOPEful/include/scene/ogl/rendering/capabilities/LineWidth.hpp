#ifndef __HOPE__GL_CAPABILITY_LINE_WIDTH__
#define __HOPE__GL_CAPABILITY_LINE_WIDTH__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the line width GL capability.
     */
    class LineWidth final : public Capability {
        private:
            /**
             * Are the lines antialiased?
             */
            GLboolean m_isAntialiased = GL_TRUE ;

            /**
             * Line width.
             */
            GLfloat m_width ;

            /**
             * Store the old width for restoring it after the application of the
             * capability.
             */
            GLfloat m_oldWidth ;

        public:
            /**
             * Set the antialising of the width.
             * Default value if true.
             */
            void setAntialiasing(const bool isEnabled) {
                m_isAntialiased = isEnabled ;
            }

            /**
             * Set the line width.
             */
            void setWidth(const float width) {
                m_width = width ;
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
