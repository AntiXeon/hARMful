#ifndef __HOPE__GL_MESH_TREE_LOADER__
#define __HOPE__GL_MESH_TREE_LOADER__

#include <cstdint>
#include <string>
#include <scene/Entity.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>

class Importer ;
struct aiScene ;
struct aiNode ;
struct aiMesh ;

namespace Hope::GL {
    /**
     * Loader of a 3D mesh model and expose the generated mesh root entity used
     * by the engine later.
     */
    class MeshTreeLoader final {
        private:
            /**
             * Root of the mesh that is created by the loader.
             */
            Hope::Entity* m_meshRoot = nullptr ;

        public:
            /**
             * Destruction of the MeshTreeLoader.
             */
            ~MeshTreeLoader() ;

            /**
             * Load a mesh.
             * @param   source      File to be loaded.
             * @param   meshRoot    Root entity of the mesh tree.
             */
            void load(
                const std::string& source,
                Hope::Entity* meshRoot
            ) ;

            /**
             * Get the mesh root.
             */
            Hope::Entity* meshRoot() const {
                return m_meshRoot ;
            }

        private:
            /**
             * Initialize the mesh from the content of the Assimp scene
             * (= mesh with mesh part(s)).
             */
            void generateNode(
                const aiScene* scene,
                const aiNode* node,
                Hope::Entity* entity
            ) ;

            /**
             * Load a mesh part.
             */
            void loadMeshPart(
            Hope::MeshGeometryComponent* geometryComponent,
            const aiMesh* mesh
            ) ;
    } ;
}

#endif
