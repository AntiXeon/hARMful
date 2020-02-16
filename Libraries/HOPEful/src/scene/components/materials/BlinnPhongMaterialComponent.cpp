#include <scene/components/materials/BlinnPhongMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/materials/BlinnPhong.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/Shadows.hpp>
#endif

using namespace Hope ;

const float BlinnPhongMaterialComponent::MinimumShininessClamp = 1.f ;
const float BlinnPhongMaterialComponent::MaximumShininessClamp = 512.f ;

BlinnPhongMaterialComponent::BlinnPhongMaterialComponent()
    : MaterialComponent(),
      m_ambient(Color(0.1f, 0.1f, 0.1f)),
      m_diffuse(Color(0.5f, 0.5f, 0.5f)),
      m_specular(Color(1.f, 1.f, 1.f)),
      m_shininess(10.f) {
    setupRendering() ;
    setupUniforms() ;
}

void BlinnPhongMaterialComponent::updateUniformValues() {
    uniforms().at(UniformNames::MaterialAmbientUniformName()) -> setVec3(m_ambient.toRGB()) ;
    uniforms().at(UniformNames::MaterialDiffuseUniformName()) -> setVec3(m_diffuse.toRGB()) ;
    uniforms().at(UniformNames::MaterialSpecularUniformName()) -> setVec3(m_specular.toRGB()) ;
    uniforms().at(UniformNames::MaterialShininessUniformName()) -> setFloating(m_shininess) ;
}

void BlinnPhongMaterialComponent::setupUniforms() {
    auto ambientUniform = std::make_unique<Hope::ShaderUniform>() ;
    ambientUniform -> setName(UniformNames::MaterialAmbientUniformName()) ;
    ambientUniform -> setLocation(UniformNames::AmbientLocation) ;
    uniforms().add(std::move(ambientUniform)) ;

    auto diffuseUniform = std::make_unique<Hope::ShaderUniform>() ;
    diffuseUniform -> setName(UniformNames::MaterialDiffuseUniformName()) ;
    diffuseUniform -> setLocation(UniformNames::DiffuseLocation) ;
    uniforms().add(std::move(diffuseUniform)) ;

    auto specularUniform = std::make_unique<Hope::ShaderUniform>() ;
    specularUniform -> setName(UniformNames::MaterialSpecularUniformName()) ;
    specularUniform -> setLocation(UniformNames::SpecularLocation) ;
    uniforms().add(std::move(specularUniform)) ;

    auto shininessUniform = std::make_unique<Hope::ShaderUniform>() ;
    shininessUniform -> setName(UniformNames::MaterialShininessUniformName()) ;
    shininessUniform -> setLocation(UniformNames::ShininessLocation) ;
    uniforms().add(std::move(shininessUniform)) ;
}

void BlinnPhongMaterialComponent::setupForwardShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(ForwardPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(BlinnPhongForwardVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesTextureUnitsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ShadowsShadowCalculationModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(BlinnPhongForwardFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}

void BlinnPhongMaterialComponent::setupDeferredShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(DeferredPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(BlinnPhongDeferredVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(BlinnPhongDeferredFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}
