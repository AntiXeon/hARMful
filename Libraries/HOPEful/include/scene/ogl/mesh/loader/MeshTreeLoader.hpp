#ifndef __HOPE__GL_MESH_TREE_LOADER__
#define __HOPE__GL_MESH_TREE_LOADER__

#include <utils/Platform.hpp>

#include <assimp/matrix4x4.h>
#include <scene/Transform.hpp>
#include <scene/components/materials/MaterialComponent.hpp>
#include <cstdint>
#include <string>
#include <map>
#include <memory>

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
            struct GeometryPartData {
                // Index of the material in the entity bearing the mesh and its
                // mesh parts.
                uint32_t material ;

                // Indices of the vertices that compose the mesh part.
                std::vector<uint32_t> indices ;
            } ;

            /**
             * Store the mesh transforms by their name.
             * Only transforms having a name are stored here.
             */
            std::map<std::string, Hope::Transform*> m_meshTransforms ;

            /**
             * Link the materials from the input file to the material components
             * used by entities and the rendering step.
             */
            std::map<unsigned int, std::shared_ptr<MaterialComponent>> m_materialRelations ;

            /**
             * Path to the source file.
             */
            std::string m_source ;

            /**
             * Root of the mesh that is created by the loader.
             */
            std::unique_ptr<Hope::Transform> m_meshRoot = nullptr ;

        public:
            /**
             * Load a mesh.
             * @param   source      File to be loaded.
             * @param   meshRoot    Root entity of the mesh tree.
             */
            exported void load(
                const std::string& source,
                Hope::Transform* meshRoot
            ) ;

            /**
             * Get the mesh root.
             */
            exported Hope::Transform* meshRoot() const {
                return m_meshRoot.get() ;
            }

            /**
             * Get a transform generated on loading by its name.
             * If the name is not found, nullptr is returned.
             */
            exported Hope::Transform* transform(const std::string& name) {
                if (m_meshTransforms.count(name) > 0) {
                    return m_meshTransforms[name] ;
                }
                return nullptr ;
            }

        private:
            /**
             * Initialize the mesh from the content of the Assimp scene
             * (= mesh with mesh part(s)).
             */
            exported void generateNode(
                const aiScene* scene,
                const aiNode* node,
                Hope::Transform* transform
            ) ;

            /**
             * Count the amount of vertices in all the meshes of the given node.
             */
            exported size_t countMeshVertices(
                const aiScene* scene,
                const aiNode* node
            ) ;

            /**
             * Load node data from the input file into a MeshGeometry.
             * @return  The MeshGeometry filled with all the geometry data.
             */
            exported void loadNodeData(
                const aiScene* scene,
                const aiNode* node,
                Hope::Entity* entity
            ) ;

            /**
             * Parse the material from the importer and convert it to a usable
             * MaterialComponent.
             * @return  Get the index of the material in the entity.
             */
            exported uint32_t materialProcessing(
                const aiScene* scene,
                const aiMesh* mesh,
                Hope::Entity* entity
            ) ;

            /**
             * Set up the transform of a mesh.
             */
            exported void setupTransform(
                const aiMatrix4x4& nodeMatrix,
                Hope::Transform* transform
            ) ;
    } ;
}

#endif
