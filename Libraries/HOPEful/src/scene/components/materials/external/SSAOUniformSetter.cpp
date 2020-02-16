#include <scene/components/materials/external/SSAOUniformSetter.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/components/materials/UniformNames.hpp>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/includes/Ao.hpp>
    #include <GL/glew.h>
#endif

#include <utils/StringExt.hpp>

using namespace Hope ;

SSAOUniformSetter::SSAOUniformSetter() {
    auto useAOUniform = std::make_unique<Hope::ShaderUniform>() ;
    useAOUniform -> setName(UniformNames::MaterialUseAOUniformName()) ;
    useAOUniform -> setLocation(UNIFORM_AO_USE_LOCATION) ;
    uniforms().add(std::move(useAOUniform)) ;
}

void SSAOUniformSetter::updateUniforms() {
    uniforms().at(UniformNames::MaterialUseAOUniformName()) -> setInteger(m_useAO) ;

    if (m_useAO) {
        // Noise texture.
        m_ssaoNode -> noiseTexture() -> bindUnit(SSAORenderNode::NoiseRenderTarget) ;

        // Kernel.
        uint8_t sampleIndex = 0 ;
        const std::array<Mind::Vector3f, AO_KERNEL_SIZE>& kernel = m_ssaoNode -> kernel() ;
        for (const Mind::Vector3f& sample : kernel) {
            std::string strSampleIndex = Doom::StringExt::ToStringi(sampleIndex) ;

            std::string kernelName = UniformNames::MaterialAOKernelUniformName() + "[" + strSampleIndex + "]" ;
            uniforms().at(kernelName) -> setVec3(sample.toArray()) ;
            sampleIndex++ ;
        }
    }
}

void SSAOUniformSetter::setSSAONode(Hope::SSAORenderNode* node) {
    m_useAO = node != nullptr ;

    if (!m_useAO || (m_ssaoNode == node)) {
        return ;
    }

    m_ssaoNode = node ;

    for (uint8_t sampleIndex = 0 ; sampleIndex < AO_KERNEL_SIZE ; ++sampleIndex) {
        std::string strSampleIndex = Doom::StringExt::ToStringi(sampleIndex) ;
        std::string kernelName = UniformNames::MaterialAOKernelUniformName() + "[" + strSampleIndex + "]" ;

        auto kernalSampleUniform = std::make_unique<Hope::ShaderUniform>() ;
        kernalSampleUniform -> setName(kernelName) ;
        kernalSampleUniform -> setLocation(UNIFORM_AO_KERNEL_LOCATION + sampleIndex) ;
        uniforms().add(std::move(kernalSampleUniform)) ;
    }
}
