---
layout: post
author: Denis CARLUS
---

Drawing shadows in a 3D scene is not that simple. A computer has no idea of what is a shadow and we have to explain how to render them. To make it simple, a shadow is when an object intercepts light before another one. That's what the technique to draw shadow tries to translate.

To do so, we have to make a render pass in which we get which objects are directly in front of a light - a directional light for **cascaded shadow mapping** (or CSM).
In a second render pass, we compare the result of the previous pass to what is finally rendered and draw shadows on objects that are not directly lit.

However, the first render pass has to be saved in memory to reuse it later on the lighting/rendering pass. We store the data in a texture.
It is a good thing for small rooms but what about a very large scenery? Do we have to store an extremely large picture to render the shadows of very far trees?
The answer is: no! To limit the footprint in memory even in the case of an open-world scene, we use _little_ textures. Indeed, the volume that includes all the rendered objects - also called camera frustum - is divided into smaller parts. Each part is named a _cascade_. For each cascade, a texture is used to render the directly lit objects from the light point of view. In general, the closest the cascade is, the smaller it is to have the better shadow resolution near the camera. Objects that are far away need a shadow map with lower details. This technique is called **cascaded shadow mapping**.

All of this sounds quite complicated... That's why hARMful makes it very simple to use in a scene, just for you!

More seriously, it is implemented through the framegraph once again. You will have to use the `DirectionalLightShadowNode` class to enable CSM in your scene. This node will generate a framegraph subtree with all the render passes to render the shadow maps. The shadow maps will automatically be used in the deferred rendering final pass to draw shadows.

Let's take a look at its constructor:
```cpp
DirectionalLightShadowNode(
    DirectionalLightComponent* light,
    ActiveCameraNode* renderingCamera,
    const uint32_t resolution,
    const float maxDistance = -1.f,
    const uint8_t amountCascades = 3,
    FrameGraphNode* parent = nullptr
) ;
```
* Of course, it takes the directional light used to render the shadows.
* The camera that is used for the final render is required as well. Indeed, we need its frustum to compute the shadow maps of each cascade.
* The resolution of the shadow map is mandatory as well. It is the size of a square texture in pixels. For example, set the resolution to 1024 so that all the cascade shadow maps are 1024x1024 textures.
* The maximal distance to render the shadows. By default, this value is set to -1 so that it uses the full render camera frustum. But you can decide to render shadows in a smaller volume to increase the shadow resolution while limitating the memory footprint.
* The amount of cascade is an interesting value. It is good to have enough cascades to have good visual results but be aware that each cascade requires a texture - think of memory footprint - and a render pass - think of performances issues.
* The parent of the node as for every framegraph node...

And now, an example to show how to integrate it in your framegraph:
```cpp
/** SCENE GRAPH **/
// Create a camera in the scene graph.
cameraEntity = new Hope::Entity(scene() -> root()) ;
cameraComponent = new Hope::PerspectiveCameraComponent() ;
cameraComponent -> setClearColor(Hope::Color(DefaultClearColor)) ;
cameraComponent -> setFarPlaneDistance(100.f) ;
cameraEntity -> addComponent(m_cameraComponent) ;
cameraComponent -> lookAt(Mind::Vector3f(0.f, 0.f, 0.f)) ;

// Create a directional light.
Hope::DirectionalLightComponent* dirLightComponent = nullptr ;
Hope::Entity* dirLightEntity = new Hope::Entity(scene() -> root()) ;
dirLightComponent = new Hope::DirectionalLightComponent() ;
dirLightComponent -> setDirection(Mind::Vector3f(0.3f, -0.5f, 0.5f)) ;
dirLightComponent -> setColor(Hope::Color(1.f, 1.f, 0.95f, 1.f)) ;
dirLightComponent -> setPower(1.f) ;
dirLightComponent -> setSpecularGenerated(true) ;
dirLightEntity -> addComponent(dirLightComponent) ;

// Continue the set up of the scene.
// ....


/** FRAME GRAPH **/   
Hope::ActiveCameraNode* activeCameraNode = new Hope::ActiveCameraNode() ;
activeCameraNode -> setCamera(cameraComponent) ;

/*
                  +-- ActiveCamera -- G-Buffer
                  |
    root-- +-- Viewport
           |      |
           |      +-- DeferredRendering
           |
           +-- DirectionalLightShadow
 */

Hope::FrameGraphNode* rootFG = new Hope::FrameGraphNode() ;

// -- Shadow mapping pass --
const uint32_t ShadowResolution = 1024 ;
const float MaxDistance = 75.f ;
const uint8_t AmountCascades = 3 ;
new Hope::DirectionalLightShadowNode(
    dirLightComponent,
    activeCameraNode,
    ShadowResolution,
    MaxDistance,
    AmountCascades,
    rootFG
) ;

// -- Rendering pass --
Hope::ViewportNode* viewportNode = new Hope::ViewportNode(rootFG) ;
viewportNode -> setPosition(Mind::Point2Df(0.f, 0.f)) ;
viewportNode -> setDimension(Mind::Dimension2Df(1.f, 1.f)) ;

// G-Buffer branch of the framegraph.
activeCameraNode -> setParent(viewportNode) ;
Hope::GBufferRenderNode* gBufferNode = new Hope::GBufferRenderNode(
    Mind::Dimension2Di(800, 480),
    true,
    activeCameraNode
) ;
Hope::ClearBuffersNode* clearBuffers = new Hope::ClearBuffersNode(Hope::GL::BufferClearer::Buffer::ColorDepthStencil, gBufferNode) ;
new Hope::RenderPassSelectorNode(DeferredPassID, clearBuffers) ;

// Deferred shading branch of the framegraph.
Hope::GBufferQuadMaterialComponent* drMaterial = new Hope::GBufferQuadMaterialComponent(gBufferNode) ;
new Hope::DeferredRenderingNode(drMaterial, viewportNode) ;

// Use the frame graph.
scene() -> setFrameGraphRoot(rootFG) ;
```
