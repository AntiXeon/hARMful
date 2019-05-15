# Entity-Component-System
hARMful uses the ECS pattern to build a 3D scene. ECS uses composition instead of inheritance to bring a higher flexibility. For example, while the application is running and displays your 3D scene, you can replace a mesh by another one.
If you do not know what is ECS, here is a quick explanation.

## Scene graph
The scene is represented by a graph, called the scene graph. As it is a graph, there are nodes with a parenthood relation.

In hARMful, these nodes are called "Entities". An Entity bears a local transformation matrix for setting the position, rotation and scale of its content. But the content itself is not directly embedded in the Entity object.

Entities bear Components as well. Components can be many things in the scene: a mesh, a behavior, a functionality, etc. For example, you can find cameras, lights, control management or meshes as Components.

Finally, a System handles all of these Entities and their Components.

If you want to learn more about ECS, you can read this Wikipedia page: https://en.wikipedia.org/wiki/Entity_component_system

## Implementation in hARMful
In hARMful, an `Entity` inherits from a `Node` class that is only used for node relationships. The `Entity` class brings the support of Components and a local transformation to it. Thus, you do not directly use a Node in the scene graph even though you can use it for your application.

Components inherits from the base class `Component`. It handles base functions as the attachment to an `Entity` - and its detachment. A `Component` does not directly implement its behavior: it only contains the data that are required. As a result, a `Component` is not API-dependent. Instead, a `Visitor` pattern is used. A Component is visited by a `Visitor` that is specific to an API, for example OpenGL or Microsoft® DirectX®. If you want to add your own `Component` classes, you can inherit the implemented `Visitor` classes and add the functions to visit you new types of `Component` classes.

You do not interact with the System, not directly. You can change the scene graph during the execution of the application and the System adapts automatically the result on screen. It is highly dynamic as its parses the scene graph to extract a list of some components that need to be processed for the rendering of the scene. Thus, you can add or remove lights, change their properties, move meshes, without carring about what to do to notify the System about these changes.

## How to use it?
Here are some examples to show how the ECS works in hARMful.
Notice that the entities must be attached to the _scene root_ Entity, directly or not. Otherwise, it will be impossible to handle them in the System.

```cpp
// Create a camera in the scene graph.
Hope::Entity* cameraEntity = new Hope::Entity(parentEntity) ;
Hope::CameraComponent* cameraComponent = new Hope::PerspectiveCameraComponent() ;
cameraComponent -> setClearColor(Hope::Color(0x0A0A0AFF)) ;
cameraEntity -> addComponent(cameraComponent) ;
```
```cpp
// Add a point light to the scene.
Hope::Entity* pointLightEntity = new Hope::Entity(parentEntity) ;
Hope::PointLightComponent* pointLightComponent = new Hope::PointLightComponent() ;
pointLightComponent -> setColor(Hope::Color(0xC5D9FFFF)) ;
pointLightComponent -> setPower(1.5f) ;
pointLightComponent -> setSpecularGenerated(false) ;
pointLightComponent -> setQuadraticAttenuation(0.3f) ;
pointLightComponent -> setLinearAttenuation(0.7f) ;
pointLightEntity -> addComponent(pointLightComponent) ;
```
```cpp
// Load a mesh from a file (using ASSIMP).
Hope::Entity* meshTreeEntity = new Hope::Entity(parentEntity) ;
Hope::MeshTreeComponent* meshTreeComponent = new Hope::MeshTreeComponent("MyMesh.fbx") ;
meshTreeEntity -> addComponent(meshTreeComponent) ;
```
