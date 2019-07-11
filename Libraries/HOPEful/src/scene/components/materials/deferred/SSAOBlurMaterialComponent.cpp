#include <scene/components/materials/deferred/SSAOBlurMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/450/effects/AoRendering.hpp>
#endif

using namespace Hope ;

SSAOBlurMaterialComponent::SSAOBlurMaterialComponent(
    const FramebufferRenderNode* aoBuffer,
    const FramebufferRenderNode* gBuffer
)
    : MaterialComponent(),
      m_aoBuffer(aoBuffer),
      m_gBuffer(gBuffer) {
    setupForwardShader() ;
}

void SSAOBlurMaterialComponent::updateUniformValues() {
    const API::Framebuffer2D* aoFramebuffer = m_aoBuffer -> framebuffer() ;
    aoFramebuffer -> bind(API::Framebuffer2D::ReadOnly) ;
    aoFramebuffer -> bindUnitColor(SSAORenderNode::AlbedoRenderTarget) ;
}

void SSAOBlurMaterialComponent::setupForwardShader() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(ForwardPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(AoRenderingSsaoVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(AoRenderingBlurFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
