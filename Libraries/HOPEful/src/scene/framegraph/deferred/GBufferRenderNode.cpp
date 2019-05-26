#include <scene/framegraph/deferred/GBufferRenderNode.hpp>

using namespace Hope ;

GBufferRenderNode::GBufferRenderNode(
    const Mind::Dimension2Di& size,
    const bool windowSize,
    FrameGraphNode* parent
) : OffScreenRenderNode(size, windowSize, parent) {
    setup() ;
}

void GBufferRenderNode::setup() {
    framebuffer().attachColor(
        AlbedoRenderTarget,
        API::InternalFormat::RedGreenBlueAlpha,
        API::PixelFormat::RedGreenBlueAlpha,
        API::PixelDataType::UnsignedByte
    ) ;

    framebuffer().attachColor(
       SpecularRenderTarget,
       API::InternalFormat::RedGreenBlueAlpha,
       API::PixelFormat::RedGreenBlueAlpha,
       API::PixelDataType::UnsignedByte
    ) ;

    framebuffer().attachColor(
       NormalRenderTarget,
       API::InternalFormat::RedGreenBlueAlpha16f,
       API::PixelFormat::RedGreenBlueAlpha,
       API::PixelDataType::HalfFloat
   ) ;

   framebuffer().setDrawBuffers({
       AlbedoRenderTarget,
       SpecularRenderTarget,
       NormalRenderTarget
   }) ;

   framebuffer().attachDepth() ;
}
