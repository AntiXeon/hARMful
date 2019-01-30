#ifndef __HOPE__GL_CAPABILITY_POLYGON_OFFSET__
#define __HOPE__GL_CAPABILITY_POLYGON_OFFSET__

namespace Hope::GL {
    /**
     * Encapsulate the polygon offset GL capability.
     */
    class PolygonOffset final : public Capability {
        private:
            /**
             * Scale factor that is used to create a variable depth offset for
             * each polygon.
             */
            GLfloat m_scaleFactor ;

            /**
             * Store the old scale factor for restoring it after the application
             * of the capability.
             */
            GLfloat m_oldScaleFactor ;

            /**
             * Is multiplied by an implementation-specific value to create a
             * constant depth offset.
             */
            GLfloat m_depthOffset ;

            /**
             * Store the old depth offset for restoring it after the application
             * of the capability.
             */
            GLfloat m_oldDepthOffset ;

        public:
            /**
             * Set the property to know if the point size can be changed from
             * shaders.
             */
            void setScaleFactor(const float scaleFactor) {
                m_scaleFactor = scaleFactor ;
            }

            /**
             * Set the depth offset.
             */
            void setDepthOffset(const float units) {
                m_depthOffset = units ;
            }

        protected:
            /**
             * Apply the capability.
             */
            virtual void apply() {
                enable(GL_POLYGON_OFFSET_FILL) ;
                glGet(GL_POLYGON_OFFSET_FACTOR, &m_oldScaleFactor) ;
                glGet(GL_POLYGON_OFFSET_UNITS, &m_oldDepthOffset) ;

                if ((m_scaleFactor != m_oldScaleFactor) && (m_depthOffset != m_oldDepthOffset)) {
                    glPolygonOffset(m_scaleFactor, m_depthOffset) ;
                }
            }

            /**
             * Remove the capability.
             */
            virtual void remove() {
                if ((m_scaleFactor != m_oldScaleFactor) && (m_depthOffset != m_oldDepthOffset)) {
                    glPolygonOffset(m_oldScaleFactor, m_oldDepthOffset) ;
                }

                disable(GL_POLYGON_OFFSET_FILL) ;
            }
    } ;
}

#endif
