#ifndef __HOPE__GL_CAPABILITY_CLIP_PLANE__
#define __HOPE__GL_CAPABILITY_CLIP_PLANE__

#include <scene/ogl/rendering/capabilities/Capability.hpp>
#include <geometry/points/Point3Df.hpp>
#include <geometry/points/Point4Df.hpp>
#include <cstdint>

namespace Hope::GL {
    /**
     * Encapsulate the clip plane GL capability.
     */
    class ClipPlane final : public Capability {
        private:
            /**
             * Index of the plane. It must be a value in the range [0 - 7].
             */
            GLenum m_index = GL_CLIP_PLANE0 ;

            /**
             * Equation of the plane : (normal, distance).
             */
            double m_equation[4] ;

            /**
             * Store the old equation for restor.
             */
            double m_oldEquation[4] ;

        public:
            /**
             * Create a new ClipPlane instance.
             */
            ClipPlane() : Capability(CapabilityType::ClipPlane) {}

            /**
             * Set the plane index. It must be a value in the range [0 - 7].
             */
            void setPlaneIndex(const uint8_t index) ;

            /**
             * Set the distance of the plane from the camera.
             */
            void setDistance(const float distance) ;

            /**
             * Set the normal of the plane.
             */
            void setNormal(const Mind::Vector3f& normal) ;

            /**
             * Set the normal of the plane.
             */
            void setNormal(const float x, const float y, const float z) ;

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
