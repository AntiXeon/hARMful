#include <scene/components/materials/MaterialComponent.hpp>
#include <cassert>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/Shadows.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
#endif

using namespace Hope ;

MaterialComponent::MaterialComponent(const bool drawShadow)
    : Component(ClassType) {
    m_settings.setRenderEffect(&m_effect) ;

    if (drawShadow) {
        setupDirectionalLightDepthMapShader() ;
    }
}

void MaterialComponent::generateUniform(
	RenderPassID passID,
	const std::string& name,
	const unsigned short location
) {
	auto uniform = std::make_unique<Hope::ShaderUniform>() ;
	uniform -> setName(name) ;
	uniform -> setLocation(location) ;
	uniforms(passID).add(std::move(uniform)) ;
}

void MaterialComponent::setupRendering() {
    // Setup shaders for the different rendering passes.
    setupForwardShader() ;
    setupDeferredShader() ;
}

void MaterialComponent::setupDirectionalLightDepthMapShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(DirectionalShadowPassID) ;
    API::ShaderProgram* shaderProgram = renderPass -> shaderProgram() ;

	auto depthClamping = std::make_unique<API::DepthClamping>() ;
	renderPass -> addCapability(std::move(depthClamping)) ;

    auto culling = std::make_unique<API::FaceCulling>();
    culling -> setCullMode(API::FaceCulling::Back);
    renderPass -> addCapability(std::move(culling));

    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ShadowsDirLightShadowsVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ShadowsDirLightShadowsFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}
