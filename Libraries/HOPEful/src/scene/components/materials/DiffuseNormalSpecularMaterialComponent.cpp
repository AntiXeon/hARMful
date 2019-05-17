#include <scene/components/materials/DiffuseNormalSpecularMaterialComponent.hpp>
#include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
#include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>
#include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>
#include <scene/components/materials/shaders/GLSL/450/materials/DiffuseNormalSpecularMap.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

using namespace Hope ;

DiffuseNormalSpecularMaterialComponent::DiffuseNormalSpecularMaterialComponent()
    : MaterialComponent(),
      m_ambient(Color(0.f, 0.f, 0.f)),
      m_diffuse(nullptr),
      m_normal(nullptr),
      m_specular(nullptr),
      m_shininess(10.f) {
    setupRendering() ;
    setupUniforms() ;
}

DiffuseNormalSpecularMaterialComponent::~DiffuseNormalSpecularMaterialComponent() {
    delete m_diffuse ;
    delete m_normal ;
    delete m_specular ;
}

void DiffuseNormalSpecularMaterialComponent::updateUniformValues() {
    if (m_diffuse) {
        m_diffuse -> activate(DiffuseMapBinding) ;
        m_diffuse -> bind() ;
        uniform(UniformNames::MaterialDiffuseUniformName()) -> setInteger(DiffuseMapBinding) ;
    }

    if (m_normal) {
        m_normal -> activate(NormalMapBinding) ;
        m_normal -> bind() ;
        uniform(UniformNames::MaterialNormalUniformName()) -> setInteger(NormalMapBinding) ;
    }

    if (m_specular) {
        m_specular -> activate(SpecularMapBinding) ;
        m_specular -> bind() ;
        uniform(UniformNames::MaterialSpecularUniformName()) -> setInteger(SpecularMapBinding) ;
    }

    uniform(UniformNames::MaterialAmbientUniformName()) -> setVec3(m_ambient.toRGB()) ;
    uniform(UniformNames::MaterialShininessUniformName()) -> setFloating(m_shininess) ;
}

void DiffuseNormalSpecularMaterialComponent::setupUniforms() {
    std::shared_ptr<Hope::ShaderUniform> ambientUniform = std::make_shared<Hope::ShaderUniform>() ;
    ambientUniform -> setName(UniformNames::MaterialAmbientUniformName()) ;
    addShaderUniform(ambientUniform) ;

    std::shared_ptr<Hope::ShaderUniform> diffuseMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    diffuseMapUniform -> setName(UniformNames::MaterialDiffuseUniformName()) ;
    addShaderUniform(diffuseMapUniform) ;

    std::shared_ptr<Hope::ShaderUniform> normalMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    normalMapUniform -> setName(UniformNames::MaterialNormalUniformName()) ;
    addShaderUniform(normalMapUniform) ;

    std::shared_ptr<Hope::ShaderUniform> specularMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    specularMapUniform -> setName(UniformNames::MaterialSpecularUniformName()) ;
    addShaderUniform(specularMapUniform) ;

    std::shared_ptr<Hope::ShaderUniform> shininessUniform = std::make_shared<Hope::ShaderUniform>() ;
    shininessUniform -> setName(UniformNames::MaterialShininessUniformName()) ;
    addShaderUniform(shininessUniform) ;
}

void DiffuseNormalSpecularMaterialComponent::setupDefaultRenderPass() {
    {
        std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(ForwardPassID) ;
        std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
        // Vertex shader code.
        shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(DiffuseNormalSpecularMapForwardVertexCode) ;
        // Fragment shader code.
        shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
        shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
        shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
        shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
        shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
        shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
        shaderProgram -> addFragmentShaderCode(DiffuseNormalSpecularMapForwardFragmentCode) ;
        shaderProgram -> build() ;

        effect().addRenderPass(renderPass) ;
    }

    // Albedo [deferred rendering] render pass
    {
        std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(AlbedoPassID) ;
        std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
        // Vertex shader code.
        shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(DiffuseNormalSpecularMapDeferredVertexPositionVertexCode) ;
        // Fragment shader code.
        shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addFragmentShaderCode(DiffuseNormalSpecularMapDeferredAlbedoFragmentCode) ;
        shaderProgram -> build() ;

        effect().addRenderPass(renderPass) ;
    }

    // Position [deferred rendering] render pass
    {
        std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(PositionPassID) ;
        std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
        // Vertex shader code.
        shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(DiffuseNormalSpecularMapDeferredVertexPositionVertexCode) ;
        // Fragment shader code.
        shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addFragmentShaderCode(DiffuseNormalSpecularMapDeferredPositionFragmentCode) ;
        shaderProgram -> build() ;

        effect().addRenderPass(renderPass) ;
    }

    // Normal [deferred rendering] render pass
    {
        std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(NormalPassID) ;
        std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
        // Vertex shader code.
        shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(DiffuseNormalSpecularMapDeferredVertexNormalVertexCode) ;
        // Fragment shader code.
        shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addFragmentShaderCode(DiffuseNormalSpecularMapDeferredNormalFragmentCode) ;
        shaderProgram -> build() ;

        effect().addRenderPass(renderPass) ;
    }

    // Specular [deferred rendering] render pass
    {
        std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(SpecularPassID) ;
        std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
        // Vertex shader code.
        shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(DiffuseNormalSpecularMapDeferredVertexNormalVertexCode) ;
        // Fragment shader code.
        shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addFragmentShaderCode(DiffuseNormalSpecularMapDeferredSpecularFragmentCode) ;
        shaderProgram -> build() ;

        effect().addRenderPass(renderPass) ;
    }

    // Texture coordinates [deferred rendering] render pass
    {
        std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(TexCoordPassID) ;
        std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
        // Vertex shader code.
        shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
        shaderProgram -> addVertexShaderCode(DiffuseNormalSpecularMapDeferredVertexTexcoordVertexCode) ;
        // Fragment shader code.
        shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
        shaderProgram -> addFragmentShaderCode(DiffuseNormalSpecularMapDeferredTexcoordFragmentCode) ;
        shaderProgram -> build() ;

        effect().addRenderPass(renderPass) ;
    }
}

void DiffuseNormalSpecularMaterialComponent::setupDiffuseRenderPass() {
}

void DiffuseNormalSpecularMaterialComponent::setupNormalRenderPass() {
}

void DiffuseNormalSpecularMaterialComponent::setupSpecularRenderPass() {
}
