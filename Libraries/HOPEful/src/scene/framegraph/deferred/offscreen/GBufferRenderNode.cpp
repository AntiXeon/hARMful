#include <scene/framegraph/deferred/offscreen/GBufferRenderNode.hpp>

using namespace Hope ;

GBufferRenderNode::GBufferRenderNode(
    const Mind::Dimension2Di& size,
    FrameGraphNode* parent
) : FramebufferRenderNode(size, FollowWindowSize, parent) {
    setup() ;
}

void GBufferRenderNode::setup() {
    framebuffer() -> attachColor(
        AlbedoMetalnessRenderTarget,
        API::InternalFormat::RedGreenBlueAlpha16f,
        API::PixelFormat::RedGreenBlueAlpha,
        API::PixelDataType::HalfFloat
    ) ;

    framebuffer() -> attachColor(
       EmissiveRoughnessRenderTarget,
       API::InternalFormat::RedGreenBlueAlpha16f,
       API::PixelFormat::RedGreenBlueAlpha,
       API::PixelDataType::HalfFloat
    ) ;

    framebuffer() -> attachColor(
       AORenderTarget,
       API::InternalFormat::RedGreenBlueAlpha16f,
       API::PixelFormat::RedGreenBlueAlpha,
       API::PixelDataType::HalfFloat
   ) ;

   framebuffer() -> attachColor(
	  NormalRenderTarget,
	  API::InternalFormat::RedGreenBlueAlpha16f,
	  API::PixelFormat::RedGreenBlueAlpha,
	  API::PixelDataType::HalfFloat
  ) ;

   framebuffer() -> setDrawBuffers({
       AlbedoMetalnessRenderTarget,
       EmissiveRoughnessRenderTarget,
       AORenderTarget,
	   NormalRenderTarget
   }) ;

   framebuffer() -> attachDepth() ;
}
