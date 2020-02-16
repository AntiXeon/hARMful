#include <scene/components/materials/CubemapMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/materials/Cubemap.hpp>
#endif

using namespace Hope ;

CubemapMaterialComponent::CubemapMaterialComponent()
    : MaterialComponent(false),
      m_map(nullptr) {
    setupForwardShader() ;
    setupDeferredShader() ;

    setupUniforms() ;
}

CubemapMaterialComponent::~CubemapMaterialComponent() {
    delete m_map ;
}

void CubemapMaterialComponent::updateUniformValues() {
    if (m_map) {
        m_map -> activate() ;
        m_map -> bind() ;
        uniforms().at(UniformNames::MaterialCubemapUniformName()) -> setInteger(CubemapBinding) ;
    }
}

void CubemapMaterialComponent::setupUniforms() {
    auto cubemapUniform = std::make_unique<Hope::ShaderUniform>() ;
    cubemapUniform -> setName(UniformNames::MaterialCubemapUniformName()) ;
    uniforms().add(std::move(cubemapUniform)) ;
}

void CubemapMaterialComponent::setupForwardShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(ForwardPassID) ;
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

    effect().addRenderPass(std::move(renderPass)) ;
}

void CubemapMaterialComponent::setupDeferredShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(DeferredPassID) ;
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
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(CubemapDeferredFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}
