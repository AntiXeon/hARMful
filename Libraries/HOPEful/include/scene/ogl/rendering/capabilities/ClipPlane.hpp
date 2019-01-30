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
             * Set the plane index. It must be a value in the range [0 - 7].
             */
            void setPlaneIndex(const uint8_t index) {
                if (index > 7) {
                    index = 7 ;
                }

                m_index = GL_CLIP_PLANE0 + index ;
            }

            /**
             * Set the distance of the plane from the camera.
             */
            void setDistance(const float distance) {
                m_equation[0] = m_equation.get(Mind::Vector4f::X) ;
                m_equation[1] = m_equation.get(Mind::Vector4f::Y) ;
                m_equation[2] = m_equation.get(Mind::Vector4f::Z) ;
                m_equation[3] = -distance ;
            }

            /**
             * Set the normal of the plane.
             */
            void setNormal(const Mind::Vector3f& normal) {
                m_equation[0] = normal.get(Mind::Vector3f::X) ;
                m_equation[1] = normal.get(Mind::Vector3f::Y) ;
                m_equation[2] = normal.get(Mind::Vector3f::Z) ;
                m_equation[3] = m_equation.get(Mind::Vector4f::W) ;
            }

            /**
             * Set the normal of the plane.
             */
            void setNormal(const float x, const float y, const float z) {
                m_equation[0] = x ;
                m_equation[1] = y ;
                m_equation[2] = z ;
                m_equation[3] = m_equation.get(Mind::Vector4f::W) ;
            }

        protected:
            /**
             * Apply the capability.
             */
            virtual void apply() {
                glEnable(m_index) ;
                glGetClipPlane(m_index, m_oldEquation) ;
                glClipPlane(m_index, m_equation) ;
            }

            /**
             * Remove the capability.
             */
            virtual void remove() {
                glClipPlane(m_index, m_oldEquation) ;
                glDisable(m_index) ;
            }
    } ;
}

#endif
