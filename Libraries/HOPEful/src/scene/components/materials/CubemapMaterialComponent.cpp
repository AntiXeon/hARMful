#include <scene/components/materials/CubemapMaterialComponent.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BlockBindings.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/BaseDataBlock.hpp>
#include <scene/components/materials/shaders/GL/4.5/modules/Directive.hpp>
#include <scene/components/materials/shaders/GL/4.5/MaterialCubemap.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#include <iostream>

using namespace Hope ;

CubemapMaterialComponent::CubemapMaterialComponent()
    : MaterialComponent(),
      m_map(nullptr) {
    setupRendering() ;
    setupUniforms() ;
}

CubemapMaterialComponent::~CubemapMaterialComponent() {
    delete m_map ;
}

void CubemapMaterialComponent::updateUniformValues() {
    if (m_map) {
        m_map -> activate() ;
        m_map -> bind() ;
        uniform(UniformNames::MaterialCubemapUniformName()) -> setInteger(CubemapBinding) ;
    }
}

void CubemapMaterialComponent::setupUniforms() {
    std::shared_ptr<Hope::ShaderUniform> cubemapUniform = std::make_shared<Hope::ShaderUniform>() ;
    cubemapUniform -> setName(UniformNames::MaterialCubemapUniformName()) ;
    addShaderUniform(cubemapUniform) ;
}

void CubemapMaterialComponent::setupDefaultRenderPass() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(DefaultPassID) ;
    std::shared_ptr<API::DepthTest> depthTest = std::make_shared<API::DepthTest>() ;
    depthTest -> setFunction(API::DepthTest::LessOrEqual) ;
    renderPass -> addCapability(depthTest) ;

    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addVertexShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addVertexShaderCode(MaterialCubemapVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(DirectiveFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BlockBindingsFragmentCode) ;
    shaderProgram -> addFragmentShaderCode(BaseDataBlockVertexCode) ;
    shaderProgram -> addFragmentShaderCode(MaterialCubemapFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}

void CubemapMaterialComponent::setupDiffuseRenderPass() {
}

void CubemapMaterialComponent::setupNormalRenderPass() {
}

void CubemapMaterialComponent::setupSpecularRenderPass() {
}
