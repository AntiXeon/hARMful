#include <scene/components/materials/DiffuseNormalSpecularMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/460/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/460/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/460/materials/DiffuseNormalSpecularMap.hpp>
    #include <scene/components/materials/shaders/GLSL/460/effects/Shadows.hpp>
#endif

using namespace Hope ;

DiffuseNormalSpecularMaterialComponent::DiffuseNormalSpecularMaterialComponent()
    : MaterialComponent(),
      m_ambient(Color(0.f, 0.f, 0.f)),
      m_diffuse(nullptr),
      m_normal(nullptr),
      m_specular(nullptr),
      m_shininess(10.f) {
    setupRendering() ;
    setupUniforms() ;
}

void DiffuseNormalSpecularMaterialComponent::updateUniformValues(const Hope::RenderPassID pass) {
    if (pass == DeferredPassID) {
        if (m_diffuse) {
            m_diffuse -> bindUnit(DiffuseMapBinding) ;
        }

        if (m_normal) {
            m_normal -> bindUnit(NormalMapBinding) ;
        }

        if (m_specular) {
            m_specular -> bindUnit(SpecularMapBinding) ;
        }

        uniforms(DeferredPassID).at(UniformNames::MaterialAmbientUniformName()) -> setVec3(m_ambient.toRGB()) ;
        uniforms(DeferredPassID).at(UniformNames::MaterialShininessUniformName()) -> setFloating(m_shininess) ;
    }
}

void DiffuseNormalSpecularMaterialComponent::setupUniforms() {
    auto ambientUniform = std::make_unique<Hope::ShaderUniform>() ;
    ambientUniform -> setName(UniformNames::MaterialAmbientUniformName()) ;
    ambientUniform -> setLocation(UniformNames::AmbientLocation) ;
    uniforms(DeferredPassID).add(std::move(ambientUniform)) ;

    auto shininessUniform = std::make_unique<Hope::ShaderUniform>() ;
    shininessUniform -> setName(UniformNames::MaterialShininessUniformName()) ;
    shininessUniform -> setLocation(UniformNames::ShininessLocation) ;
    uniforms(DeferredPassID).add(std::move(shininessUniform)) ;
}

void DiffuseNormalSpecularMaterialComponent::setupForwardShader() {}

void DiffuseNormalSpecularMaterialComponent::setupDeferredShader() {
    std::unique_ptr<API::RenderPass> renderPass = std::make_unique<API::RenderPass>(DeferredPassID) ;
    API::ShaderProgram* shaderProgram = renderPass -> shaderProgram() ;

    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseNormalSpecularMapDeferredVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseNormalSpecularMapDeferredFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(std::move(renderPass)) ;
}
