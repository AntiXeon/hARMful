#include <scene/ogl/mesh/loader/MeshTreeLoader.hpp>
#include <scene/ogl/mesh/MeshGeometry.hpp>
#include <scene/ogl/mesh/Vertex.hpp>
#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <scene/components/materials/PhongMaterialComponent.hpp>
#include <utils/LogSystem.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace Hope::GL ;

MeshTreeLoader::~MeshTreeLoader() {
    delete m_meshRoot ;
}

void MeshTreeLoader::load(
    const std::string& source,
    Hope::Entity* meshRoot
) {
    Assimp::Importer importer ;

    const aiScene* scene = importer.ReadFile(
        source.c_str(),
        // aiProcessPreset_TargetRealtime_Fast
        aiProcess_Triangulate |
            aiProcess_GenSmoothNormals |
            aiProcess_JoinIdenticalVertices |
            aiProcess_CalcTangentSpace
    ) ;

    if (scene) {
        m_meshRoot = new Hope::Entity(meshRoot) ;
        generateNode(scene, scene -> mRootNode, m_meshRoot) ;
    }
    else {
        std::string errorLog = importer.GetErrorString() ;

        // Write the error in the log.
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
            logSharedPtr -> writeLine(level, errorLog) ;
        }
    }
}

void MeshTreeLoader::generateNode(
    const aiScene* scene,
    const aiNode* node,
    Hope::Entity* entity
) {
    if (node -> mNumMeshes > 0) {
        Hope::Entity* meshEntity = new Hope::Entity(entity) ;

        Hope::MeshGeometryComponent* geometryComponent = new Hope::MeshGeometryComponent() ;
        meshEntity -> addComponent(geometryComponent) ;

        Hope::PhongMaterialComponent* tmpMaterial = new Hope::PhongMaterialComponent() ;
        meshEntity -> addComponent(tmpMaterial) ;

        // Load the different parts of the current node.
        for (unsigned int index = 0 ; index < node -> mNumMeshes ; ++index) {
            unsigned int meshIndex = node -> mMeshes[index] ;
            aiMesh* meshToLoad = scene -> mMeshes[meshIndex] ;
            loadMeshPart(geometryComponent, meshToLoad) ;
        }
    }

    // Load the meshes of the children.
    for (unsigned int index = 0 ; index < node -> mNumChildren ; ++index) {
        Hope::Entity* childEntity = new Hope::Entity(entity) ;
        aiNode* child = node -> mChildren[index] ;
        generateNode(scene, child, childEntity) ;
    }
}

void MeshTreeLoader::loadMeshPart(
    Hope::MeshGeometryComponent* geometryComponent,
    const aiMesh* mesh
) {
    const aiVector3D Zero(0.f, 0.f, 0.f) ;

    std::vector<float> vertices ;
    std::vector<uint32_t> indices ;

    // Fill the vertex buffer.
    uint32_t amountVertices = mesh -> mNumVertices ;

    for (uint32_t vertexIndex = 0 ; vertexIndex < amountVertices ; ++vertexIndex) {
        aiVector3D pos = mesh -> mVertices[vertexIndex] ;
        aiVector3D normal = mesh -> mNormals[vertexIndex] ;
        aiVector3D texCoord ;

        if (mesh -> HasTextureCoords(0)) {
            texCoord = mesh -> mTextureCoords[0][vertexIndex] ;
        }
        else {
            texCoord = Zero ;
        }

        std::vector<float> vertexCoordinates = std::move(Vertex(
            Mind::Vector3f(pos.x, pos.y, pos.z),
            Mind::Vector2f(texCoord.x, texCoord.y),
            Mind::Vector3f(normal.x, normal.y, normal.z)
        ).data()) ;

        vertices.insert(vertices.end(), vertexCoordinates.begin(), vertexCoordinates.end()) ;
    }

    // Fill the index buffer.
    uint32_t amountFaces = mesh -> mNumFaces ;

    for (uint32_t faceIndex = 0 ; faceIndex < amountFaces ; ++faceIndex) {
        const aiFace& face = mesh -> mFaces[faceIndex] ;

        indices.push_back(face.mIndices[0]) ;
        indices.push_back(face.mIndices[1]) ;
        indices.push_back(face.mIndices[2]) ;
    }

    geometryComponent -> addMeshPart(vertices, indices) ;
}
