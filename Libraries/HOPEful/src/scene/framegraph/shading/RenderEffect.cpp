#include <scene/framegraph/shading/RenderEffect.hpp>

using namespace Hope ;

void RenderEffect::addRenderPass(std::unique_ptr<API::RenderPass> pass) {
    //m_renderPasses[pass -> id()] = std::move(pass) ;
    RenderPassID passID = pass -> id() ;
    m_renderPasses.insert(std::make_pair(passID, std::move(pass))) ;
}

void RenderEffect::removeRenderPass(std::unique_ptr<API::RenderPass> pass) {
    m_renderPasses.erase(pass -> id()) ;
}
