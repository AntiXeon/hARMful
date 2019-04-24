#ifndef __HOPE__GL_MESH_GEOMETRY__
#define __HOPE__GL_MESH_GEOMETRY__

#include <vector>
#include <scene/ogl/GLDefines.hpp>
#include <scene/ogl/mesh/MeshPart.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * A MeshGeometry contains the geometry data of a 3D object.
     */
    class MeshGeometry final {
        friend class MeshTreeComponent ;

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
             * Mesh parts composing the whole mesh.
             */
            std::vector<MeshPart> m_parts ;

        public:
            /**
             * Create a new MeshGeometry.
             */
            MeshGeometry(const std::vector<float>& vertices) ;

            /**
             * Add a mesh part.
             */
            void addPart(
                const uint32_t materialID,
                const std::vector<uint32_t>& indices
            ) ;

            /**
             * Destruction of the MeshGeometry by deleting the buffers.
             */
            void clearBuffers() ;

            /**
             * Bind the mesh geometry for data management, rendering, etc.
             */
            void bind() const {
                glBindVertexArray(m_vertexArray) ;
            }

            /**
             * Unbind the mesh geometry after data management, rendering, etc.
             */
            void unbind() const {
                glBindVertexArray(0) ;
            }

            /**
             * Get a part.
             */
            const MeshPart& part(const uint32_t index) const {
                return m_parts[index] ;
            }

            /**
             * Get the amount of parts composing the current mesh.
             */
            size_t amountParts() const {
                return m_parts.size() ;
            }

            // Copy/move operations.
            MeshGeometry(const MeshGeometry& copied) = default ;
            MeshGeometry(MeshGeometry&& moved) = default ;
            MeshGeometry& operator=(const MeshGeometry& copied) = default ;
            MeshGeometry& operator=(MeshGeometry&& moved) = default ;
    } ;
}

#endif
