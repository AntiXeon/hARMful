#include <scene/framegraph/deferred/GBufferRenderNode.hpp>

using namespace Hope ;

GBufferRenderNode::GBufferRenderNode(
    const Mind::Dimension2Di& size,
    const bool windowSize,
    FrameGraphNode* parent
) : FramebufferRenderNode(size, windowSize, parent) {
    setup() ;
}

void GBufferRenderNode::setup() {
    framebuffer() -> attachColor(
        AlbedoRenderTarget,
        API::InternalFormat::RedGreenBlueAlpha,
        API::PixelFormat::RedGreenBlueAlpha,    // useless for MSAA
        API::PixelDataType::UnsignedByte        // useless for MSAA
    ) ;

    framebuffer() -> attachColor(
       SpecularRenderTarget,
       API::InternalFormat::RedGreenBlueAlpha,
       API::PixelFormat::RedGreenBlueAlpha,    // useless for MSAA
       API::PixelDataType::UnsignedByte        // useless for MSAA
    ) ;

    framebuffer() -> attachColor(
       NormalRenderTarget,
       API::InternalFormat::RedGreenBlueAlpha,
       API::PixelFormat::RedGreenBlueAlpha,    // useless for MSAA
       API::PixelDataType::UnsignedByte        // useless for MSAA
   ) ;

   framebuffer() -> setDrawBuffers({
       AlbedoRenderTarget,
       SpecularRenderTarget,
       NormalRenderTarget
   }) ;

   framebuffer() -> attachDepth() ;
}
