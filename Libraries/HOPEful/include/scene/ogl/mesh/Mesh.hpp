#ifndef __HOPE__GL_MESH__
#define __HOPE__GL_MESH__

#include <vector>
#include <scene/ogl/mesh/MeshPart.hpp>

namespace Hope::GL {

    class MeshPart ;

    /**
     * A Mesh that contains all data to be displayed in an OpenGL scene.
     */
    class Mesh final {
        private:
            /**
             * List of mesh parts that compose the current Mesh.
             */
            std::vector<MeshPart> m_parts ;

        public:
            /**
             * Create a new Mesh.
             */
            Mesh(const std::vector<MeshPart>& parts) {
                m_parts = parts ;
            }

            /**
             * Get the mesh parts that compose the current Mesh.
             */
            const std::vector<MeshPart>& parts() const {
                return m_parts ;
            }
    } ;
}

#endif
