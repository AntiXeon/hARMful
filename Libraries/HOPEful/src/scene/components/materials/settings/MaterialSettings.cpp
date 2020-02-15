#include <scene/components/materials/settings/MaterialSettings.hpp>
#include <cassert>

#ifdef OGL
    #include <scene/ogl/rendering/capabilities/AlphaTest.hpp>
    #include <scene/ogl/rendering/capabilities/BlendEquation.hpp>
#endif

using namespace Hope ;

void MaterialSettings::setAlphaBlendingMode(
    const RenderPassID pass,
    const AlphaBlendingMode mode
) {
    API::RenderPass* renderPass = m_effect -> renderPass(pass) ;

    if (!renderPass || (mode == m_alphaBlend)) {
        return ;
    }

    // Remove the previous capability.
    API::CapabilityType previousCapability = findAlphaCapabilityType(m_alphaBlend) ;
    renderPass -> removeCapability(previousCapability) ;

    // Use the new capability.
    if (mode == AlphaBlendingMode::AlphaBlend) {
        std::shared_ptr<API::BlendEquation> blendEquation = std::make_shared<API::BlendEquation>() ;
        renderPass -> addCapability(blendEquation) ;
    }
    else if (mode == AlphaBlendingMode::AlphaClip) {
        std::shared_ptr<API::AlphaTest> alphaTest = std::make_shared<API::AlphaTest>() ;
        renderPass -> addCapability(alphaTest) ;
    }
}

void MaterialSettings::setShadowMode(const ShadowMode mode) {
    API::RenderPass* renderPass = m_effect -> renderPass(DirectionalShadowPassID) ;
    assert(renderPass != nullptr) ;

    ShadowMode previousMode = m_shadowMode ;
    m_shadowMode = mode ;

    // Remove the previous mode capability.
    if ((mode != previousMode) && (mode != ShadowMode::AlphaClip)) {
        renderPass -> removeCapability(Hope::GL::CapabilityType::AlphaTest) ;
        return ;
    }

    // In case of AlphaClip, add the AlphaTest capability.
    std::shared_ptr<API::AlphaTest> alphaTest = std::make_shared<API::AlphaTest>() ;
    renderPass -> addCapability(alphaTest) ;
}

API::CapabilityType MaterialSettings::findAlphaCapabilityType(const AlphaBlendingMode mode) {
    switch(mode) {
        case AlphaBlendingMode::AlphaBlend:
            return API::CapabilityType::BlendEquation ;

        case AlphaBlendingMode::AlphaClip:
            return API::CapabilityType::AlphaTest ;

        default:
            return API::CapabilityType::Undefined ;
    }
}
