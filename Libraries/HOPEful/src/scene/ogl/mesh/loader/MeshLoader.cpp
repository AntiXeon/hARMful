#include <scene/ogl/mesh/loader/MeshLoader.hpp>
#include <scene/ogl/mesh/Vertex.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace Hope::GL ;

MeshLoader::MeshLoader(const std::string& source) {
    m_source = source ;
}

std::shared_ptr<Mesh>& MeshLoader::mesh() {
    return m_mesh ;
}

bool MeshLoader::load() {
    bool success = false ;
    Assimp::Importer importer ;

    const aiScene* scene = importer.ReadFile(
        m_source.c_str(),
        aiProcess_Triangulate | aiProcess_GenSmoothNormals
    ) ;

    if (scene) {
        success = initializeFromScene(scene) ;
    }
    else {
        // Log errors...
    }

    return success ;
}

bool MeshLoader::initializeFromScene(const aiScene* scene) {
    uint32_t amountParts = scene -> mNumMeshes ;
    // Resize to be able to store all the mesh parts.
    m_parts.resize(amountParts) ;

    // Initialize each mesh part.
    for (uint32_t partIndex = 0 ; partIndex < amountParts ; ++partIndex) {
        const aiMesh* part = scene -> mMeshes[partIndex] ;
        initializeMeshPart(partIndex, part) ;
    }

    m_mesh = std::make_shared<Mesh>(m_parts) ;

    return true ;
}

void MeshLoader::initializeMeshPart(
    const uint32_t partIndex,
    const aiMesh* part
)
{
    const aiVector3D Zero(0.f, 0.f, 0.f) ;

    std::vector<Vertex> vertices ;
    std::vector<uint32_t> indices ;

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

        Vertex newVertex(
            Mind::Vector3f(pos.x, pos.y, pos.z),
            Mind::Vector2f(texCoord.x, texCoord.y),
            Mind::Vector3f(normal.x, normal.y, normal.z)
        );

        vertices.push_back(newVertex) ;
    }

    // Fill the index buffer.
    uint32_t amountFaces = part -> mNumFaces ;

    for (uint32_t faceIndex = 0 ; faceIndex < amountFaces ; ++faceIndex) {
        const aiFace& face = part -> mFaces[faceIndex] ;
        //assert(face.mNumIndices == 3) ;

        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    m_parts[partIndex].initialize(vertices, indices) ;
}
