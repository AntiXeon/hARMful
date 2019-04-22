#ifndef __HOPE__GL_MESH_GEOMETRY__
#define __HOPE__GL_MESH_GEOMETRY__

#include <vector>
#include <scene/ogl/GLDefines.hpp>
#include <scene/ogl/mesh/MeshPart.hpp>
#include <interfaces/IRenderable.hpp>
#include <GL/glew.h>

namespace Hope::GL {
    /**
     * A MeshGeometry contains the geometry data of a 3D object.
     */
    class MeshGeometry final : public Hope::IRenderable {
        friend class MeshTreeComponent ;

        private:
            /**
             * ID of the VAO.
             */
            GLuint m_vertexArray = INVALID_VALUE ;

            /**
             * Mesh parts composing the whole mesh.
             */
            std::vector<MeshPart> m_parts ;

        public:
            /**
             * Create a new MeshGeometry.
             */
            MeshGeometry() ;

            /**
             * Add a mesh part.
             */
            void addPart(
                const std::vector<float>& vertices,
                const std::vector<uint32_t>& indices
            ) {
                glBindVertexArray(m_vertexArray) ;
                m_parts.push_back(MeshPart(vertices, indices)) ;
                glBindVertexArray(0) ;
            }

            /**
             * Destruction of the MeshGeometry by deleting the buffers.
             */
            void clearBuffers() ;

            /**
             * Render the mesh parts on screen.
             */
            void render() const override {
                glBindVertexArray(m_vertexArray) ;

                for (const MeshPart& part : m_parts) {
                    part.render() ;
                }

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
