#ifndef __HOPE__GL_MESHPART__
#define __HOPE__GL_MESHPART__

#include <vector>
#include <scene/ogl/GLDefines.hpp>
#include <GL/glew.h>
#include <cstdint>

namespace Hope::GL {

    class Vertex ;

    /**
     * A MeshPart is a subpart of a Mesh. A complex Mesh can have several parts.
     */
    class MeshPart final {
        private:
            /**
             * ID of the VAO.
             */
            GLuint m_vertexArray = INVALID_VALUE ;

            /**
             * ID of the vertex buffer of this part.
             */
            GLuint m_vertexBuffer = INVALID_VALUE ;

            /**
             * ID of the index buffer of this part.
             */
            GLuint m_indexBuffer = INVALID_VALUE ;

            /**
             * Index of the material to draw this part.
             */
            uint32_t m_materialIndex = INVALID_MATERIAL ;

            /**
             * Indices of the vertices.
             */
            std::vector<uint32_t> m_indices ;

        public:
            /**
             * Destruction of the MeshPart.
             */
            ~MeshPart() ;

            /**
             * Initialize the MeshPart data.
             */
            bool initialize(
                const std::vector<float>& vertices,
                const std::vector<uint32_t>& indices
            ) ;

            /**
             * Get the vertex buffer ID.
             */
            GLuint vertexBufferID() const {
                return m_vertexBuffer ;
            }

            /**
             * Get the index buffer ID.
             */
            GLuint indexBufferID() const {
                return m_indexBuffer ;
            }

            /**
             * Index of the material to draw this part.
             */
            uint32_t materialIndex() const {
                return m_materialIndex ;
            }

            /**
             * Amount of indices of vertex in this part.
             */
            uint32_t amountIndices() const {
                return m_indices.size() ;
            }

            /**
             * Indices of the vertices.
             */
            const uint32_t* indices() const {
                return m_indices.data() ;
            }

            /**
             * Bind the VAO of the mesh part.
             */
            void bind() const {
                glBindVertexArray(m_vertexArray) ;
            }

            // Copy/move operations.
            MeshPart() = default ;
            MeshPart(const MeshPart& copied) = default ;
            MeshPart(MeshPart&& moved) = default ;
            MeshPart& operator=(const MeshPart& copied) = default ;
            MeshPart& operator=(MeshPart&& moved) = default ;
    } ;
}

#endif
