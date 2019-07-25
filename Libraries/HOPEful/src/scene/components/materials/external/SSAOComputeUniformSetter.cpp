#include <scene/components/materials/external/SSAOComputeUniformSetter.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/components/materials/UniformNames.hpp>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/includes/Ao.hpp>
    #include <GL/glew.h>
#endif

#include <utils/StringExt.hpp>

using namespace Hope ;

SSAOComputeUniformSetter::SSAOComputeUniformSetter() {
    std::shared_ptr<Hope::ShaderUniform> useAOUniform = std::make_shared<Hope::ShaderUniform>() ;
    useAOUniform -> setName(UniformNames::MaterialUseAOUniformName()) ;
    useAOUniform -> setLocation(UNIFORM_AO_USE_LOCATION) ;
    addShaderUniform(useAOUniform) ;
}

void SSAOComputeUniformSetter::updateUniforms() {
    uniform(UniformNames::MaterialUseAOUniformName()) -> setInteger(m_useAO) ;

    if (m_useAO) {
        // Noise texture.
        m_ssaoNode -> noiseTexture() -> bindUnit(SSAORenderNode::NoiseRenderTarget) ;

        // Kernel.
        uint8_t sampleIndex = 0 ;
        const std::array<Mind::Vector3f, AO_KERNEL_SIZE>& kernel = m_ssaoNode -> kernel() ;
        for (const Mind::Vector3f& sample : kernel) {
            std::string strSampleIndex = Doom::StringExt::ToStringi(sampleIndex) ;

            std::string kernelName = UniformNames::MaterialAOKernelUniformName() + "[" + strSampleIndex + "]" ;
            uniform(kernelName) -> setVec3(sample.toArray()) ;
            sampleIndex++ ;
        }
    }
}

void SSAOComputeUniformSetter::setSSAONode(const Hope::SSAORenderNode* node) {
    m_useAO = node != nullptr ;

    if (!m_useAO || (m_ssaoNode == node)) {
        return ;
    }

    m_ssaoNode = node ;

    for (uint8_t sampleIndex = 0 ; sampleIndex < AO_KERNEL_SIZE ; ++sampleIndex) {
        std::string strSampleIndex = Doom::StringExt::ToStringi(sampleIndex) ;
        std::string kernelName = UniformNames::MaterialAOKernelUniformName() + "[" + strSampleIndex + "]" ;

        std::shared_ptr<Hope::ShaderUniform> kernalSampleUniform = std::make_shared<Hope::ShaderUniform>() ;
        kernalSampleUniform -> setName(kernelName) ;
        kernalSampleUniform -> setLocation(UNIFORM_AO_KERNEL_LOCATION + sampleIndex) ;
        addShaderUniform(kernalSampleUniform) ;
    }
}
