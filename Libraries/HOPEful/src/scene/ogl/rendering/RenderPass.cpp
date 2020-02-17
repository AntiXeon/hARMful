#include <scene/ogl/rendering/RenderPass.hpp>
#include <iostream>

using namespace Hope::GL ;

RenderPass::RenderPass(const RenderPassID id)
    : m_id(id) {
    m_shaderProgram = std::make_unique<ShaderProgram>() ;
}

void RenderPass::addFilterOption(const std::shared_ptr<Hope::FilterOption> option) {
    m_options.insert(option) ;
}

void RenderPass::removeFilterOption(const std::shared_ptr<Hope::FilterOption> option) {
    m_options.erase(option) ;
}

bool RenderPass::addCapability(std::unique_ptr<Capability> capability) {
    if (m_capabilities.count(capability -> type()) == 0) {
        unsigned int index = m_capabilitiesPointers.size() ;
        m_capabilitiesPointers.push_back(capability.get()) ;

        auto type = capability -> type() ;
        m_capabilities.insert(
            std::make_pair(
                type,
                CapabilityIndex({
                    index,
                    std::move(capability)
                })
            )
        ) ;
        return true ;
    }

    return false ;
}

void RenderPass::removeCapability(const CapabilityType type) {
    if (m_capabilities.count(type) == 1) {
        size_t index = (m_capabilities.find(type) -> second).index ;
        m_capabilitiesPointers.erase(m_capabilitiesPointers.begin() + index) ;
        m_capabilities.erase(type) ;
    }
}

const Capability* RenderPass::capability(const CapabilityType type) const {
    if (m_capabilities.count(type) == 1) {
        return (m_capabilities.find(type) -> second).capability.get() ;
    }

    return nullptr ;
}
