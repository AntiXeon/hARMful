#include <scene/ogl/mesh/loader/MaterialLoader.hpp>
#include <scene/components/materials/PBRMaterialComponent.hpp>

using namespace Hope ;
using namespace Hope::GL ;

std::unique_ptr<MaterialComponent> MaterialLoader::ConvertMaterial(
    const fs::path& /*meshPath*/,
    const aiMaterial* material
) {
	// Override the default material from Assimp.
	static const aiString DefaultMaterialName(AI_DEFAULT_MATERIAL_NAME) ;
	aiString currentName ;
	material -> Get(AI_MATKEY_NAME, currentName) ;

	// if (currentName == DefaultMaterialName) {
	// 	auto defaultMaterial = std::make_unique<PBRMaterialComponent>() ;
	// 	return defaultMaterial ;
	// }
	// else {
	// 	return BlinnPhongMaterial(material) ;
	// }

	auto defaultMaterial = std::make_unique<PBRMaterialComponent>() ;
	return defaultMaterial ;
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
