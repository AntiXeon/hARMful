#ifndef __HOPE__GL_MESH__
#define __HOPE__GL_MESH__

#include <vector>
#include <scene/ogl/mesh/MeshPart.hpp>
#include <interfaces/IRenderable.hpp>

namespace Hope::GL {

    class MeshLoader ;
    class MeshPart ;

    /**
     * A Mesh that contains all data to be displayed in an OpenGL scene.
     */
    class Mesh final : public Hope::IRenderable {
        friend class MeshLoader ;

        private:
            /**
             * ID of the VAO.
             */
            GLuint m_vertexArray = INVALID_VALUE ;

            /**
             * List of mesh parts that compose the current Mesh.
             */
            std::vector<MeshPart> m_parts ;

        public:
            /**
             * Create a new Mesh.
             */
            Mesh() {
                glGenVertexArrays(1, &m_vertexArray) ;
                std::cout << "VAO: " << m_vertexArray << std::endl ;
            }

            /**
             * Destruction of the Mesh.
             */
            virtual ~Mesh() {
                for (auto& part : m_parts) {
                    part.deleteBuffers() ;
                }

                glDeleteVertexArrays(1, &m_vertexArray) ;
            }

            /**
             * Get the mesh parts that compose the current Mesh.
             */
            const std::vector<MeshPart>& parts() const {
                return m_parts ;
            }

            /**
             * Bind the mesh VAO to draw it.
             */
            void bind() {
                glBindVertexArray(m_vertexArray) ;
            }

            /**
             * Unbing the mesh VAO from the OpenGL state machine.
             */
            void unbind() {
                glBindVertexArray(0) ;
            }

            /**
             * Render the mesh parts on screen.
             */
            void render() override {
                for (auto& part : m_parts) {
                    part.render() ;
                }
            }

            // Copy/move operations.
            Mesh(const Mesh& copied) = default ;
            Mesh(Mesh&& moved) = default ;
            Mesh& operator=(const Mesh& copied) = default ;
            Mesh& operator=(Mesh&& moved) = default ;

        private:
            /**
             * Add a mesh part.
             */
            void addPart(const MeshPart& part) {
                m_parts.push_back(part) ;
            }
    } ;
}

#endif
