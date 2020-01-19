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
    const FramebufferRenderNode* aoBuffer
)
    : MaterialComponent(),
      m_aoBuffer(aoBuffer) {
    setupForwardShader() ;
}

void SSAOBlurMaterialComponent::updateUniformValues() {
    const API::Framebuffer2D* framebuffer = m_aoBuffer -> framebuffer() ;
    framebuffer -> bindUnitColor(SSAORenderNode::AORenderTarget) ;
}

void SSAOBlurMaterialComponent::setupUniforms() {
    std::shared_ptr<Hope::ShaderUniform> albedoUniform = std::make_shared<Hope::ShaderUniform>() ;
    albedoUniform -> setName(UniformNames::MaterialGBufferAlbedoUniformName()) ;
    addShaderUniform(albedoUniform) ;

    std::shared_ptr<Hope::ShaderUniform> specularUniform = std::make_shared<Hope::ShaderUniform>() ;
    specularUniform -> setName(UniformNames::MaterialGBufferSpecularUniformName()) ;
    addShaderUniform(specularUniform) ;

    std::shared_ptr<Hope::ShaderUniform> normalUniform = std::make_shared<Hope::ShaderUniform>() ;
    normalUniform -> setName(UniformNames::MaterialGBufferNormalUniformName()) ;
    addShaderUniform(normalUniform) ;

    std::shared_ptr<Hope::ShaderUniform> depthUniform = std::make_shared<Hope::ShaderUniform>() ;
    depthUniform -> setName(UniformNames::MaterialGBufferDepthUniformName()) ;
    addShaderUniform(depthUniform) ;
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
