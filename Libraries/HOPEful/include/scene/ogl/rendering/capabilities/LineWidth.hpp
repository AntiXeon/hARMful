#ifndef __HOPE__GL_CAPABILITY_LINE_WIDTH__
#define __HOPE__GL_CAPABILITY_LINE_WIDTH__

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
            void setAntialiasing(const boolean isEnabled) {
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
            virtual void apply() {
                if (m_isAntialiased) {
                    enable(GL_LINE_SMOOTH) ;
                }

                glGetFloatv(GL_LINE_WIDTH, &m_oldWidth) ;
                glLineWidth(m_width) ;
            }

            /**
             * Remove the capability.
             */
            virtual void remove() {
                if (m_isAntialiased) {
                    if (m_width != m_oldWidth) {
                        glLineWidth(m_oldWidth) ;
                    }

                    disable(GL_LINE_SMOOTH) ;
                }
            }
    } ;
}

#endif
