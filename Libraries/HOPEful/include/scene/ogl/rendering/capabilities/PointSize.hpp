#ifndef __HOPE__GL_CAPABILITY_POINT_SIZE__
#define __HOPE__GL_CAPABILITY_POINT_SIZE__

namespace Hope::GL {
    /**
     * Encapsulate the point size GL capability.
     */
    class PointSize final : public Capability {
        private:
            /**
             * To know if the point size can be changed from shaders.
             */
            GLboolean m_isProgrammable ;

            /**
             * Store the old programmable property for restoring it after the
             * application of the capability.
             */
            GLboolean m_wasProgrammable ;

            /**
             * Point size.
             */
            GLfloat m_size ;

            /**
             * Store the old size for restoring it after the application of the
             * capability.
             */
            GLfloat m_oldSize ;

        public:
            /**
             * Set the property to know if the point size can be changed from
             * shaders.
             */
            void setProgrammable(const boolean isProgrammable) {
                m_isProgrammable = isProgrammable ;
            }

            /**
             * Set the line width.
             */
            void setSize(const float size) {
                m_size = size ;
            }

        protected:
            /**
             * Apply the capability.
             */
            virtual void apply() {
                if (m_isProgrammable) {
                    enable(GL_PROGRAM_POINT_SIZE) ;
                }

                glGetFloatv(GL_POINT_SIZE, &m_oldSize) ;

                if (m_size != m_oldSize) {
                    glPointSize(m_size) ;
                }
            }

            /**
             * Remove the capability.
             */
            virtual void remove() {
                if (m_size != m_oldSize) {
                    glPointSize(m_oldSize) ;
                }

                if (m_isProgrammable) {
                    disable(GL_PROGRAM_POINT_SIZE) ;
                }
            }
    } ;
}

#endif
