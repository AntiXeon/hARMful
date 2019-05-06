#include <scene/components/materials/DiffuseNormalSpecularMaterialComponent.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BlockBindings.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BaseDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/ModelDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/Directive.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/AmountLights.hpp>
#include <scene/components/materials/shaders/GL/4.5/FunctionsLightCompute.hpp>
#include <scene/components/materials/shaders/GL/4.5/FunctionsUtility.hpp>
#include <scene/components/materials/shaders/GL/4.5/MaterialDiffuseNormalSpecularMap.hpp>
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

void DiffuseNormalSpecularMaterialComponent::setupRendering() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>() ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(MaterialDiffuseNormalSpecularMapVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(AmountLightsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(MaterialDiffuseNormalSpecularMapFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
