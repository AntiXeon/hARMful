#ifndef __HOPE__GL_CAPABILITY_POINT_SIZE__
#define __HOPE__GL_CAPABILITY_POINT_SIZE__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the point size GL capability.
     */
    class PointSize final : public Capability {
        private:
            struct Parameters {
                /**
                 * To know if the point size can be changed from shaders.
                 */
                GLboolean isProgrammable ;

                /**
                 * Point size.
                 */
                GLfloat size ;
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
             * Create a new PointSize instance.
             */
            PointSize() : Capability(CapabilityType::PointSize) {}

            /**
             * Set the property to know if the point size can be changed from
             * shaders.
             */
            void setProgrammable(const bool isProgrammable) {
                m_current.isProgrammable = isProgrammable ;
            }

            /**
             * Set the line width.
             */
            void setSize(const float size) {
                m_current.size = size ;
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
