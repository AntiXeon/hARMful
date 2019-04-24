#include <scene/ogl/mesh/loader/MeshTreeLoader.hpp>
#include <scene/ogl/mesh/Vertex.hpp>
#include <scene/ogl/mesh/MeshGeometry.hpp>
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
        aiProcessPreset_TargetRealtime_Fast
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
        setupTransform(node -> mTransformation, meshEntity) ;
        loadNodeData(scene, node, meshEntity) ;
    }

    // Load the meshes of the children.
    for (unsigned int index = 0 ; index < node -> mNumChildren ; ++index) {
        Hope::Entity* childEntity = new Hope::Entity(entity) ;
        aiNode* child = node -> mChildren[index] ;
        generateNode(scene, child, childEntity) ;
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
    std::vector<MeshPartData> partData ;
    partData.reserve(node -> mNumMeshes) ;

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
            aiVector3D texCoord = Zero ;

            std::vector<float> vertexCoordinates = std::move(Vertex(
                Mind::Vector3f(pos.x, pos.y, pos.z),
                Mind::Vector2f(texCoord.x, texCoord.y),
                Mind::Vector3f(normal.x, normal.y, normal.z)
            ).data()) ;

            vertices.insert(vertices.end(), vertexCoordinates.begin(), vertexCoordinates.end()) ;
        }

        // Get the indices that compose the faces.
        const unsigned char AmountVerticesByFace = 3 ;
        uint32_t amountFaces = meshToLoad -> mNumFaces ;
        partData[index].indices.reserve(amountFaces * AmountVerticesByFace) ;

        for (uint32_t faceIndex = 0 ; faceIndex < amountFaces ; ++faceIndex) {
            const aiFace& face = meshToLoad -> mFaces[faceIndex] ;

            partData[index].indices.push_back(face.mIndices[0]) ;
            partData[index].indices.push_back(face.mIndices[1]) ;
            partData[index].indices.push_back(face.mIndices[2]) ;
        }

        partData[index].material = materialProcessing(scene, meshToLoad, entity) ;
    }

    // Put data into the geometry.
    MeshGeometry* geometry = new MeshGeometry(vertices) ;
    for (MeshPartData& part : partData) {
        geometry -> addPart(part.material, part.indices) ;
    }

    // Add the components to the entity.
    MeshGeometryComponent* geometryComponent = new MeshGeometryComponent(geometry) ;
    entity -> addComponent(geometryComponent) ;
}

uint32_t MeshTreeLoader::materialProcessing(
    const aiScene* scene,
    const aiMesh* mesh,
    Hope::Entity* entity
) {
    int aiMaterialIndex = mesh -> mMaterialIndex ;
    int partMaterialIndex = 0 ;

    if (m_materialRelations.count(aiMaterialIndex) > 0) {
        PhongMaterialComponent* materialComponent = static_cast<PhongMaterialComponent*>(m_materialRelations[aiMaterialIndex]) ;
        partMaterialIndex = entity -> addComponent(materialComponent) ;
    }
    else {
        PhongMaterialComponent* materialComponent = new PhongMaterialComponent() ;
        m_materialRelations[aiMaterialIndex] = materialComponent ;
        partMaterialIndex = entity -> addComponent(materialComponent) ;

        // Default is Phong material for now (temporary code).
        aiMaterial* material = scene -> mMaterials[aiMaterialIndex] ;
        aiColor4D specularColor ;
        aiColor4D diffuseColor ;
        aiColor4D ambientColor ;
        float shininess ;

        aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor) ;
        aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor) ;
        aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor) ;
        aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess) ;

        materialComponent -> setAmbient(Color(ambientColor.r, ambientColor.g, ambientColor.b)) ;
        materialComponent -> setDiffuse(Color(diffuseColor.r, diffuseColor.g, diffuseColor.b)) ;
        materialComponent -> setSpecular(Color(specularColor.r, specularColor.g, specularColor.b)) ;
        materialComponent -> setShininess(shininess) ;
    }

    return partMaterialIndex ;
}

void MeshTreeLoader::setupTransform(
    const aiMatrix4x4& nodeMatrix,
    Hope::Entity* entity
) {
    Mind::Matrix4x4f transformMatrix ;
    const size_t MatrixSize = transformMatrix.size() ;

    for (size_t col = 0 ; col < MatrixSize ; ++col) {
        Mind::Point4Df transformColumn(
            nodeMatrix[col][0],
            nodeMatrix[col][1],
            nodeMatrix[col][2],
            nodeMatrix[col][3]
        ) ;

        transformMatrix.setColumnValues(col, transformColumn) ;
    }

    (entity -> transform()).setMatrix(transformMatrix) ;
}
