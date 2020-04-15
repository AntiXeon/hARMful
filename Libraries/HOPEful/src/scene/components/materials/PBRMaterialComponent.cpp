#include <scene/components/materials/PBRMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/materials/Pbr.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/Shadows.hpp>
#endif

using namespace Hope ;

PBRMaterialComponent::PBRMaterialComponent()
    : MaterialComponent() {
	m_albedo.setColor(Color(0.9f, 0.9f, 0.9f)) ;
	m_metalness.setValue(0.f) ;
	m_roughness.setValue(0.4f) ;
	m_ao.setValue(1.f) ;

    setupRendering() ;
    setupUniforms() ;
}

void PBRMaterialComponent::updateUniformValues() {
	// Albedo.
	bind(
		m_albedo,
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialAlbedoVertexUniformName()),
		AlbedoTextureValueBinding,
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialAlbedoUseTextureUniformName())
	) ;
	// Metalness.
	bind(
		m_metalness,
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialMetalnessVertexUniformName()),
		MetalnessTextureValueBinding,
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialMetalnessUseTextureUniformName())
	) ;
	// Emissive.
	bind(
		m_emissive,
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialEmissiveVertexUniformName()),
		EmissiveTextureValueBinding,
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialEmissiveUseTextureUniformName())
	) ;
	// Roughness.
	bind(
		m_roughness,
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialRoughnessVertexUniformName()),
		RoughnessTextureValueBinding,
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialRoughnessUseTextureUniformName())
	) ;
	// Ambient occlusion.
	bind(
		m_ao,
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialAOVertexUniformName()),
		AOUseTextureBinding,
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialAOUseTextureUniformName())
	) ;

	// Normal map.
	const float NormalMapPercentage = 1.f ;
	bind(
		NormalTextureValueBinding,
		m_normal.get(),
		uniforms(DeferredPassID).at(UniformNames::PBRMaterialNormalUseTextureUniformName()),
		NormalMapPercentage
	) ;
}

void PBRMaterialComponent::generateValueUniforms(
	RenderPassID passID,
	const std::array<UniformNameLocation, 3>& namesAndLocations
) {
	for (auto& uniformData : namesAndLocations) {
		generateUniform(passID, uniformData.name, uniformData.location) ;
	}
}

void PBRMaterialComponent::setupUniforms() {
	// Albedo.
	generateValueUniforms(
		DeferredPassID,
		{{
			{UniformNames::PBRMaterialAlbedoUseTextureUniformName(), AlbedoUseTextureBinding},
			{UniformNames::PBRMaterialAlbedoVertexUniformName(), AlbedoVertexValueBinding},
			{UniformNames::PBRMaterialAlbedoTextureUniformName(), AlbedoTextureValueBinding}
		}}
	) ;

	// Metalness.
	generateValueUniforms(
		DeferredPassID,
		{{
			{UniformNames::PBRMaterialMetalnessUseTextureUniformName(), MetalnessUseTextureBinding},
			{UniformNames::PBRMaterialMetalnessVertexUniformName(), MetalnessVertexValueBinding},
			{UniformNames::PBRMaterialMetalnessTextureUniformName(), MetalnessTextureValueBinding}
		}}
	) ;

	// Emissive.
	generateValueUniforms(
		DeferredPassID,
		{{
			{UniformNames::PBRMaterialEmissiveUseTextureUniformName(), EmissiveUseTextureBinding},
			{UniformNames::PBRMaterialEmissiveVertexUniformName(), EmissiveVertexValueBinding},
			{UniformNames::PBRMaterialEmissiveTextureUniformName(), EmissiveTextureValueBinding}
		}}
	) ;

	// Roughness.
	generateValueUniforms(
		DeferredPassID,
		{{
			{UniformNames::PBRMaterialRoughnessUseTextureUniformName(), RoughnessUseTextureBinding},
			{UniformNames::PBRMaterialRoughnessVertexUniformName(), RoughnessVertexValueBinding},
			{UniformNames::PBRMaterialRoughnessTextureUniformName(), RoughnessTextureValueBinding}
		}}
	) ;

	// AO.
	generateValueUniforms(
		DeferredPassID,
		{{
			{UniformNames::PBRMaterialAOUseTextureUniformName(), AOUseTextureBinding},
			{UniformNames::PBRMaterialAOVertexUniformName(), AOVertexValueBinding},
			{UniformNames::PBRMaterialAOTextureUniformName(), AOTextureValueBinding}
		}}
	) ;

	// Normal map.
	generateUniform(
		DeferredPassID,
		UniformNames::PBRMaterialNormalUseTextureUniformName(),
		NormalUseTextureBinding
	) ;

	generateUniform(
		DeferredPassID,
		UniformNames::PBRMaterialNormalTextureUniformName(),
		NormalTextureValueBinding
	) ;
}

void PBRMaterialComponent::setupDeferredShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(DeferredPassID) ;
    API::ShaderProgram* shaderProgram = renderPass -> shaderProgram() ;

    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(PbrDeferredVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(PbrDeferredFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}

void PBRMaterialComponent::bind(
	const ValueTexture& valueTexture,
	Hope::ShaderUniform* valueUniform,
	const unsigned short textureUnit,
	Hope::ShaderUniform* percentageUniform
) {
	valueUniform -> setFloating(valueTexture.value()) ;

	bind(
		textureUnit,
		valueTexture.texture(),
		percentageUniform,
		valueTexture.texturePercentage()
	) ;
}

void PBRMaterialComponent::bind(
	const ColorTexture& colorTexture,
	Hope::ShaderUniform* colorUniform,
	const unsigned short textureUnit,
	Hope::ShaderUniform* percentageUniform
) {
	colorUniform -> setVec3(colorTexture.color().toRGB()) ;

	bind(
		textureUnit,
		colorTexture.texture(),
		percentageUniform,
		colorTexture.texturePercentage()
	) ;
}

void PBRMaterialComponent::bind(
	const unsigned short bindingUnit,
	const API::TextureImage2D* texture,
	Hope::ShaderUniform* percentageUniform,
	const float percentage
) {
	if (texture) {
	    texture -> bindUnit(bindingUnit) ;
		percentageUniform -> setFloating(percentage) ;
	}
	else {
		percentageUniform -> setFloating(0.f) ;
	}
}
