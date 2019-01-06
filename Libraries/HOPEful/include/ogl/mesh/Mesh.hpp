#ifndef __HOPE__GL_MESH__
#define __HOPE__GL_MESH__

#include <vector>
#include <GL/glew.h>
#include <interfaces/IRenderable.hpp>
#include <ogl/mesh/MeshPart.hpp>

namespace Hope { namespace GL {

    class MeshPart ;

    /**
     * A Mesh that contains all data to be displayed in an OpenGL scene.
     */
    class Mesh final : public IRenderable {
        private:
            /**
             * List of mesh parts that compose the current Mesh.
             */
            std::vector<MeshPart> m_parts ;

        public:
            /**
             * Create a new Mesh.
             */
            Mesh(const std::vector<MeshPart>& parts) ;

            /**
             * Destruction of the Mesh.
             */
            ~Mesh() ;

            /**
             * Render the mesh in the 3D scene.
             */
            void render() override ;


            // Copy/move operations.
            Mesh(const Mesh& copied) = default ;
            Mesh(Mesh&& moved) = default ;
            Mesh& operator=(const Mesh& copied) = default ;
            Mesh& operator=(Mesh&& moved) = default ;
    } ;
}}

#endif
