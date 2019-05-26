---
layout: post
author: Denis CARLUS
---

Deferred rendering is a technique for rendering scenes with a lot a lights. Indeed, even if forward rendering is easy to use, it is not efficient when a lot of lights are in the scene. There are several reasons for this:
- each object that is rendered is computed over each light in the scene;
- each object is fully rendered even if it is partially or totally occluded by another object, in front of it;
- the rendering is done by object, what can be a huge task to be completed in limited time when their are a lot of objects and lights.

Deferred rendering tries to solve these issues. First of all, it renders different simple properties of the objects as their color or their normal map with few and very fast calculations. Secondly, the shading part is made later when all the properties of the rendered objects are stored - in textures - and applied on a fullscreen polygon. As a result, the shading is only performed on the visible parts of the objects in the scene only. Finally, shading is only performed on a picture that has the size of the wanted resolution, so that computing light contributions is faster.

However, each property is stored in a picture of the size for the final shading. That means deferred rendering uses a lot of VRAM.
Other techniques exist, even if none of them is perfect as Forward+ rendering. Great engines combines these techniques to improve performances.

This is a quick explanation of what is deferred rendering but you can find much more complete documentation on how it works _behind-the-scene_ on internet.

## How to use it?
In hARMful, deferred rendering is abstracted and ask very few work for you to set it up!

Everything is done in the framegraph, and your scene graph stays as it is for a common forward rendering.
You have to be careful when setting the framegraph. The order of the nodes is very important here as the `GBufferRenderNode` **must** be before any `GBufferRenderNode`.

```cpp
/** FRAME GRAPH **/

/*
               +-- ActiveCamera -- G-Buffer -- Clear buffers -- Deferred pass
               |
    Viewport-- +
               |
               +-- DeferredRendering
 */

Hope::ViewportNode* viewportNode = new Hope::ViewportNode() ;
viewportNode -> setPosition(Mind::Point2Df(0.f, 0.f)) ;
viewportNode -> setDimension(Mind::Dimension2Df(1.f, 1.f)) ;

// G-Buffer branch of the framegraph.
Hope::ActiveCameraNode* activeCameraNode = new Hope::ActiveCameraNode(viewportNode) ;
activeCameraNode -> setCamera(m_cameraComponent) ;
Hope::GBufferRenderNode* gBufferNode = new Hope::GBufferRenderNode(
    Mind::Dimension2Di(800, 480),
    true,
    activeCameraNode
) ;
Hope::ClearBuffersNode* clearBuffers = new Hope::ClearBuffersNode(Hope::GL::BufferClearer::Buffer::ColorDepth, gBufferNode) ;
new Hope::RenderPassSelectorNode(DeferredPassID, clearBuffers) ;


// Deferred shading branch of the framegraph.
Hope::GBufferQuadMaterialComponent* drMaterial = new Hope::GBufferQuadMaterialComponent(gBufferNode) ;
new Hope::DeferredRenderingNode(drMaterial, viewportNode) ;

// Use the frame graph.
scene() -> setFrameGraphRoot(viewportNode) ;
```

## How to create materials that use deferred rendering?
The first things to create are the shaders. You need at least a duet of vertex/fragment shaders for both modes: forward rendering and deferred rendering.
Notice that the deferred rendering works with view-space values (normals, lights positions).
That's why there is no G-Buffer dedicated to world position of the scene objects. Their view-space position is retrieved from the depth buffer.
The C++ code and the shaders utility functions are common to both forward and deferred rendering by the way.

A fragment dedicated to deferred rendering must output four values with the given locations:
```glsl
layout(location = 0) out vec4 gAlbedo ;
layout(location = 1) out vec4 gNormal ;
layout(location = 2) out vec4 gSpecular ;
```

Once its done, you have to create the corresponding `MaterialComponent`. You should implement the `setupForwardShader()` method and of course the `setupDeferredShader()` method, using the right render pass IDs. Then you set up the uniforms as usually, the code is common to both rendering modes.
