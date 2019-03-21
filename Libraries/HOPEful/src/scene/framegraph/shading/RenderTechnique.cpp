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

void RenderTechnique::addShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) {
    m_shaderAttribs.insert(attrib) ;
}

void RenderTechnique::removeShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) {
    m_shaderAttribs.erase(attrib) ;
}

void RenderTechnique::addRenderPass(const std::shared_ptr<API::RenderPass> pass) {
    m_renderPasses.insert(pass) ;
}

void RenderTechnique::removeRenderPass(const std::shared_ptr<API::RenderPass> pass) {
    m_renderPasses.erase(pass) ;
}
