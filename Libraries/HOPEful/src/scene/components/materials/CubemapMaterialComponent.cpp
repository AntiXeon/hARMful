#include <scene/components/materials/CubemapMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/450/materials/Cubemap.hpp>
#endif

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

void CubemapMaterialComponent::setupForwardShader() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(ForwardPassID) ;
    std::shared_ptr<API::DepthTest> depthTest = std::make_shared<API::DepthTest>() ;
    depthTest -> setFunction(API::DepthTest::LessOrEqual) ;
    renderPass -> addCapability(depthTest) ;

    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(CubemapForwardVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(CubemapForwardFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}

void CubemapMaterialComponent::setupDeferredShader() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(DeferredPassID) ;
    std::shared_ptr<API::DepthTest> depthTest = std::make_shared<API::DepthTest>() ;
    depthTest -> setFunction(API::DepthTest::LessOrEqual) ;
    renderPass -> addCapability(depthTest) ;

    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(CubemapDeferredVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(CubemapDeferredFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
