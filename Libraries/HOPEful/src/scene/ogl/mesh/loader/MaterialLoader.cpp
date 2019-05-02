#include <scene/ogl/mesh/loader/MaterialLoader.hpp>
#include <scene/components/materials/PhongMaterialComponent.hpp>
#include <scene/components/materials/DiffuseMaterialComponent.hpp>
#include <assimp/scene.h>

using namespace Hope ;
using namespace Hope::GL ;

MaterialComponent* MaterialLoader::ConvertMaterial(
    const fs::path& meshPath,
    const aiMaterial* material
) {
    if (material -> GetTextureCount(aiTextureType_DIFFUSE) == 0) {
        return BlinnPhongMaterial(material) ;
    }
    else {
        return DiffuseMaterial(meshPath, material) ;
    }
}

MaterialComponent* MaterialLoader::BlinnPhongMaterial(const aiMaterial* material) {
    PhongMaterialComponent* materialComponent = new PhongMaterialComponent() ;
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
    return materialComponent ;
}

MaterialComponent* MaterialLoader::DiffuseMaterial(
    const fs::path& meshPath,
    const aiMaterial* material
) {
    const int DiffuseIndex = 0 ;
    aiString assimpPath ;
    aiTextureMapMode mapMode[3] ;

    material -> GetTexture(
        aiTextureType_DIFFUSE,
        DiffuseIndex,
        &assimpPath,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        mapMode
    ) ;

    // Use an absolute path to the texture.
    fs::path absoluteTexturePath ;
    fs::path texturePath(assimpPath.C_Str()) ;

    if (texturePath.is_absolute()) {
        absoluteTexturePath = texturePath ;
    }
    else {
        absoluteTexturePath = meshPath.parent_path() / texturePath ;
    }

    Texture2D* diffuseMap = new Texture2D(absoluteTexturePath.string()) ;
    DiffuseMaterialComponent* materialComponent = new DiffuseMaterialComponent() ;
    materialComponent -> setDiffuse(diffuseMap) ;

    // Get the other values of the material.
    aiColor4D specularColor ;
    float shininess ;
    aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor) ;
    aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess) ;
    materialComponent -> setSpecular(Color(specularColor.r, specularColor.g, specularColor.b)) ;
    materialComponent -> setShininess(shininess) ;

    return materialComponent ;
}
