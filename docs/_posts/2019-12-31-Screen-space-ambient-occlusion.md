---
layout: post
author: Denis CARLUS
---

Ambient occlusion is used to mimic the lack of light when two objects are close enough, as light particles are trapped and cannot escape tiny spaces.

The screen-space ambient occlusion (SSAO) is a quite cheap ambient occlusion technique for 3D realtime rendering. SSAO has been introduced by Crytek in their Crysis video game (2007). Since, more realistic techniques - but requiring more powerful hardware - have been developed.

![With/without SSAO](../../../assets/images/post_img/ssao_anim.gif)
_When SSAO is enabled, additional shadows are visible between close objects. Look at the ground below the cubes and the pipe on right._

As its name says, this post-production effect is based on what is rendered from the view space (camera) on offscreen buffers. It is thus available using deferred rendering. SSAO uses several informations rendered in the G-Buffer: position, normals and depth buffer[^1].

As a result, SSAO requires an access to the G-Buffer you have defined when setting up deferred rendering. You do not need more data to enable SSAO. Let's see how to use the `SSAORenderNode` in hARMful engine!

You have to plug the `SSAORenderNode` in the framegraph in a separated branch from `GBufferRenderNode` and `FinalStepRenderingNode`. As data must already be rendered into the GBuffer, be careful of plugging `SSAORenderNode` after `GBufferRenderNode`.

```cpp
// ....

/*
              +-- ActiveCamera --+-- G-Buffer
              |                  |
              |                  +-- SSAORender
              |
    root-- Viewport
              |
              +-- DeferredRendering
 */

Hope::ViewportNode* viewportNode = new Hope::ViewportNode(rootFG) ;

// G-Buffer branch of the framegraph.
activeCameraNode -> setParent(viewportNode) ;

Hope::GBufferRenderNode* gBufferNode = new Hope::GBufferRenderNode(
    Mind::Dimension2Di(800, 480),
    true,
    activeCameraNode
) ;
Hope::ClearBuffersNode* clearBuffers = new Hope::ClearBuffersNode(Hope::GL::BufferClearer::Buffer::ColorDepthStencil, gBufferNode) ;
new Hope::RenderPassSelectorNode(DeferredPassID, clearBuffers) ;

// ==> SSAO pass <==
new Hope::SSAORenderNode(gBufferNode, activeCameraNode) ;

// Deferred shading branch of the framegraph.
Hope::GBufferQuadMaterialComponent* drMaterial = new Hope::GBufferQuadMaterialComponent(gBufferNode) ;
new Hope::FinalStepRenderingNode(drMaterial, viewportNode) ;

// ....
```

That's all!

[^1]: Here is a technical discussion of what is internally done. hARMful computes the view space position from the depth buffer. So the only data from G-Buffer the are required to compute SSAO are normals and depth buffer. Additionaly, albedo is used as well in order to merge data of both albedo (on RGB channels) and ambient occlusion (on Alpha channel) into a single render target. This helps saving memory on GPU without any extra computational cost.
