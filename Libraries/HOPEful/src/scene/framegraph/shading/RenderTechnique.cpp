#include <scene/framegraph/shading/RenderTechnique.hpp>

using namespace Hope ;

void RenderTechnique::setAPI(
    const GraphicsAPI api,
    const int majorVersion,
    const int minorVersion
) {
    m_apiParameters.api = api ;
    m_apiParameters.majorVersion = majorVersion ;
    m_apiParameters.minorVersion = minorVersion ;
}

void RenderTechnique::addFilterOption(const std::shared_ptr<Hope::FilterOption> option) {
    m_options.insert(option) ;
}

void RenderTechnique::removeFilterOption(const std::shared_ptr<Hope::FilterOption> option) {
    m_options.erase(option) ;
}

void RenderTechnique::addShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) {
    m_shaderParams.insert(param) ;
}

void RenderTechnique::removeShaderParameter(const std::shared_ptr<Hope::ShaderParameter> param) {
    m_shaderParams.erase(param) ;
}

void RenderTechnique::addRenderPass(const std::shared_ptr<API::RenderPass> pass) {
    m_renderPasses.insert(pass) ;
}

void RenderTechnique::removeRenderPass(const std::shared_ptr<API::RenderPass> pass) {
    m_renderPasses.erase(pass) ;
}
