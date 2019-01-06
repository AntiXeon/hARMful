#ifndef __HOPE__GL_MESHPART__
#define __HOPE__GL_MESHPART__

#include <vector>
#include <ogl/GLDefines.hpp>
#include <GL/glew.h>

namespace Hope { namespace GL {

    class Vertex ;

    /**
     * A MeshPart is a subpart of a Mesh. A complex Mesh can have several parts.
     */
    class MeshPart final {
        private:
            /**
             * ID of the vertex buffer of this part.
             */
            GLuint m_vertexBuffer = INVALID_VALUE ;

            /**
             * ID of the index buffer of this part.
             */
            GLuint m_indexBuffer = INVALID_VALUE ;

            /**
             * Amount of indices of vertex in this part.
             */
            unsigned int m_amountIndices = 0 ;

            /**
             * Index of the material to draw this part.
             */
            unsigned int m_materialIndex = INVALID_MATERIAL ;

        public:
            /**
             * Destruction of the MeshPart.
             */
            ~MeshPart() ;

            /**
             * Initialize the MeshPart data.
             */
            bool initialize
            (
                const std::vector<Vertex>& vertices,
                const std::vector<uint32_t>& indices
            ) ;


            // Copy/move operations.
            MeshPart() = default ;
            MeshPart(const MeshPart& copied) = default ;
            MeshPart(MeshPart&& moved) = default ;
            MeshPart& operator=(const MeshPart& copied) = default ;
            MeshPart& operator=(MeshPart&& moved) = default ;
    } ;
}}

#endif
