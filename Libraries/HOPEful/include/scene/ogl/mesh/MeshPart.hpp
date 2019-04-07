#ifndef __HOPE__GL_MESHPART__
#define __HOPE__GL_MESHPART__

#include <vector>
#include <scene/ogl/GLDefines.hpp>
#include <interfaces/IRenderable.hpp>
#include <GL/glew.h>
#include <cstdint>

namespace Hope::GL {

    class Vertex ;

    /**
     * A MeshPart is a subpart of a Mesh. A complex Mesh can have several parts.
     */
    class MeshPart final : public Hope::IRenderable {
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
                 const std::vector<uint16_t>& indices
             ) ;

            /**
             * Destruction of the MeshPart.
             */
            virtual ~MeshPart() ;

            /**
             * Render the mesh part on screen.
             */
            void render() override {
                glDrawElements(
                    GL_TRIANGLE_STRIP,
                    m_amountIndices,
                    GL_UNSIGNED_INT,
                    nullptr
                ) ;
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

            // Copy/move operations.
            MeshPart() = default ;
            MeshPart(const MeshPart& copied) = default ;
            MeshPart(MeshPart&& moved) = default ;
            MeshPart& operator=(const MeshPart& copied) = default ;
            MeshPart& operator=(MeshPart&& moved) = default ;
    } ;
}

#endif
