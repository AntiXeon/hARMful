#include <scene/framegraph/shading/RenderEffect.hpp>

using namespace Hope ;

void RenderEffect::addShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) {
    m_shaderAttribs[attrib -> name()] = attrib ;
}

void RenderEffect::removeShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) {
    m_shaderAttribs.erase(attrib -> name()) ;
}

void RenderEffect::addTechnique(const std::shared_ptr<RenderTechnique> technique) {
    m_techniques.insert(technique) ;
}

void RenderEffect::removeTechnique(const std::shared_ptr<RenderTechnique> technique) {
    m_techniques.erase(technique) ;
}
