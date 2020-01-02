#ifndef __HOPE__GL_CAPABILITY_POLYGON_OFFSET__
#define __HOPE__GL_CAPABILITY_POLYGON_OFFSET__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the polygon offset GL capability.
     */
    class PolygonOffset final : public Capability {
        private:
            struct Parameters {
                /**
                 * Scale factor that is used to create a variable depth offset
                 * for each polygon.
                 */
                GLfloat scaleFactor ;

                /**
                 * Is multiplied by an implementation-specific value to create a
                 * constant depth offset.
                 */
                GLfloat depthOffset ;

                bool operator==(const Parameters& other) {
                    return (scaleFactor == other.scaleFactor) &&
                            (depthOffset == other.depthOffset) ;
                }

                bool operator!=(const Parameters& other) {
                    return !(*this == other) ;
                }
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
             * Create a new PolygonOffset instance.
             */
            PolygonOffset() : Capability(CapabilityType::PolygonOffset) {}

            /**
             * Set the property to know if the point size can be changed from
             * shaders.
             */
            void setScaleFactor(const float scaleFactor) {
                m_current.scaleFactor = scaleFactor ;
            }

            /**
             * Set the depth offset.
             */
            void setDepthOffset(const float units) {
                m_current.depthOffset = units ;
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
