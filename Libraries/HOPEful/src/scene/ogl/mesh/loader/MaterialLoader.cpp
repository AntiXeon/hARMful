#include <scene/ogl/mesh/loader/MaterialLoader.hpp>

using namespace Hope ;
using namespace Hope::GL ;

std::unique_ptr<MaterialComponent> MaterialLoader::ConvertMaterial(
    const fs::path& meshPath,
    const aiMaterial* material
) {
	// Override the default material from Assimp.
	static const aiString DefaultMaterialName(AI_DEFAULT_MATERIAL_NAME) ;
	aiString currentName ;
	material -> Get(AI_MATKEY_NAME, currentName) ;

	if (currentName == DefaultMaterialName) {
		auto defaultMaterial = std::make_unique<PBRMaterialComponent>() ;
		return defaultMaterial ;
	}
	else {
		auto pbrMat = std::make_unique<PBRMaterialComponent>() ;

		// Albedo from diffuse.
		pbrMat -> setAlbedo(
			PropertyColor(
				meshPath,
				material,
				AI_MATKEY_COLOR_DIFFUSE,
				aiTextureType::aiTextureType_DIFFUSE
			)
		) ;

		// Emissive from emissive.
		pbrMat -> setEmissive(
			PropertyColor(
				meshPath,
				material,
				AI_MATKEY_COLOR_EMISSIVE,
				aiTextureType::aiTextureType_EMISSIVE
			)
		) ;

		// Normal from normal.
		if (material -> GetTextureCount(aiTextureType_NORMALS) > 0) {
			pbrMat -> setNormalMap(
				GetTexture(
				    aiTextureType::aiTextureType_NORMALS,
				    meshPath,
				    material
				)
			) ;
		}

		return pbrMat ;
	}
}

Hope::ValueTexture MaterialLoader::PropertyValue(
	const fs::path& meshPath,
	const aiMaterial* material,
	const char* pKey,
	const unsigned int type,
	const unsigned int idx,
	const aiTextureType propertyTextureType
) {
	ValueTexture value ;

	if (material -> GetTextureCount(propertyTextureType) > 0) {
		value.setTexture(GetTexture(propertyTextureType, meshPath, material)) ;
		value.setTexturePercentage(1.f) ;
	}
	else {
		float aiValue = 0.f ;

	    if (aiGetMaterialFloat(material, pKey, type, idx, &aiValue) == AI_SUCCESS) {
			value.setValue(aiValue) ;
		}
	}

	return value ;
}

Hope::ColorTexture MaterialLoader::PropertyColor(
	const fs::path& meshPath,
	const aiMaterial* material,
	const char* pKey,
	const unsigned int type,
	const unsigned int idx,
	const aiTextureType propertyTextureType
) {
	ColorTexture color ;

	if (material -> GetTextureCount(propertyTextureType) > 0) {
		color.setTexture(GetTexture(propertyTextureType, meshPath, material)) ;
		color.setTexturePercentage(1.f) ;
	}
	else {
		aiColor4D aiColor ;

		if (aiGetMaterialColor(material, pKey, type, idx, &aiColor) == AI_SUCCESS) {
			color.setColor(
				Color(aiColor.r, aiColor.g, aiColor.b, aiColor.a)
			) ;
		}
	}

	return color ;
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
