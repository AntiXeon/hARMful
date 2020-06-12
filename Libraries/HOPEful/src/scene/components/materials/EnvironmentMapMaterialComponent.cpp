#include <scene/components/materials/EnvironmentMapMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/materials/Cubemap.hpp>
#endif

using namespace Hope ;

EnvironmentMapMaterialComponent::EnvironmentMapMaterialComponent(API::EnvironmentMap* map)
    : MaterialComponent(false) {
    setupForwardShader() ;
    setupDeferredShader() ;

    if (map) {
        m_map = map -> envMap() ;
    }

    setupUniforms() ;
}

void EnvironmentMapMaterialComponent::updateUniformValues() {
    if (m_map) {
        m_map -> bindUnit(CubemapBinding) ;
    }
}

void EnvironmentMapMaterialComponent::setupUniforms() {
    generateUniform(
        DeferredPassID,
        UniformNames::MaterialCubemapUniformName(),
        CubemapBinding
    ) ;
}

void EnvironmentMapMaterialComponent::setupForwardShader() {}

void EnvironmentMapMaterialComponent::setupDeferredShader() {
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
