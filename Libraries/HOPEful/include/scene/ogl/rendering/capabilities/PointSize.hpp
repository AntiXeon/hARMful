#ifndef __HOPE__GL_CAPABILITY_POINT_SIZE__
#define __HOPE__GL_CAPABILITY_POINT_SIZE__

#include <utils/Platform.hpp>

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
            exported PointSize() : Capability(CapabilityType::PointSize) {}

            /**
             * Set the property to know if the point size can be changed from
             * shaders.
             */
            exported void setProgrammable(const bool isProgrammable) {
                m_current.isProgrammable = isProgrammable ;
            }

            /**
             * Set the line width.
             */
            exported void setSize(const float size) {
                m_current.size = size ;
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
