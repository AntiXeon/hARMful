#ifndef __HOPE__GL_MESH_GEOMETRY__
#define __HOPE__GL_MESH_GEOMETRY__

#include <utils/Platform.hpp>

#include <vector>
#include <scene/ogl/GLDefines.hpp>
#include <scene/ogl/mesh/Geometry.hpp>
#include <scene/ogl/mesh/GeometryPart.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * A MeshGeometry contains the geometry data of a 3D object.
     */
    class MeshGeometry final : public Geometry {
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
             * ID of the index buffer of this part.
             */
            GLuint m_indexBuffer = INVALID_VALUE ;

            /**
             * Indices of the vertices that compose the mesh and mesh parts.
             */
            std::vector<uint32_t> m_indices ;

            /**
             * Mesh parts composing the whole mesh.
             */
            std::vector<GeometryPart> m_parts ;

        public:
            /**
             * Create a new MeshGeometry.
             */
            exported MeshGeometry(const std::vector<float>& vertices) ;

            /**
             * Add a mesh part.
             */
            exported void addPart(
                const uint32_t materialID,
                const std::vector<uint32_t>& indices
            ) ;

            /**
             * Generate all the buffers when the
             */
            exported void completed() ;

            /**
             * Destruction of the MeshGeometry by deleting the buffers.
             */
            exported void clearBuffers() ;

            /**
             * Bind the mesh geometry for data management, rendering, etc.
             */
            exported void bind() const override {
                glBindVertexArray(m_vertexArray) ;
            }

            /**
             * Unbind the mesh geometry after data management, rendering, etc.
             */
            exported void unbind() const override {
                glBindVertexArray(0) ;
            }

            /**
             * Get a part.
             */
            exported const GeometryPart& part(const uint32_t index) const override {
                return m_parts[index] ;
            }

            /**
             * Amount of indices in the total mesh.
             */
            exported size_t amountIndices() const override {
                return m_indices.size() ;
            }

            /**
             * Get the amount of parts composing the current mesh.
             */
            exported size_t amountParts() const override {
                return m_parts.size() ;
            }

            /**
             * Type of the indice values.
             */
            exported GLenum indiceType() const override {
                return GL_UNSIGNED_INT ;
            }

            // Copy/move operations.
            MeshGeometry(const MeshGeometry& copied) = default ;
            MeshGeometry(MeshGeometry&& moved) = default ;
            MeshGeometry& operator=(const MeshGeometry& copied) = default ;
            MeshGeometry& operator=(MeshGeometry&& moved) = default ;
    } ;
}

#endif
