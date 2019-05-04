#ifndef __HOPE__GL_VERTEX__
#define __HOPE__GL_VERTEX__

#include <geometry/points/Point2Df.hpp>
#include <geometry/points/Point3Df.hpp>
#include <vector>

namespace Hope::GL {
    /**
     * Vertex data.
     */
    class Vertex final {
        public:
            /**
             * Amount of values for position.
             */
            static const unsigned char PositionLength = 3 ;

            /**
             * Amount of values for texture coordinates.
             */
            static const unsigned char TexCoordLength = 2 ;

            /**
             * Amount of values for normal.
             */
            static const unsigned char NormalLength = 3 ;

            /**
             * Amount of values for tangent.
             */
            static const unsigned char TangentLength = 3 ;

            /**
             * Amount of values for bitangent.
             */
            static const unsigned char BitangentLength = 3 ;

            /**
             * Amount of values in a Vertex.
             */
            static const unsigned char TotalLength = PositionLength + TexCoordLength + NormalLength + TangentLength + BitangentLength ;

        private:
            /**
             * Data of the vertex as an array of float values.
             */
            std::vector<float> m_data ;

        public:
            /**
             * Create a new vertex.
             */
            Vertex(
                const Mind::Vector3f& pos,
                const Mind::Vector2f& tex,
                const Mind::Vector3f& normal,
                const Mind::Vector3f& tangent,
                const Mind::Vector3f& bitangent
            ) ;

            /**
             * Move the vertex as an array of float values.
             * The order of the data is:
             * 0,1,2    => position(X,Y,Z)
             * 3,4      => texture(X,Y)
             * 5,6,7    => normal(X,Y,Z)
             * 8,9,10   => tangent(X,Y,Z)
             */
            std::vector<float>& data() {
                return m_data ;
            }
    };
}

#endif
