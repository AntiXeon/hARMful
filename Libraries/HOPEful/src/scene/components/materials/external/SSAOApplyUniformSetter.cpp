#include <scene/components/materials/external/SSAOApplyUniformSetter.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/components/materials/UniformNames.hpp>

#ifdef OGL
    #include <scene/components/materials/shaders/GLSL/includes/Ao.hpp>
    #include <GL/glew.h>
#endif

#include <utils/StringExt.hpp>

using namespace Hope ;

SSAOApplyUniformSetter::SSAOApplyUniformSetter() {
    std::shared_ptr<Hope::ShaderUniform> useAOUniform = std::make_shared<Hope::ShaderUniform>() ;
    useAOUniform -> setName(UniformNames::MaterialUseAOUniformName()) ;
    useAOUniform -> setLocation(UNIFORM_AO_USE_LOCATION) ;
    addShaderUniform(useAOUniform) ;
}

void SSAOApplyUniformSetter::updateUniforms() {
    uniform(UniformNames::MaterialUseAOUniformName()) -> setInteger(m_useAO) ;

    if (m_useAO) {
        FramebufferRenderNode* aoBufferNode = m_ssaoNode -> aoBuffer() ;
        API::Framebuffer2D* aoFramebuffer = aoBufferNode -> framebuffer() ;
        aoFramebuffer -> bindUnitColor(Hope::SSAORenderNode::AORenderTarget) ;
    }
}

void SSAOApplyUniformSetter::setSSAONode(Hope::SSAORenderNode* node) {
    m_useAO = node != nullptr ;

    if (!m_useAO || (m_ssaoNode == node)) {
        return ;
    }

    m_ssaoNode = node ;
}
