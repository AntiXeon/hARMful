#include <scene/components/materials/deferred/SSAOMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/includes/TextureUnits.hpp>
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/AoRendering.hpp>
#endif

using namespace Hope ;

SSAOMaterialComponent::SSAOMaterialComponent(const AbstractFramebufferRenderNode* gBuffer)
    : MaterialComponent(),
      m_gBuffer(gBuffer) {
    setupForwardShader() ;
}

void SSAOMaterialComponent::updateUniformValues(const Hope::RenderPassID) {
    const API::Framebuffer* framebuffer = m_gBuffer -> framebuffer() ;
    framebuffer -> bindUnitColor(GBufferRenderNode::AlbedoRenderTarget) ;
    framebuffer -> bindUnitColor(GBufferRenderNode::NormalRenderTarget) ;
    framebuffer -> bindUnitDepth(GBufferRenderNode::DepthRenderTarget) ;
}

void SSAOMaterialComponent::setupForwardShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(ForwardPassID) ;
    API::ShaderProgram* shaderProgram = renderPass -> shaderProgram() ;

    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(AoRenderingSsaoVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesTextureUnitsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesAoModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(AoRenderingSsaoFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}
