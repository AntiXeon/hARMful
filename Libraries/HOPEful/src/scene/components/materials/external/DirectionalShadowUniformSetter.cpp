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
    auto useShadowUniform = std::make_unique<Hope::ShaderUniform>() ;
    useShadowUniform -> setName(UniformNames::MaterialUseShadowUniformName()) ;
    useShadowUniform -> setLocation(UNIFORM_SHADOW_USE_LOCATION) ;
    uniforms().add(std::move(useShadowUniform)) ;
}

void DirectionalShadowUniformSetter::updateUniforms() {
    uniforms().at(UniformNames::MaterialUseShadowUniformName()) -> setInteger(m_useShadow) ;

    if (m_useShadow) {
        const API::Framebuffer2DStack* framebuffer = m_dirLightShadowNode -> depthFramebuffer() ;
        framebuffer -> bindUnitDepth(SHADOW_DEPTH_MAP_BINDING_UNIT) ;

        uniforms().at(UniformNames::MaterialAmountCascadesUniformName()) -> setInteger(m_dirLightShadowNode -> amountCascades()) ;

        int amountCascades = m_dirLightShadowNode -> amountCascades() ;
        for (int cascadeIndex = 0 ; cascadeIndex < amountCascades ; ++cascadeIndex) {
            const ShadowCascade& cascade = m_dirLightShadowNode -> cascade(cascadeIndex) ;
            std::string strCascadeIndex = Doom::StringExt::ToStringi(cascadeIndex) ;

            // Cascade split uniforms.
            std::string cascadeSplitName = UniformNames::MaterialCascadedSplitsUniformName() + "[" + strCascadeIndex + "]" ;
            uniforms().at(cascadeSplitName) -> setFloating(cascade.relativeFarPlane()) ;

            // Light view projection matrix.
            Mind::Matrix4x4f viewProjectionMatrix = cascade.projectionMatrix() * cascade.viewMatrix() ;
            viewProjectionMatrix.transposed(viewProjectionMatrix) ;

            std::string lightMatrixName = UniformNames::MaterialLightViewProjectionMatricesUniformName() + "[" + strCascadeIndex + "]" ;
            uniforms().at(lightMatrixName) -> setMat4(viewProjectionMatrix.toArray()) ;
        }
    }
}

void DirectionalShadowUniformSetter::setLightShadowNode(const Hope::DirectionalLightShadowNode* node) {
    if ((node == nullptr) || (m_dirLightShadowNode == node)) {
        return ;
    }

    m_useShadow = node != nullptr ;

    m_dirLightShadowNode = node ;
    auto amountCascadesUniform = std::make_unique<Hope::ShaderUniform>() ;
    amountCascadesUniform -> setName(UniformNames::MaterialAmountCascadesUniformName()) ;
    amountCascadesUniform -> setLocation(UNIFORM_SHADOW_AMOUNT_CASCADE_LOCATION) ;
    uniforms().add(std::move(amountCascadesUniform)) ;

    int amountCascades = m_dirLightShadowNode -> amountCascades() ;
    for (int cascadeIndex = 0 ; cascadeIndex < amountCascades ; ++cascadeIndex) {
        std::string strCascadeIndex = Doom::StringExt::ToStringi(cascadeIndex) ;

        // Cascade split uniforms.
        auto cascadedSplitUniform = std::make_unique<Hope::ShaderUniform>() ;
        std::string cascadeSplitName = UniformNames::MaterialCascadedSplitsUniformName() + "[" + strCascadeIndex + "]" ;
        cascadedSplitUniform -> setName(cascadeSplitName) ;
        cascadedSplitUniform -> setLocation(UNIFORM_SHADOW_CASCADED_SPLITS_LOCATION + cascadeIndex) ;
        uniforms().add(std::move(cascadedSplitUniform)) ;

        // Light view matrices.
        auto lightMatrixUniform = std::make_unique<Hope::ShaderUniform>() ;
        std::string lightMatrixName = UniformNames::MaterialLightViewProjectionMatricesUniformName() + "[" + strCascadeIndex + "]" ;
        lightMatrixUniform -> setName(lightMatrixName) ;
        lightMatrixUniform -> setLocation(UNIFORM_SHADOW_CASCADE_MATRICES_LOCATION + cascadeIndex) ;
        uniforms().add(std::move(lightMatrixUniform)) ;
    }
}
