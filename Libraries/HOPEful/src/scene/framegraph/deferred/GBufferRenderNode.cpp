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
        API::Texture2D::PixelFormat::RedGreenBlueAlpha,
        API::Texture2D::PixelDataType::UnsignedByte
    ) ;

    framebuffer().attachColor(
       SpecularRenderTarget,
       API::Texture2D::PixelFormat::RedGreenBlueAlpha,
       API::Texture2D::PixelDataType::UnsignedByte
    ) ;

    framebuffer().attachColor(
       NormalRenderTarget,
       API::Texture2D::PixelFormat::RedGreenBlueAlpha,
       API::Texture2D::PixelDataType::UnsignedByte
   ) ;

   framebuffer().setDrawBuffers({
       AlbedoRenderTarget,
       SpecularRenderTarget,
       NormalRenderTarget
   }) ;

   framebuffer().attachDepth() ;
}
