#include <scene/ogl/rendering/RenderPass.hpp>

using namespace Hope::GL ;

RenderPass::RenderPass(const RenderPassID id)
    : m_id(id) {
    m_shaderProgram = std::make_shared<ShaderProgram>() ;
}

void RenderPass::addFilterOption(const std::shared_ptr<Hope::FilterOption> option) {
    m_options.insert(option) ;
}

void RenderPass::removeFilterOption(const std::shared_ptr<Hope::FilterOption> option) {
    m_options.erase(option) ;
}

bool RenderPass::addCapability(const std::shared_ptr<Capability> capability) {
    if (m_capabilities.count(capability -> type()) == 0) {
        m_capabilities[capability -> type()] = capability ;
        return true ;
    }

    return false ;
}

std::shared_ptr<Capability> RenderPass::removeCapability(const CapabilityType type) {
    if (m_capabilities.count(type) == 1) {
        std::shared_ptr<Capability> capability = m_capabilities.find(type) -> second ;
        m_capabilities.erase(type) ;
        return capability ;
    }

    return nullptr;
}

std::shared_ptr<Capability> RenderPass::capability(const CapabilityType type) const {
    if (m_capabilities.count(type) == 1) {
        return m_capabilities.find(type) -> second ;
    }

    return nullptr ;
}
