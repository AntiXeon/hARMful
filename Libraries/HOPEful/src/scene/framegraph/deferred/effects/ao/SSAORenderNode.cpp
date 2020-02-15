#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <scene/framegraph/ClearBuffersNode.hpp>
#include <scene/framegraph/MemoryBarrierNode.hpp>
#include <scene/framegraph/deferred/effects/EffectApplierNode.hpp>
#include <scene/framegraph/deferred/offscreen/OffscreenRenderingNode.hpp>
#include <scene/components/materials/deferred/SSAOMaterialComponent.hpp>
#include <scene/components/materials/deferred/SSAOBlurMaterialComponent.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>
#include <scene/SceneTypes.hpp>
#include <utils/Random.hpp>

using namespace Hope ;

SSAORenderNode::SSAORenderNode(
    GBufferRenderNode* gBuffer,
    FramebufferRenderNode* output,
    FrameGraphNode* parent
) : EffectFrameGraphNode(parent),
    m_gBuffer(gBuffer),
    m_output(output) {
    Doom::Random::Initialize() ;
    generateNoiseTexture() ;
    generateKernel() ;
    generateFramegraphSubtree() ;

    m_effectApplyData.setSSAO(this) ;
}

void SSAORenderNode::generateNoiseTexture() {
    std::array<float, NoiseTextureDataSize> noiseData ;

    for (int index = 0 ; index < NoiseTextureDataSize ; index += Mind::Vector4f::AmountCoords) {
        noiseData[index] = Doom::Random::GetNormalizedFloat() * 2.f - 1.f ;       // X
        noiseData[index + 1] = Doom::Random::GetNormalizedFloat() * 2.f - 1.f ;   // Y
        noiseData[index + 2] = 0.f ;
    }

    const static bool GenerateMipmap = true ;
    m_noiseTexture = std::make_shared<API::TextureImage2D>(
        Mind::Dimension2Di(NoiseTextureSideSize, NoiseTextureSideSize),
        API::InternalFormat::RedGreenBlueAlpha16f,
        API::PixelFormat::RedGreenBlueAlpha,
        API::PixelDataType::Float,
        noiseData.data(),
        GenerateMipmap
    ) ;

    m_noiseTexture -> setFiltering(API::FilterMode::Nearest, API::FilterMode::Nearest) ;
}

void SSAORenderNode::generateKernel() {
    for (int kernelIndex = 0 ; kernelIndex < AO_KERNEL_SIZE ; ++kernelIndex) {
        // Generate the sample.
        Mind::Vector3f sample(
            Doom::Random::GetNormalizedFloat() * 2.f - 1.f,
            Doom::Random::GetNormalizedFloat() * 2.f - 1.f,
            Doom::Random::GetNormalizedFloat()
        ) ;

        float squaredIndex = kernelIndex * kernelIndex ;
        float scale = squaredIndex / (AO_KERNEL_SIZE * AO_KERNEL_SIZE) ;

        const float LerpFrom = 0.1f ;
        const float LerpTo = 1.f ;
        sample *= LerpFrom * (1.f - scale) + LerpTo * scale ;
        m_kernel[kernelIndex] = sample ;
    }
}

void SSAORenderNode::generateFramegraphSubtree() {
    API::Framebuffer* gFramebuffer = m_gBuffer -> framebuffer() ;
    Mind::Dimension2Di framebufferDimension(
        gFramebuffer -> width(),
        gFramebuffer -> height()
    ) ;

    bool windowSized = m_gBuffer -> windowSize() ;

    // This subtree renders the ambient occlusion into the dedicated
    // framebuffer.
    {
        m_subtree.aoRendering.ssaoApplier = new EffectApplierNode(
            &m_effectApplyData,
            this
        ) ;

        // Buffer in which AO is written with ambient occlusion.
        m_subtree.aoRendering.offscreen = new FramebufferRenderNode(
            framebufferDimension,
            windowSized,
            m_subtree.aoRendering.ssaoApplier
        ) ;
        // Try to use RED channel only.
        m_subtree.aoRendering.offscreen -> framebuffer() -> attachColor(
            AORenderTarget,
            API::InternalFormat::RedGreenBlueAlpha,
            API::PixelFormat::RedGreenBlueAlpha,
            API::PixelDataType::UnsignedInt
        ) ;
        m_subtree.aoRendering.offscreen -> framebuffer() -> setDrawBuffers({ AORenderTarget }) ;

        // Render pass selection.
        m_subtree.aoRendering.passSelector = new RenderPassSelectorNode(
            DeferredPassID,
            m_subtree.aoRendering.offscreen
        ) ;

        // Rendering of the ambient occlusion pass.
        m_subtree.aoRendering.deferredRendering = new OffscreenRenderingNode(
            std::make_unique<SSAOMaterialComponent>(m_gBuffer),
            m_subtree.aoRendering.passSelector
        ) ;
    }

    // In this subtree, the ambient occlusion is blurred in its final render
    // target.
    {
        // Buffer in which AO is written.
        m_subtree.aoBlurCopy.offscreen = new FramebufferRenderNode(
            framebufferDimension,
            windowSized,
            this
        ) ;
        m_subtree.aoBlurCopy.offscreen -> framebuffer() -> attachColor(
            AORenderTarget,
            m_output -> framebuffer() -> colorAttachment(AORenderTarget)
        ) ;
        m_subtree.aoBlurCopy.offscreen -> framebuffer() -> setDrawBuffers({ AORenderTarget }) ;

        // Render pass selection.
        m_subtree.aoBlurCopy.passSelector = new RenderPassSelectorNode(
            DeferredPassID,
            m_subtree.aoBlurCopy.offscreen
        ) ;

        // Rendering of the ambient occlusion pass.
        m_subtree.aoBlurCopy.deferredRendering = new OffscreenRenderingNode(
            std::make_unique<SSAOBlurMaterialComponent>(m_subtree.aoRendering.offscreen),
            m_subtree.aoBlurCopy.passSelector
        ) ;
    }
}
