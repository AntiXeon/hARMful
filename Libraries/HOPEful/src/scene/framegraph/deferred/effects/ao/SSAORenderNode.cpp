#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <scene/framegraph/ClearBuffersNode.hpp>
#include <scene/framegraph/MemoryBarrierNode.hpp>
#include <scene/framegraph/deferred/DeferredRenderingNode.hpp>
#include <scene/components/materials/deferred/SSAOMaterialComponent.hpp>
#include <scene/components/materials/deferred/SSAOBlurMaterialComponent.hpp>
#include <scene/SceneTypes.hpp>
#include <utils/Random.hpp>

using namespace Hope ;

SSAORenderNode::SSAORenderNode(
    GBufferRenderNode* gBuffer,
    FrameGraphNode* parent
) : EffectFrameGraphNode(parent),
    m_gBuffer(gBuffer) {
    generateNoiseTexture() ;
    generateKernel() ;
    generateFramegraphSubtree() ;
}

SSAORenderNode::~SSAORenderNode() {
    delete m_noiseTexture ;
    delete m_ssaoMaterial ;
}

void SSAORenderNode::generateNoiseTexture() {
    std::array<float, NoiseTextureDataSize> noiseData ;

    for (int index = 0 ; index < NoiseTextureDataSize ; index += Mind::Vector3f::AmountCoords) {
        noiseData[index] = Doom::Random::GetNormalizedFloat() * 2.f - 1.f ;       // X
        noiseData[index + 1] = Doom::Random::GetNormalizedFloat() * 2.f - 1.f ;   // Y
        noiseData[index + 2] = Doom::Random::GetNormalizedFloat() ;               // Z
    }

    const static bool GenerateMipmap = false ;
    m_noiseTexture = new API::TextureImage2D(
        Mind::Dimension2Di(NoiseTextureSideSize, NoiseTextureSideSize),
        API::InternalFormat::RedGreenBlue16f,
        API::PixelFormat::RedGreenBlue,
        API::PixelDataType::Float,
        noiseData.data(),
        GenerateMipmap
    ) ;

    m_noiseTexture -> setWrapModes({ API::WrapMode::Repeat, API::WrapMode::Repeat }) ;
}

void SSAORenderNode::generateKernel() {
    const float DefaultScale = 1.f / static_cast<float>(AO_KERNEL_SIZE) ;

    for (int kernelIndex = 0 ; kernelIndex < AO_KERNEL_SIZE ; ++kernelIndex) {
        // Generate the sample.
        Mind::Vector3f sample(
            Doom::Random::GetNormalizedFloat() * 2.f - 1.f,
            Doom::Random::GetNormalizedFloat() * 2.f - 1.f,
            Doom::Random::GetNormalizedFloat()
        ) ;

        sample.normalize() ;
        sample *= Doom::Random::GetNormalizedFloat() ;

        // Aggregate most of the samples close to the origin of the hemisphere.
        // lerp
        const float LerpFrom = 0.1f ;
        const float LerpTo = 1.f ;
        float lerpScale = LerpFrom + (DefaultScale * DefaultScale) * (LerpTo - LerpFrom) ;
        sample *= lerpScale ;

        // Store the sample.
        m_kernel[kernelIndex] = sample ;
    }
}

void SSAORenderNode::generateFramegraphSubtree() {
    const Mind::Dimension2Di& dimension = m_gBuffer -> framebuffer() -> size() ;
    bool windowSized = m_gBuffer -> windowSize() ;

    // This subtree renders the ambient occlusion into the dedicated
    // framebuffer.
    {
        // Buffer in which AO is written with albedo.
        m_subtree.aoRendering.offscreen = new FramebufferRenderNode(
            dimension,
            windowSized,
            this
        ) ;
        m_subtree.aoRendering.offscreen -> framebuffer() -> attachColor(
            AlbedoRenderTarget,
            API::InternalFormat::RedGreenBlueAlpha,
            API::PixelFormat::RedGreenBlueAlpha,
            API::PixelDataType::UnsignedByte
        ) ;
        m_subtree.aoRendering.offscreen -> framebuffer() -> setDrawBuffers({ AlbedoRenderTarget }) ;

        // Render pass selection.
        m_subtree.aoRendering.passSelector = new RenderPassSelectorNode(
            ForwardPassID,
            m_subtree.aoRendering.offscreen
        ) ;

        // Rendering of the ambient occlusion pass.
        m_ssaoMaterial = new SSAOMaterialComponent(m_gBuffer) ;
        m_subtree.aoRendering.deferredRendering = new DeferredRenderingNode(
            m_ssaoMaterial,
            m_subtree.aoRendering.passSelector
        ) ;
    }

    // In this subtree, the ambient occlusion is copied into the G-Buffer as the
    // alpha channel of the albedo target. It is blurred at the same time.
    {
        // Buffer in which AO is written with albedo.
        m_subtree.aoBlurCopy.offscreen = new FramebufferRenderNode(
            m_gBuffer,
            this
        ) ;

        // Render pass selection.
        m_subtree.aoBlurCopy.passSelector = new RenderPassSelectorNode(
            ForwardPassID,
            m_subtree.aoBlurCopy.offscreen
        ) ;

        // Rendering of the ambient occlusion pass.
        m_ssaoBlurMaterial = new SSAOBlurMaterialComponent(
            m_subtree.aoRendering.offscreen,
            m_gBuffer
        ) ;
        m_subtree.aoBlurCopy.deferredRendering = new DeferredRenderingNode(
            m_ssaoBlurMaterial,
            m_subtree.aoBlurCopy.passSelector
        ) ;
    }
}
