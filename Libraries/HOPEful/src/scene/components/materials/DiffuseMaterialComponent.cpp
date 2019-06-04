#include <scene/components/materials/DiffuseMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/450/materials/DiffuseMap.hpp>
    #include <scene/components/materials/shaders/GLSL/450/effects/Shadows.hpp>
    #include <scene/components/materials/shaders/GLSL/450/DeferredPasses.hpp>
#endif

using namespace Hope ;

DiffuseMaterialComponent::DiffuseMaterialComponent()
    : MaterialComponent(),
      m_ambient(Color(0.f, 0.f, 0.f)),
      m_diffuse(nullptr),
      m_specular(Color(1.f, 1.f, 1.f)),
      m_shininess(10.f) {
    setupRendering() ;
    setupUniforms() ;
}

DiffuseMaterialComponent::~DiffuseMaterialComponent() {
    delete m_diffuse ;
}

void DiffuseMaterialComponent::updateUniformValues() {
    if (m_diffuse) {
        m_diffuse -> bindUnit(DiffuseMapBinding) ;
    }

    uniform(UniformNames::MaterialAmbientUniformName()) -> setVec3(m_ambient.toRGB()) ;
    uniform(UniformNames::MaterialSpecularUniformName()) -> setVec3(m_specular.toRGB()) ;
    uniform(UniformNames::MaterialShininessUniformName()) -> setFloating(m_shininess) ;
}

void DiffuseMaterialComponent::setupUniforms() {
    std::shared_ptr<Hope::ShaderUniform> ambientUniform = std::make_shared<Hope::ShaderUniform>() ;
    ambientUniform -> setName(UniformNames::MaterialAmbientUniformName()) ;
    ambientUniform -> setLocation(UniformNames::AmbientLocation) ;
    addShaderUniform(ambientUniform) ;

    std::shared_ptr<Hope::ShaderUniform> specularUniform = std::make_shared<Hope::ShaderUniform>() ;
    specularUniform -> setName(UniformNames::MaterialSpecularUniformName()) ;
    specularUniform -> setLocation(UniformNames::SpecularLocation) ;
    addShaderUniform(specularUniform) ;

    std::shared_ptr<Hope::ShaderUniform> shininessUniform = std::make_shared<Hope::ShaderUniform>() ;
    shininessUniform -> setName(UniformNames::MaterialShininessUniformName()) ;
    shininessUniform -> setLocation(UniformNames::ShininessLocation) ;
    addShaderUniform(shininessUniform) ;
}

void DiffuseMaterialComponent::setupForwardShader() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(ForwardPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseMapForwardVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesTextureUnitsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ShadowsShadowCalculationModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseMapForwardFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}

void DiffuseMaterialComponent::setupDeferredShader() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(DeferredPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseMapDeferredVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseMapDeferredFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
