#include <scene/framegraph/shading/RenderEffect.hpp>

using namespace Hope ;

void RenderEffect::addShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) {
    m_shaderParams.insert(param) ;
}

void RenderEffect::removeShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) {
    m_shaderParams.erase(param) ;
}

void RenderEffect::addTechnique(const std::shared_ptr<RenderTechnique> technique) {
    m_techniques.insert(technique) ;
}

void RenderEffect::removeTechnique(const std::shared_ptr<RenderTechnique> technique) {
    m_techniques.erase(technique) ;
}
