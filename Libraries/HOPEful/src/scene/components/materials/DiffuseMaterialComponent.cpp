#include <scene/components/materials/DiffuseMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/materials/DiffuseMap.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/Shadows.hpp>
#endif

using namespace Hope ;

DiffuseMaterialComponent::DiffuseMaterialComponent()
    : MaterialComponent(),
      m_ambient(Color(0.f, 0.f, 0.f)),
      m_diffuse(nullptr),
      m_specular(Color(1.f, 1.f, 1.f)),
      m_shininess(10.f) {
    setupRendering() ;
    setupUniforms() ;
}

void DiffuseMaterialComponent::updateUniformValues(const Hope::RenderPassID pass) {
    if (pass == DeferredPassID) {
        if (m_diffuse) {
            m_diffuse -> bindUnit(DiffuseMapBinding) ;
        }

        uniforms(DeferredPassID).at(UniformNames::MaterialAmbientUniformName()) -> setVec3(m_ambient.toRGB()) ;
        uniforms(DeferredPassID).at(UniformNames::MaterialSpecularUniformName()) -> setVec3(m_specular.toRGB()) ;
        uniforms(DeferredPassID).at(UniformNames::MaterialShininessUniformName()) -> setFloating(m_shininess) ;
    }
}

void DiffuseMaterialComponent::setupUniforms() {
    auto ambientUniform = std::make_unique<Hope::ShaderUniform>() ;
    ambientUniform -> setName(UniformNames::MaterialAmbientUniformName()) ;
    ambientUniform -> setLocation(UniformNames::AmbientLocation) ;
    uniforms(DeferredPassID).add(std::move(ambientUniform)) ;

    auto specularUniform = std::make_unique<Hope::ShaderUniform>() ;
    specularUniform -> setName(UniformNames::MaterialSpecularUniformName()) ;
    specularUniform -> setLocation(UniformNames::SpecularLocation) ;
    uniforms(DeferredPassID).add(std::move(specularUniform)) ;

    auto shininessUniform = std::make_unique<Hope::ShaderUniform>() ;
    shininessUniform -> setName(UniformNames::MaterialShininessUniformName()) ;
    shininessUniform -> setLocation(UniformNames::ShininessLocation) ;
    uniforms(DeferredPassID).add(std::move(shininessUniform)) ;
}

void DiffuseMaterialComponent::setupForwardShader() {}

void DiffuseMaterialComponent::setupDeferredShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(DeferredPassID) ;
    API::ShaderProgram* shaderProgram = renderPass -> shaderProgram() ;

    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseMapDeferredVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseMapDeferredFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}
