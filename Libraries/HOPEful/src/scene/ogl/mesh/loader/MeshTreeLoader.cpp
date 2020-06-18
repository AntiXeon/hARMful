#include <scene/ogl/mesh/loader/MeshTreeLoader.hpp>
#include <scene/ogl/mesh/loader/MaterialLoader.hpp>
#include <scene/ogl/mesh/Vertex.hpp>
#include <scene/ogl/mesh/MeshGeometry.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/Entity.hpp>
#include <utils/LogSystem.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <filesystem>

using namespace Hope::GL ;
namespace fs = std::filesystem ;

void MeshTreeLoader::load(
    const std::string& source,
    Hope::Transform* meshRoot
) {
    m_source = source ;
    Assimp::Importer importer ;

    const aiScene* scene = importer.ReadFile(
        m_source.c_str(),
        aiProcess_Triangulate
		| aiProcess_CalcTangentSpace
		| aiProcess_RemoveRedundantMaterials
		| aiProcess_JoinIdenticalVertices
		| aiProcess_GenSmoothNormals
    ) ;

    if (scene) {
        m_meshRoot = std::make_unique<Hope::Transform>(meshRoot) ;
        generateNode(scene, scene -> mRootNode, m_meshRoot.get()) ;
    }
    else {
        std::string errorLog = importer.GetErrorString() ;

        Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
        Doom::LogSystem::WriteLine(level, errorLog) ;
    }
}

void MeshTreeLoader::generateNode(
    const aiScene* scene,
    const aiNode* node,
    Hope::Transform* transform
) {
    setupTransform(node -> mTransformation, transform) ;

    if (node -> mNumMeshes > 0) {
        loadNodeData(scene, node, transform -> entity()) ;

        std::string nodeName((node -> mName).C_Str()) ;
        if (!nodeName.empty() && m_meshTransforms.count(nodeName) == 0) {
            m_meshTransforms[nodeName] = transform ;
        }
    }

    // Load the meshes of the children.
    for (unsigned int index = 0 ; index < node -> mNumChildren ; ++index) {
        Hope::Transform* childTransform = new Hope::Transform(transform) ;
        aiNode* child = node -> mChildren[index] ;
        generateNode(scene, child, childTransform) ;
    }
}

size_t MeshTreeLoader::countMeshVertices(
    const aiScene* scene,
    const aiNode* node
) {
    // Get the total amount of vertices for the current node.
    size_t totalAmountVertices = 0 ;

    for (unsigned int index = 0 ; index < node -> mNumMeshes ; ++index) {
        unsigned int meshIndex = node -> mMeshes[index] ;
        aiMesh* meshToLoad = scene -> mMeshes[meshIndex] ;

        totalAmountVertices += meshToLoad -> mNumVertices ;
    }

    return totalAmountVertices ;
}

void MeshTreeLoader::loadNodeData(
    const aiScene* scene,
    const aiNode* node,
    Hope::Entity* entity
) {
    const aiVector3D Zero(0.f, 0.f, 0.f) ;

    // Store all the vertices of the node.
    std::vector<float> vertices ;
    vertices.reserve(countMeshVertices(scene, node)) ;

    // Store the index of the vertices for each mesh.
    std::vector<GeometryPartData> partData ;
    partData.resize(node -> mNumMeshes) ;

    uint32_t indexOffset = 0 ;

    // Process the different meshes of the node.
    for (unsigned int index = 0 ; index < node -> mNumMeshes ; ++index) {
        unsigned int meshIndex = node -> mMeshes[index] ;
        aiMesh* meshToLoad = scene -> mMeshes[meshIndex] ;

        // Geometry processing.
        uint32_t amountVertices = meshToLoad -> mNumVertices ;

        // Get the vertex coordinates.
        for (uint32_t vertexIndex = 0 ; vertexIndex < amountVertices ; ++vertexIndex) {
            aiVector3D pos = meshToLoad -> mVertices[vertexIndex] ;
            aiVector3D normal = meshToLoad -> mNormals[vertexIndex] ;

            aiVector3D tangent = Zero ;
            aiVector3D bitangent = Zero ;
            if (meshToLoad -> HasTangentsAndBitangents()) {
                tangent = meshToLoad -> mTangents[vertexIndex] ;
                bitangent = meshToLoad -> mBitangents[vertexIndex] ;
            }

            aiVector3D texCoord = Zero ;
            const int TextureCoordSetIndex = 0 ;
            if (meshToLoad -> HasTextureCoords(TextureCoordSetIndex)) {
                texCoord = meshToLoad -> mTextureCoords[TextureCoordSetIndex][vertexIndex] ;
            }

            std::vector<float> vertexCoordinates = std::move(Vertex(
                Mind::Vector3f(pos.x, pos.y, pos.z),
                Mind::Vector2f(texCoord.x, texCoord.y),
                Mind::Vector3f(normal.x, normal.y, normal.z),
                Mind::Vector3f(tangent.x, tangent.y, tangent.z),
                Mind::Vector3f(bitangent.x, bitangent.y, bitangent.z)
            ).data()) ;

            vertices.insert(vertices.end(), vertexCoordinates.begin(), vertexCoordinates.end()) ;
        }

        // Get the indices that compose the faces.
        const unsigned char AmountVerticesByFace = 3 ;
        uint32_t amountFaces = meshToLoad -> mNumFaces ;
        partData[index].indices.reserve(amountFaces * AmountVerticesByFace) ;

        for (uint32_t faceIndex = 0 ; faceIndex < amountFaces ; ++faceIndex) {
            const aiFace& face = meshToLoad -> mFaces[faceIndex] ;

            partData[index].indices.push_back(face.mIndices[0] + indexOffset) ;
            partData[index].indices.push_back(face.mIndices[1] + indexOffset) ;
            partData[index].indices.push_back(face.mIndices[2] + indexOffset) ;
        }

        partData[index].material = materialProcessing(
			scene,
			meshToLoad,
			entity
		) ;

        indexOffset += amountVertices ;
    }

    // Put data into the geometry.
    MeshGeometry* geometry = new MeshGeometry(vertices) ;
    for (GeometryPartData& part : partData) {
        geometry -> addPart(part.material, part.indices) ;
    }
    geometry -> completed() ;

    // Add the components to the entity.
    auto geometryComponent = std::make_shared<MeshGeometryComponent>(geometry) ;
    entity -> addComponent(geometryComponent) ;
}

uint32_t MeshTreeLoader::materialProcessing(
    const aiScene* scene,
    const aiMesh* mesh,
    Hope::Entity* entity
) {
    int aiMaterialIndex = mesh -> mMaterialIndex ;
    int partMaterialIndex = 0 ;

    if (m_materialRelations.count(aiMaterialIndex) == 0) {
        aiMaterial* material = scene -> mMaterials[aiMaterialIndex] ;
        m_materialRelations[aiMaterialIndex] = MaterialLoader::ConvertMaterial(
            fs::path(m_source),
            material
        ) ;
    }

    auto materialComponent = m_materialRelations[aiMaterialIndex] ;
    partMaterialIndex = entity -> addComponent(materialComponent) ;

    return partMaterialIndex ;
}

void MeshTreeLoader::setupTransform(
    const aiMatrix4x4& nodeMatrix,
    Hope::Transform* transform
) {
    Mind::Matrix4x4f transformMatrix ;

    const uint32_t MatrixSize = static_cast<uint32_t>(transformMatrix.size()) ;

    for (uint32_t row = 0 ; row < MatrixSize ; ++row) {
        Mind::Point4Df transformRow(
            nodeMatrix[row][0],
            nodeMatrix[row][1],
            nodeMatrix[row][2],
            nodeMatrix[row][3]
        ) ;

        transformMatrix.setRowValues(row, transformRow) ;
    }
    transform -> setLocal(transformMatrix) ;
}
