#include <scene/ogl/mesh/loader/MaterialLoader.hpp>
#include <utils/StringExt.hpp>

using namespace Hope ;
using namespace Hope::GL ;

const std::string MaterialLoader::TextureFolderName = "textures" ;
const std::list<std::string> MaterialLoader::TextureExtensions = { ".jpg", ".jpeg", ".png" } ;

const std::string MaterialLoader::AlbedoFilename = "albedo" ;
const std::string MaterialLoader::AmbientOcclusionFilename = "ao" ;
const std::string MaterialLoader::EmissiveFilename = "emissive" ;
const std::string MaterialLoader::HeightFilename = "height" ;
const std::string MaterialLoader::MetalnessFilename = "metalness" ;
const std::string MaterialLoader::NormalFilename = "normal" ;
const std::string MaterialLoader::RoughnessFilename = "roughness" ;

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

		// Albedo.
		pbrMat -> setAlbedo(
			PropertyColor(
				meshPath,
				material,
				AI_MATKEY_COLOR_DIFFUSE,
				AlbedoFilename
			)
		) ;

		// Ambient occlusion.
		pbrMat -> setAmbientOcclusion(
			PropertyValue(
				meshPath,
				material,
				nullptr, 1, 0,
				AmbientOcclusionFilename
			)
		) ;

		// Emissive.
		pbrMat -> setEmissive(
			PropertyColor(
				meshPath,
				material,
				AI_MATKEY_COLOR_EMISSIVE,
				EmissiveFilename
			)
		) ;

		// Metalness.
		pbrMat -> setMetalness(
			PropertyValue(
				meshPath,
				material,
				nullptr, 0, 0,
				MetalnessFilename
			)
		) ;

		// Normal.
		pbrMat -> setNormalMap(
			GetTexture(
				meshPath,
				NormalFilename
			)
		) ;

		// Roughness.
		pbrMat -> setRoughness(
			PropertyValue(
				meshPath,
				material,
				nullptr, 0, 0,
				RoughnessFilename
			)
		) ;

		return pbrMat ;
	}
}

Hope::ValueTexture MaterialLoader::PropertyValue(
	const fs::path& meshPath,
	const aiMaterial* material,
	const char* pKey,
	const unsigned int type,
	const unsigned int idx,
	const std::string& textureName
) {
	ValueTexture value ;
	value.setTexture(GetTexture(meshPath, textureName)) ;

	if (pKey) {
		float aiValue = 0.f ;

	    if (aiGetMaterialFloat(material, pKey, type, idx, &aiValue) == AI_SUCCESS) {
			value.setValue(aiValue) ;
		}
	}
	else {
		value.setValue(static_cast<float>(type)) ;
	}

	return value ;
}

Hope::ColorTexture MaterialLoader::PropertyColor(
	const fs::path& meshPath,
	const aiMaterial* material,
	const char* pKey,
	const unsigned int type,
	const unsigned int idx,
	const std::string& textureName
) {
	ColorTexture color ;
	color.setTexture(GetTexture(meshPath, textureName)) ;

	if (pKey) {
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
	const fs::path& meshPath,
	const std::string& textureName
) {
	std::string texturePath ;

	for (auto& extension : TextureExtensions) {
		fs::path textureFilename(textureName + extension) ;

		fs::path texturePath(TextureFolderName) ;
		texturePath = texturePath / meshPath.stem() / textureFilename ;

		fs::path absoluteTexturePath ;
		absoluteTexturePath = meshPath.parent_path() / texturePath ;

		if (fs::exists(absoluteTexturePath)) {
			auto texturePtr = std::make_unique<TextureImage2D>(absoluteTexturePath) ;
			return texturePtr ;
		}
	}

	return nullptr ;
}

void MaterialLoader::SetAlphaBlendingMaterial(MaterialComponent* material) {
    auto& materialSettings = material -> settings() ;
    materialSettings.setAlphaBlendingMode(ForwardPassID, AlphaBlendingMode::AlphaBlend) ;
    materialSettings.setAlphaBlendingMode(DeferredPassID, AlphaBlendingMode::AlphaBlend) ;
}
