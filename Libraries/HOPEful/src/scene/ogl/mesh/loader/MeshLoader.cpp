#include <scene/ogl/mesh/loader/MeshLoader.hpp>
#include <scene/ogl/mesh/Vertex.hpp>
#include <utils/LogSystem.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <iostream>

using namespace Hope::GL ;

MeshLoader::MeshLoader(const std::string& source) {
    m_source = source ;
    m_mesh = std::make_shared<Mesh>() ;

    load() ;
}

std::shared_ptr<Mesh>& MeshLoader::mesh() {
    return m_mesh ;
}

bool MeshLoader::load() {
    bool success = false ;
    Assimp::Importer importer ;

    const aiScene* scene = importer.ReadFile(
        m_source.c_str(),
        aiProcess_Triangulate |
            aiProcess_GenSmoothNormals |
            aiProcess_JoinIdenticalVertices |
            aiProcess_CalcTangentSpace
    ) ;

    if (scene) {
        success = initializeFromScene(scene) ;
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

    return success ;
}

bool MeshLoader::initializeFromScene(const aiScene* scene) {
    uint32_t amountParts = scene -> mNumMeshes ;

    m_mesh -> bind() ;

    // Initialize each mesh part.
    for (uint32_t partIndex = 0 ; partIndex < amountParts ; ++partIndex) {
        const aiMesh* part = scene -> mMeshes[partIndex] ;
        initializeMeshPart(part) ;
    }

    m_mesh -> unbind() ;

    return true ;
}

void MeshLoader::initializeMeshPart(const aiMesh* part)
{
    const aiVector3D Zero(0.f, 0.f, 0.f) ;

    std::vector<float> vertices ;
    std::vector<uint16_t> indices ;

    // Fill the vertex buffer.
    uint32_t amountVertices = part -> mNumVertices ;

    for (uint32_t vertexIndex = 0 ; vertexIndex < amountVertices ; ++vertexIndex) {
        aiVector3D pos = part -> mVertices[vertexIndex] ;
        aiVector3D normal = part -> mNormals[vertexIndex] ;
        aiVector3D texCoord ;

        if (part -> HasTextureCoords(0)) {
            texCoord = part -> mTextureCoords[0][vertexIndex] ;
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
    uint32_t amountFaces = part -> mNumFaces ;

    for (uint32_t faceIndex = 0 ; faceIndex < amountFaces ; ++faceIndex) {
        const aiFace& face = part -> mFaces[faceIndex] ;

        indices.push_back(face.mIndices[0]) ;
        indices.push_back(face.mIndices[1]) ;
        indices.push_back(face.mIndices[2]) ;
    }

    MeshPart meshPart(vertices, indices) ;
    m_mesh -> addPart(meshPart) ;
}
