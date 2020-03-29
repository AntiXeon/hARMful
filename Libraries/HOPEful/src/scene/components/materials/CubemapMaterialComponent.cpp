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

void CubemapMaterialComponent::updateUniformValues(const Hope::RenderPassID pass) {
    if (pass == DeferredPassID) {
        if (m_map) {
            m_map -> activate() ;
            m_map -> bind() ;
            uniforms(DeferredPassID).at(UniformNames::MaterialCubemapUniformName()) -> setInteger(CubemapBinding) ;
        }
    }
}

void CubemapMaterialComponent::setupUniforms() {
    auto cubemapUniform = std::make_unique<Hope::ShaderUniform>() ;
    cubemapUniform -> setName(UniformNames::MaterialCubemapUniformName()) ;
    uniforms(DeferredPassID).add(std::move(cubemapUniform)) ;
}

void CubemapMaterialComponent::setupForwardShader() {}

void CubemapMaterialComponent::setupDeferredShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(DeferredPassID) ;
    std::unique_ptr<API::DepthTest> depthTest = std::make_unique<API::DepthTest>() ;
    depthTest -> setFunction(API::DepthTest::LessOrEqual) ;
    renderPass -> addCapability(std::move(depthTest)) ;

    API::ShaderProgram* shaderProgram = renderPass -> shaderProgram() ;

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
