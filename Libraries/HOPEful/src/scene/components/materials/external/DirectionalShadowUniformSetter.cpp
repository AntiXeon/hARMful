#include <scene/components/materials/external/DirectionalShadowUniformSetter.hpp>
#include <scene/components/materials/UniformNames.hpp>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/includes/TextureUnits.hpp>
#endif

using namespace Hope ;

DirectionalShadowUniformSetter::DirectionalShadowUniformSetter() {
    std::shared_ptr<Hope::ShaderUniform> useShadowUniform = std::make_shared<Hope::ShaderUniform>() ;
    useShadowUniform -> setName(UniformNames::MaterialUseShadowUniformName()) ;
    addShaderUniform(useShadowUniform) ;

    std::shared_ptr<Hope::ShaderUniform> shadowDepthUniform = std::make_shared<Hope::ShaderUniform>() ;
    shadowDepthUniform -> setName(UniformNames::MaterialShadowDepthUniformName()) ;
    addShaderUniform(shadowDepthUniform) ;
}

void DirectionalShadowUniformSetter::updateUniforms() {
    uniform(UniformNames::MaterialUseShadowUniformName()) -> setBoolean(m_useShadow) ;

    if (m_dirLightShadowNode && m_useShadow) {
        const API::Framebuffer& framebuffer = m_dirLightShadowNode -> depthFramebuffer() ;
        framebuffer.bindUnitDepth(SHADOW_DEPTH_MAP_BINDING_UNIT) ;
    }
}
