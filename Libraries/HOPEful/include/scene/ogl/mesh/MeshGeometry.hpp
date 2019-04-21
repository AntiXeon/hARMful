#ifndef __HOPE__GL_MESH_GEOMETRY__
#define __HOPE__GL_MESH_GEOMETRY__

#include <vector>
#include <scene/ogl/GLDefines.hpp>
#include <interfaces/IRenderable.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * A MeshGeometry contains the geometry data of a 3D object.
     */
    class MeshGeometry final : public Hope::IRenderable {
        private:
            /**
             * ID of the VAO.
             */
            GLuint m_vertexArray = INVALID_VALUE ;

            /**
             * ID of the vertex buffer of this mesh.
             */
            GLuint m_vertexBuffer = INVALID_VALUE ;

            /**
             * ID of the index buffer of this mesh.
             */
            GLuint m_indexBuffer = INVALID_VALUE ;

            /**
             * Amount of vertex indices.
             */
            uint32_t m_amountIndices = 0 ;

        public:
            /**
             * Create a new MeshGeometry.
             */
            MeshGeometry() = default ;

            /**
             * Create a new MeshGeometry.
             */
            MeshGeometry(
                const std::vector<float>& vertices,
                const std::vector<uint32_t>& indices
            ) ;

            /**
             * Destruction of the MeshGeometry.
             */
            virtual ~MeshGeometry() ;

            /**
             * Render the mesh parts on screen.
             */
            void render() const override {
                glBindVertexArray(m_vertexArray) ;
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
                glDrawElements(GL_TRIANGLES, m_amountIndices, GL_UNSIGNED_INT, nullptr) ;
                glBindVertexArray(0) ;
            }

            // Copy/move operations.
            MeshGeometry(const MeshGeometry& copied) = default ;
            MeshGeometry(MeshGeometry&& moved) = default ;
            MeshGeometry& operator=(const MeshGeometry& copied) = default ;
            MeshGeometry& operator=(MeshGeometry&& moved) = default ;
    } ;
}

#endif
