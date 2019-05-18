#include <scene/components/materials/DiffuseNormalSpecularMaterialComponent.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <memory>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/450/Modules.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Functions.hpp>
    #include <scene/components/materials/shaders/GLSL/450/modules/Includes.hpp>
    #include <scene/components/materials/shaders/GLSL/450/materials/DiffuseNormalSpecularMap.hpp>
    #include <scene/components/materials/shaders/GLSL/450/DeferredPasses.hpp>
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

DiffuseNormalSpecularMaterialComponent::~DiffuseNormalSpecularMaterialComponent() {
    delete m_diffuse ;
    delete m_normal ;
    delete m_specular ;
}

void DiffuseNormalSpecularMaterialComponent::updateUniformValues(const RenderPassID passID) {
    const bool ForwardRendering = passID == ForwardPassID ;

    if (ForwardRendering) {
        if (m_diffuse) {
            m_diffuse -> bindUnit(DiffuseMapBinding) ;
        }

        if (m_normal) {
            m_normal -> bindUnit(NormalMapBinding) ;
        }

        if (m_specular) {
            m_specular -> bindUnit(SpecularMapBinding) ;
        }
    }
    else {
        static const unsigned int TextureUnit0 = DiffuseMapBinding ;
        switch (passID) {
            case AlbedoPassID:
                m_diffuse -> bindUnit(TextureUnit0) ;
                break ;

            case NormalPassID:
                m_normal -> bindUnit(TextureUnit0) ;
                break ;

            case SpecularPassID:
                m_specular -> bindUnit(TextureUnit0) ;
                break ;
        }
    }

    uniform(UniformNames::MaterialAmbientUniformName()) -> setVec3(m_ambient.toRGB()) ;
    uniform(UniformNames::MaterialShininessUniformName()) -> setFloating(m_shininess) ;
}

void DiffuseNormalSpecularMaterialComponent::setupUniforms() {
    std::shared_ptr<Hope::ShaderUniform> ambientUniform = std::make_shared<Hope::ShaderUniform>() ;
    ambientUniform -> setName(UniformNames::MaterialAmbientUniformName()) ;
    addShaderUniform(ambientUniform) ;

    std::shared_ptr<Hope::ShaderUniform> diffuseMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    diffuseMapUniform -> setName(UniformNames::MaterialDiffuseUniformName()) ;
    addShaderUniform(diffuseMapUniform) ;

    std::shared_ptr<Hope::ShaderUniform> normalMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    normalMapUniform -> setName(UniformNames::MaterialNormalUniformName()) ;
    addShaderUniform(normalMapUniform) ;

    std::shared_ptr<Hope::ShaderUniform> specularMapUniform = std::make_shared<Hope::ShaderUniform>() ;
    specularMapUniform -> setName(UniformNames::MaterialSpecularUniformName()) ;
    addShaderUniform(specularMapUniform) ;

    std::shared_ptr<Hope::ShaderUniform> shininessUniform = std::make_shared<Hope::ShaderUniform>() ;
    shininessUniform -> setName(UniformNames::MaterialShininessUniformName()) ;
    addShaderUniform(shininessUniform) ;
}

void DiffuseNormalSpecularMaterialComponent::setupForwardRenderPass() {
    std::shared_ptr<API::RenderPass> renderPass = std::make_shared<API::RenderPass>(ForwardPassID) ;
    std::shared_ptr<API::ShaderProgram> shaderProgram = renderPass -> shaderProgram() ;
    // Vertex shader code.
    shaderProgram -> addVertexShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addVertexShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addVertexShaderCode(DiffuseNormalSpecularMapForwardVertexCode) ;
    // Fragment shader code.
    shaderProgram -> addFragmentShaderCode(ModulesDirectiveModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesBlockBindingsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesBaseDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(ModulesModelDataBlockModuleCode) ;
    shaderProgram -> addFragmentShaderCode(IncludesAmountLightsModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsLightComputeModuleCode) ;
    shaderProgram -> addFragmentShaderCode(FunctionsUtilityModuleCode) ;
    shaderProgram -> addFragmentShaderCode(DiffuseNormalSpecularMapForwardFragmentCode) ;
    shaderProgram -> build() ;

    effect().addRenderPass(renderPass) ;
}
