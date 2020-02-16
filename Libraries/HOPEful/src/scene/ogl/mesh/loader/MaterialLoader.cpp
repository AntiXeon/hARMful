#include <scene/ogl/mesh/loader/MaterialLoader.hpp>
#include <scene/components/materials/BlinnPhongMaterialComponent.hpp>
#include <scene/components/materials/DiffuseMaterialComponent.hpp>
#include <scene/components/materials/DiffuseNormalMaterialComponent.hpp>
#include <scene/components/materials/DiffuseNormalSpecularMaterialComponent.hpp>

using namespace Hope ;
using namespace Hope::GL ;

MaterialComponent* MaterialLoader::ConvertMaterial(
    const fs::path& meshPath,
    const aiMaterial* material
) {
    if (material -> GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        if (material -> GetTextureCount(aiTextureType_NORMALS) > 0) {
            if (material -> GetTextureCount(aiTextureType_SPECULAR) > 0) {
                return DiffuseNormalSpecularMaterial(meshPath, material) ;
            }
            else {
                return DiffuseNormalMaterial(meshPath, material) ;
            }
        }
        else {
            return DiffuseMaterial(meshPath, material) ;
        }
    }
    else {
        // Override the default material from Assimp.
        static const aiString DefaultMaterialName(AI_DEFAULT_MATERIAL_NAME) ;
        aiString currentName ;
        material -> Get(AI_MATKEY_NAME, currentName) ;

        if (currentName == DefaultMaterialName) {
            return new BlinnPhongMaterialComponent() ;
        }
        else {
            return BlinnPhongMaterial(material) ;
        }
    }
}

MaterialComponent* MaterialLoader::BlinnPhongMaterial(const aiMaterial* material) {
    BlinnPhongMaterialComponent* materialComponent = new BlinnPhongMaterialComponent() ;
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
    SetAlphaBlendingMaterial(materialComponent) ;

    return materialComponent ;
}

MaterialComponent* MaterialLoader::DiffuseMaterial(
    const fs::path& meshPath,
    const aiMaterial* material
) {
    DiffuseMaterialComponent* materialComponent = new DiffuseMaterialComponent() ;
    materialComponent -> setDiffuseMap(GetTexture(aiTextureType_DIFFUSE, meshPath, material)) ;

    // Get the other values of the material.
    aiColor4D specularColor ;
    float shininess ;
    aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor) ;
    aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess) ;
    materialComponent -> setSpecular(Color(specularColor.r, specularColor.g, specularColor.b)) ;
    materialComponent -> setShininess(shininess) ;
    SetAlphaBlendingMaterial(materialComponent) ;

    return materialComponent ;
}

MaterialComponent* MaterialLoader::DiffuseNormalMaterial(
    const fs::path& meshPath,
    const aiMaterial* material
) {
    DiffuseNormalMaterialComponent* materialComponent = new DiffuseNormalMaterialComponent() ;
    materialComponent -> setDiffuseMap(GetTexture(aiTextureType_DIFFUSE, meshPath, material)) ;
    materialComponent -> setNormalMap(GetTexture(aiTextureType_NORMALS, meshPath, material)) ;

    // Get the other values of the material.
    aiColor4D specularColor ;
    float shininess ;
    aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor) ;
    aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess) ;
    materialComponent -> setSpecular(Color(specularColor.r, specularColor.g, specularColor.b)) ;
    materialComponent -> setShininess(shininess) ;
    SetAlphaBlendingMaterial(materialComponent) ;

    return materialComponent ;
}

MaterialComponent* MaterialLoader::DiffuseNormalSpecularMaterial(
    const fs::path& meshPath,
    const aiMaterial* material
) {
    DiffuseNormalSpecularMaterialComponent* materialComponent = new DiffuseNormalSpecularMaterialComponent() ;
    materialComponent -> setDiffuseMap(GetTexture(aiTextureType_DIFFUSE, meshPath, material)) ;
    materialComponent -> setNormalMap(GetTexture(aiTextureType_NORMALS, meshPath, material)) ;
    materialComponent -> setSpecularMap(GetTexture(aiTextureType_SPECULAR, meshPath, material)) ;

    // Get the other values of the material.
    float shininess ;
    aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess) ;
    materialComponent -> setShininess(shininess) ;
    SetAlphaBlendingMaterial(materialComponent) ;

    return materialComponent ;
}

std::unique_ptr<TextureImage2D> MaterialLoader::GetTexture(
    const aiTextureType type,
    const fs::path& meshPath,
    const aiMaterial* material
) {
    const int TextureIndex = 0 ;
    aiString assimpPath ;
    aiTextureMapMode mapMode[3] ;

    material -> GetTexture(
        type,
        TextureIndex,
        &assimpPath,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        mapMode
    ) ;

    auto texturePtr = std::make_unique<TextureImage2D>(GetFullTexturePath(meshPath, assimpPath)) ;
    return texturePtr ;
}

std::string MaterialLoader::GetFullTexturePath(
    const fs::path& meshPath,
    const aiString& assimpPath
) {
    // Use an absolute path to the texture.
    fs::path absoluteTexturePath ;
    fs::path texturePath(assimpPath.C_Str()) ;

    if (texturePath.is_absolute()) {
        absoluteTexturePath = texturePath ;
    }
    else {
        absoluteTexturePath = meshPath.parent_path() / texturePath ;
    }

    return absoluteTexturePath.string() ;
}

void MaterialLoader::SetAlphaBlendingMaterial(MaterialComponent* material) {
    auto& materialSettings = material -> settings() ;
    materialSettings.setAlphaBlendingMode(ForwardPassID, AlphaBlendingMode::AlphaBlend) ;
    materialSettings.setAlphaBlendingMode(DeferredPassID, AlphaBlendingMode::AlphaBlend) ;
}
