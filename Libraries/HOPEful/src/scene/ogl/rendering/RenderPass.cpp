#include <scene/ogl/rendering/RenderPass.hpp>

using namespace Hope::GL ;

RenderPass::RenderPass() {
    m_shaderProgram = std::make_shared<ShaderProgram>() ;
}

void RenderPass::addFilterOption(const std::shared_ptr<Hope::FilterOption> option) {
    m_options.insert(option) ;
}

void RenderPass::removeFilterOption(const std::shared_ptr<Hope::FilterOption> option) {
    m_options.erase(option) ;
}

void RenderPass::addCapability(const std::shared_ptr<Hope::GL::Capability> capability) {
    m_capabilities.insert(capability) ;
}

void RenderPass::removeCapability(const std::shared_ptr<Hope::GL::Capability> capability) {
    m_capabilities.erase(capability) ;
}
