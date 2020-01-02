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
        API::PixelFormat::RedGreenBlueAlpha,
        API::PixelDataType::UnsignedByte
    ) ;
    auto albedo = framebuffer() -> colorAttachment(AlbedoRenderTarget) ;
    albedo -> setFiltering(GL::FilterMode::Nearest, GL::FilterMode::Nearest) ;
    albedo -> setWrapModes({ GL::WrapMode::ClampToEdge, GL::WrapMode::ClampToEdge }) ;

    framebuffer() -> attachColor(
       SpecularRenderTarget,
       API::InternalFormat::RedGreenBlueAlpha,
       API::PixelFormat::RedGreenBlueAlpha,
       API::PixelDataType::UnsignedByte
    ) ;

    framebuffer() -> attachColor(
       NormalRenderTarget,
       API::InternalFormat::RedGreenBlueAlpha,
       API::PixelFormat::RedGreenBlueAlpha,
       API::PixelDataType::UnsignedByte
   ) ;
   auto normal = framebuffer() -> colorAttachment(NormalRenderTarget) ;
   normal -> setFiltering(GL::FilterMode::Nearest, GL::FilterMode::Nearest) ;
   normal -> setWrapModes({ GL::WrapMode::ClampToEdge, GL::WrapMode::ClampToEdge }) ;

   framebuffer() -> setDrawBuffers({
       AlbedoRenderTarget,
       SpecularRenderTarget,
       NormalRenderTarget
   }) ;

   framebuffer() -> attachDepth() ;
   auto depth = framebuffer() -> depthAttachment() ;
   depth -> setWrapModes({ GL::WrapMode::ClampToEdge, GL::WrapMode::ClampToEdge }) ;
}
