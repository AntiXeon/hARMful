#ifndef __HOPE__GL_VERTEX__
#define __HOPE__GL_VERTEX__

#include <geometry/points/Point2Df.hpp>
#include <geometry/points/Point3Df.hpp>
#include <vector>

namespace Hope::GL {
    /**
     * Vertex data.
     */
    class Vertex final
    {
        public:
            /**
             * Amount of values in a Vertex.
             */
            static const int AmountValues = 3 + 2 + 3 ;

            /**
             * Size of the vertex data in bytes.
             */
            static const int DataByteSize = AmountValues * sizeof(float);

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
                const Mind::Vector3f& normal
            ) ;

            /**
             * Move the vertex as an array of float values.
             * The order of the data is:
             * 0,1,2    => position(X,Y,Z)
             * 3,4      => texture(X,Y)
             * 5,6,7    => normal(X,Y,Z)
             */
            std::vector<float>& data() {
                return m_data ;
            }
    };
}

#endif
