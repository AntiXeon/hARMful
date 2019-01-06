#ifndef __HOPE__GL_MESHLOADER__
#define __HOPE__GL_MESHLOADER__

#include <cstdint>
#include <string>
#include <memory>
#include <ogl/mesh/Mesh.hpp>

class Importer ;
struct aiScene ;
struct aiMesh ;

namespace Hope { namespace GL {
    /**
     * Loader of a 3D mesh model and expose the generated Mesh used by the
     * engine later.
     */
    class MeshLoader final {
        private:
            /**
             * File path of the mesh to be loaded.
             */
            std::string m_source ;

            /**
             * Loaded mesh parts that will be aggregated into the final Mesh.
             */
            std::vector<MeshPart> m_parts ;

            /**
             * Mesh that is loaded as a usable structure within HOPEful.
             */
            std::shared_ptr<Mesh> m_mesh ;

        public:
            /**
             * Create a new MeshLoader.
             * @param   source  File to be loaded.
             */
            MeshLoader(const std::string& source) ;

            /**
             * Get the loaded Mesh.
             */
            std::shared_ptr<Mesh>& mesh() ;

        private:
            /**
             * Load data into a Mesh.
             * @return  TRUE on success; FALSE otherwise.
             */
            bool load() ;

            /**
             * Initialize the mesh from the content of the Assimp scene
             * (= mesh with mesh part(s)).
             */
            bool initializeFromScene(const aiScene* scene) ;

            /**
             * Initialize a mesh part.
             * @param   partIndex   Index of the part in the whole mesh.
             * @param   part        Data of the mesh part.
             */
            void initializeMeshPart(
                const uint32_t partIndex,
                const aiMesh* part
            ) ;
    } ;
}}

#endif
