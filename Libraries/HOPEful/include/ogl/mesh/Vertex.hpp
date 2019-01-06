#ifndef __HOPE__GL_VERTEX__
#define __HOPE__GL_VGERTEX__

#include <GL/glew.h>
#include <geometry/points/Point2Df.hpp>
#include <geometry/points/Point3Df.hpp>

namespace Hope { namespace GL {

    class Vertex final
    {
        private:
            /**
             * Position of the vertex in 3D space.
             */
            Mind::Vector3f m_pos = Mind::Vector3f() ;

            /**
             * UV coordinates of the vertex.
             */
            Mind::Vector2f m_tex = Mind::Vector2f() ;

            /**
             * Normal value of the vertex.
             */
            Mind::Vector3f m_normal = Mind::Vector3f() ;

        public:
            /**
             * Create a new vertex.
             */
            Vertex(
                const Mind::Vector3f& pos,
                const Mind::Vector2f& tex,
                const Mind::Vector3f& normal
            ) ;
    };

}}

#endif
