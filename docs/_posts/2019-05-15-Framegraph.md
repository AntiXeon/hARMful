---
layout: post
author: Denis CARLUS
---

The frame graph is a key feature in the hARMful engine as it is used to describe how the render passes are performed. It is not bound to the scene graph but controls the scene graph rendering step in a convenient way. With the following explanations, you will be able to understand how much the frame graph is powerful.

## What is a frame graph?
The frame graph is intended to control how the scene will be displayed on screen. You control the render passes by using special nodes, the `FramegraphNodes`, that compose this graph. These `FramegraphNodes` are not related to the `Entities` of the scene graph as seen in the *Entity-Component-System* description.

So what kind of things can you do with the frame graph? For example, you can split the screen in a video game to give a specific point of view to 2 players.
Or, you can decide to render the scene into a texture and use it in another render pass as a reflection map.

Keep in mind that **the scene cannot be rendered without the frame graph**, and some nodes are mandatory for the rendering step.

## How does it work?
The creation of the frame graph is quite easy.

The scene has a frame graph root node. All your `FramegraphNodes` must be connected to this root, directly or not, so that there is a graph.

### Minimal frame graph
The minimal frame graph is composed of two nodes:
* `Viewport`: it defines the area inside the window that is used to display the scene. The position and the size defined into the `Viewport` are relative to the window size. So, if you want a `Viewport` using the half width of the window, enter a value of 0.5 for the width of the Viewport.
* `ActiveCamera`: it defines the camera to use to render the scene. Your scene can contain several cameras and you can switch the used camera through this `FramegraphNodes`. As the frame graph is dynamic, the system will apply the change directly on the next frame render.

```cpp
// Set the viewport using the whole window area.
Hope::Viewport* viewportNode = new Hope::Viewport() ;
viewportNode -> setPosition(Mind::Point2Df(0.f, 0.f)) ;
viewportNode -> setDimension(Mind::Dimension2Df(1.f, 1.f)) ;

// Set the camera to use.
Hope::ActiveCamera* activeCameraNode = new Hope::ActiveCamera(viewportNode) ;
activeCameraNode -> setCamera(myCameraComponent) ;

// Use the frame graph.
scene() -> setFrameGraphRoot(viewportNode) ;
```

### Going further
Many other nodes can be used to change the way the render is processed. You can inherit from the `FramegraphNode` class to create your own nodes and implement the methods from the `Visitor` pattern.

The `FramegraphNode` class is a concrete class and can be used as a root node for example. You can connect two `Viewport` objects to it, each `Viewport` having an `ActiveCamera` child node. This is how you can perform a splitscreen view for 2 players.

By connecting and modifying the `FramegraphNodes` while the application is running, you easily change how the scene is rendered with few manipulations.
