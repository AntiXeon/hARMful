#include <scene/components/materials/BlinnPhongMaterialComponent.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BlockBindings.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BaseDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/ModelDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/Directive.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/AmountLights.hpp>
#include <scene/components/materials/shaders/GL/4.5/FunctionsLightCompute.hpp>
#include <scene/components/materials/shaders/GL/4.5/MaterialBlinnPhong.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

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
    uniform(UniformNames::MaterialAmbientUniformName()) -> setVec3(m_ambient.toRGB()) ;
    uniform(UniformNames::MaterialDiffuseUniformName()) -> setVec3(m_diffuse.toRGB()) ;
    uniform(UniformNames::MaterialSpecularUniformName()) -> setVec3(m_specular.toRGB()) ;
    uniform(UniformNames::MaterialShininessUniformName()) -> setFloating(m_shininess) ;
}

void BlinnPhongMaterialComponent::setupUniforms() {
    std::shared_ptr<Hope::ShaderUniform> ambientUniform = std::make_shared<Hope::ShaderUniform>() ;
    ambientUniform -> setName(UniformNames::MaterialAmbientUniformName()) ;
    addShaderUniform(ambientUniform) ;

    std::shared_ptr<Hope::ShaderUniform> diffuseUniform = std::make_shared<Hope::ShaderUniform>() ;
    diffuseUniform -> setName(UniformNames::MaterialDiffuseUniformName()) ;
    addShaderUniform(diffuseUniform) ;

    std::shared_ptr<Hope::ShaderUniform> specularUniform = std::make_shared<Hope::ShaderUniform>() ;
    specularUniform -> setName(UniformNames::MaterialSpecularUniformName()) ;
    addShaderUniform(specularUniform) ;

    std::shared_ptr<Hope::ShaderUniform> shininessUniform = std::make_shared<Hope::ShaderUniform>() ;
    shininessUniform -> setName(UniformNames::MaterialShininessUniformName()) ;
    addShaderUniform(shininessUniform) ;
}

void BlinnPhongMaterialComponent::setupRendering() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>() ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(MaterialBlinnPhongVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(ModelDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(AmountLightsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(MaterialBlinnPhongFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
