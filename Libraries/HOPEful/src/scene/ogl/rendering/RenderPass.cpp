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

void RenderPass::addShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) {
    m_shaderAttribs[attrib -> name()] = attrib ;
}

void RenderPass::removeShaderAttribute(const std::shared_ptr<Hope::ShaderAttribute> attrib) {
    m_shaderAttribs.erase(attrib -> name()) ;
}

void RenderPass::addCapability(const std::shared_ptr<Hope::GL::Capability> capability) {
    m_capabilities.insert(capability) ;
}

void RenderPass::removeCapability(const std::shared_ptr<Hope::GL::Capability> capability) {
    m_capabilities.erase(capability) ;
}
