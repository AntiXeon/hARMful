#ifndef __HOPE__GL_MESHPART__
#define __HOPE__GL_MESHPART__

#include <vector>
#include <scene/ogl/GLDefines.hpp>
#include <interfaces/IRenderable.hpp>
#include <GL/glew.h>
#include <cstdint>

#include <iostream>

namespace Hope::GL {

    class MeshGeometry ;
    class Vertex ;

    /**
     * A MeshPart is a subpart of a Mesh. A complex Mesh can have several parts.
     */
    class MeshPart final : public Hope::IRenderable {
        friend class MeshGeometry ;

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
             * Index of the material to draw this part.
             */
            uint32_t m_materialIndex = INVALID_MATERIAL ;

            /**
             * Amount of vertex indices.
             */
            uint32_t m_amountIndices = 0 ;

        public:
            /**
             * Create a new MeshPart.
             */
             MeshPart(
                 const std::vector<float>& vertices,
                 const std::vector<uint32_t>& indices
             ) ;

            /**
             * Render the mesh part on screen.
             */
            void render() const override {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
                glDrawElements(GL_TRIANGLES, m_amountIndices, GL_UNSIGNED_INT, nullptr) ;
            }

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
                return m_amountIndices ;
            }

        private:
            /**
             * Delete the mesh part buffers.
             */
            void deleteBuffers() ;
    } ;
}

#endif
