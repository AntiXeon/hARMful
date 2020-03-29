#include <scene/components/materials/deferred/SSAOBlurMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <memory>

#ifdef OGL
    #define NoTarget    GL_NONE
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/AoRendering.hpp>
#endif

using namespace Hope ;

SSAOBlurMaterialComponent::SSAOBlurMaterialComponent(
    const AbstractFramebufferRenderNode* aoBuffer
)
    : MaterialComponent(),
      m_aoBuffer(aoBuffer) {
    setupForwardShader() ;
}

void SSAOBlurMaterialComponent::updateUniformValues(const Hope::RenderPassID) {
    const API::Framebuffer* framebuffer = m_aoBuffer -> framebuffer() ;
    framebuffer -> bindUnitColor(SSAORenderNode::AORenderTarget) ;
}

void SSAOBlurMaterialComponent::setupUniforms() {}

void SSAOBlurMaterialComponent::setupForwardShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(ForwardPassID) ;
    API::ShaderProgram* shaderProgram = renderPass -> shaderProgram() ;

    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(AoRenderingSsaoVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(AoRenderingBlurFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}
