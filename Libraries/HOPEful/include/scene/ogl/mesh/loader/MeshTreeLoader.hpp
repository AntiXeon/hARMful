#ifndef __HOPE__GL_MESH_TREE_LOADER__
#define __HOPE__GL_MESH_TREE_LOADER__

#include <cstdint>
#include <string>
#include <map>
#include <assimp/matrix4x4.h>
#include <scene/Entity.hpp>

namespace Hope {
    class MaterialComponent ;
}

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
             * Data used to build the mesh parts.
             */
            struct MeshPartData {
                // Index of the material in the entity bearing the mesh and its
                // mesh parts.
                uint32_t material ;

                // Indices of the vertices that compose the mesh part.
                std::vector<uint32_t> indices ;
            } ;

            /**
             * Link the materials from the input file to the material components
             * used by entities and the rendering step.
             */
            std::map<unsigned int, MaterialComponent*> m_materialRelations ;

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
             * Count the amount of vertices in all the meshes of the given node.
             */
            size_t countMeshVertices(
                const aiScene* scene,
                const aiNode* node
            ) ;

            /**
             * Load node data from the input file into a MeshGeometry.
             * @return  The MeshGeometry filled with all the geometry data.
             */
            void loadNodeData(
                const aiScene* scene,
                const aiNode* node,
                Hope::Entity* entity
            ) ;

            /**
             * Parse the material from the importer and convert it to a usable
             * MaterialComponent.
             * @return  Get the index of the material in the entity.
             */
            uint32_t materialProcessing(
                const aiScene* scene,
                const aiMesh* mesh,
                Hope::Entity* entity
            ) ;

            /**
             * Set up the transform of a mesh.
             */
            void setupTransform(
                const aiMatrix4x4& nodeMatrix,
                Hope::Entity* entity
            ) ;
    } ;
}

#endif
