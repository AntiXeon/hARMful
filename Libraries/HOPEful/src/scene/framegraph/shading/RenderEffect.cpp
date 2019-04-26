#include <scene/framegraph/shading/RenderEffect.hpp>

using namespace Hope ;

void RenderEffect::addRenderPass(const std::shared_ptr<API::RenderPass> pass) {
    m_renderPasses.insert(pass) ;
}

void RenderEffect::removeRenderPass(const std::shared_ptr<API::RenderPass> pass) {
    m_renderPasses.erase(pass) ;
}
