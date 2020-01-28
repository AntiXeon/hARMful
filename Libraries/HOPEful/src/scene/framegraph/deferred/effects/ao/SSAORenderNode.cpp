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
    FrameGraphNode* parent
) : EffectFrameGraphNode(parent),
    m_gBuffer(gBuffer) {
    Doom::Random::Initialize() ;
    generateNoiseTexture() ;
    generateKernel() ;
    generateFramegraphSubtree() ;

    m_effectApplyData.setSSAO(this) ;
}

SSAORenderNode::~SSAORenderNode() {
    delete m_ssaoMaterial ;
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
    const Mind::Dimension2Di FramebufferDimension(
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
        m_subtree.aoRendering.offscreen = new FramebufferMultisampleRenderNode(
            FramebufferDimension,
            windowSized,
            m_subtree.aoRendering.ssaoApplier
        ) ;
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
        m_ssaoMaterial = new SSAOMaterialComponent(m_gBuffer) ;
        m_subtree.aoRendering.deferredRendering = new OffscreenRenderingNode(
            m_ssaoMaterial,
            m_subtree.aoRendering.passSelector
        ) ;
    }

    // In this subtree, the ambient occlusion is copied into the G-Buffer as the
    // alpha channel of the albedo target. It is blurred at the same time.
    {
        // Buffer in which AO is written with albedo.
        m_subtree.aoBlurCopy.offscreen = new FramebufferMultisampleRenderNode(
            FramebufferDimension,
            windowSized,
            this
        ) ;
        m_subtree.aoBlurCopy.offscreen -> framebuffer() -> attachColor(
            GBufferRenderNode::AlbedoRenderTarget,
            m_gBuffer -> framebuffer() -> colorAttachment(GBufferRenderNode::AlbedoRenderTarget)
        ) ;

        // Render pass selection.
        m_subtree.aoBlurCopy.passSelector = new RenderPassSelectorNode(
            DeferredPassID,
            m_subtree.aoBlurCopy.offscreen
        ) ;

        // Rendering of the ambient occlusion pass.
        m_ssaoBlurMaterial = new SSAOBlurMaterialComponent(m_subtree.aoRendering.offscreen) ;
        m_subtree.aoBlurCopy.deferredRendering = new OffscreenRenderingNode(
            m_ssaoBlurMaterial,
            m_subtree.aoBlurCopy.passSelector
        ) ;
    }
}
