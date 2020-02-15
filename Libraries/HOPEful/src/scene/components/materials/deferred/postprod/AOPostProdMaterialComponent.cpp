#include <scene/components/materials/deferred/postprod/AOPostProdMaterialComponent.hpp>
#include <scene/framegraph/deferred/subtree/ShadingStepNode.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/DeferredRendering.hpp>
#endif

using namespace Hope ;

AOPostProdMaterialComponent::AOPostProdMaterialComponent(const FramebufferRenderNode* framebufferNode)
    : MaterialComponent(),
      m_framebufferNode(framebufferNode) {
    setupForwardShader() ;
}

void AOPostProdMaterialComponent::updateUniformValues() {
    const API::Framebuffer* framebuffer = m_framebufferNode -> framebuffer() ;
    framebuffer -> bindUnitColor(ShadingStepNode::ShadingRenderTarget) ;
    framebuffer -> bindUnitColor(SSAORenderNode::AORenderTarget) ;
}

void AOPostProdMaterialComponent::setupForwardShader() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(ForwardPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(DeferredRenderingShadingVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesTextureUnitsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DeferredRenderingAoApplyFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
