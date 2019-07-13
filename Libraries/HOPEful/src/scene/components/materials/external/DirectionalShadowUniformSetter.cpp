#include <scene/components/materials/external/DirectionalShadowUniformSetter.hpp>
#include <scene/framegraph/deferred/effects/shadows/DirectionalLightShadowNode.hpp>
#include <scene/components/materials/UniformNames.hpp>
#include <utils/StringExt.hpp>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/includes/TextureUnits.hpp>

    #include <GL/glew.h>
#endif

using namespace Hope ;

DirectionalShadowUniformSetter::DirectionalShadowUniformSetter() {
    std::shared_ptr<Hope::ShaderUniform> useShadowUniform = std::make_shared<Hope::ShaderUniform>() ;
    useShadowUniform -> setName(UniformNames::MaterialUseShadowUniformName()) ;
    useShadowUniform -> setLocation(UNIFORM_SHADOW_USE_LOCATION) ;
    addShaderUniform(useShadowUniform) ;
}

void DirectionalShadowUniformSetter::updateUniforms() {
    uniform(UniformNames::MaterialUseShadowUniformName()) -> setInteger(m_useShadow) ;

    if (m_useShadow) {
        const API::Framebuffer2DStack* framebuffer = m_dirLightShadowNode -> depthFramebuffer() ;
        framebuffer -> bindUnitDepth(SHADOW_DEPTH_MAP_BINDING_UNIT) ;

        uniform(UniformNames::MaterialAmountCascadesUniformName()) -> setInteger(m_dirLightShadowNode -> amountCascades()) ;

        int amountCascades = m_dirLightShadowNode -> amountCascades() ;
        for (int cascadeIndex = 0 ; cascadeIndex < amountCascades ; ++cascadeIndex) {
            const ShadowCascade& cascade = m_dirLightShadowNode -> cascade(cascadeIndex) ;
            std::string strCascadeIndex = Doom::StringExt::ToStringi(cascadeIndex) ;

            // Cascade split uniforms.
            std::string cascadeSplitName = UniformNames::MaterialCascadedSplitsUniformName() + "[" + strCascadeIndex + "]" ;
            uniform(cascadeSplitName) -> setFloating(cascade.relativeFarPlane()) ;

            // Light view projection matrix.
            Mind::Matrix4x4f viewProjectionMatrix = cascade.projectionMatrix() * cascade.viewMatrix() ;
            viewProjectionMatrix.transposed(viewProjectionMatrix) ;

            std::string lightMatrixName = UniformNames::MaterialLightViewProjectionMatricesUniformName() + "[" + strCascadeIndex + "]" ;
            uniform(lightMatrixName) -> setMat4(viewProjectionMatrix.toArray()) ;
        }
    }
}

void DirectionalShadowUniformSetter::setLightShadowNode(const Hope::DirectionalLightShadowNode* node) {
    if ((node == nullptr) || (m_dirLightShadowNode == node)) {
        return ;
    }

    m_useShadow = node != nullptr ;

    m_dirLightShadowNode = node ;
    std::shared_ptr<Hope::ShaderUniform> amountCascadesUniform = std::make_shared<Hope::ShaderUniform>() ;
    amountCascadesUniform -> setName(UniformNames::MaterialAmountCascadesUniformName()) ;
    amountCascadesUniform -> setLocation(UNIFORM_SHADOW_AMOUNT_CASCADE_LOCATION) ;
    addShaderUniform(amountCascadesUniform) ;

    int amountCascades = m_dirLightShadowNode -> amountCascades() ;
    for (int cascadeIndex = 0 ; cascadeIndex < amountCascades ; ++cascadeIndex) {
        std::string strCascadeIndex = Doom::StringExt::ToStringi(cascadeIndex) ;

        // Cascade split uniforms.
        std::shared_ptr<Hope::ShaderUniform> cascadedSplitUniform = std::make_shared<Hope::ShaderUniform>() ;
        std::string cascadeSplitName = UniformNames::MaterialCascadedSplitsUniformName() + "[" + strCascadeIndex + "]" ;
        cascadedSplitUniform -> setName(cascadeSplitName) ;
        cascadedSplitUniform -> setLocation(UNIFORM_SHADOW_CASCADED_SPLITS_LOCATION + cascadeIndex) ;
        addShaderUniform(cascadedSplitUniform) ;

        // Light view matrices.
        std::shared_ptr<Hope::ShaderUniform> lightMatrixUniform = std::make_shared<Hope::ShaderUniform>() ;
        std::string lightMatrixName = UniformNames::MaterialLightViewProjectionMatricesUniformName() + "[" + strCascadeIndex + "]" ;
        lightMatrixUniform -> setName(lightMatrixName) ;
        lightMatrixUniform -> setLocation(UNIFORM_SHADOW_CASCADE_MATRICES_LOCATION + cascadeIndex) ;
        addShaderUniform(lightMatrixUniform) ;
    }
}
