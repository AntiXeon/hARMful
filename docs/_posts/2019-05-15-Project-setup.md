---
layout: post
author: Denis CARLUS
---

This article is dedicated to the setup of an application using the hARMful engine from scratch. As you can see, the setup is very fast and easy.

## Main window
The entry point of the hARMful engine is the `Window` class.

If you want to add logics to your application - what is often the case - you will have to inherit from the base `Window` implementation according to the graphics API you want to use. Indeed, the `Window` base class provides two virtual methods that are empty: *pre-render* and *post-render* actions. You can do what you want in these two methods to update your 3D scene. You can implement only one of them if you do not use the other one.

```cpp
class MyWindow final : public Hope::GL::Window {
    protected:
        // Allows the user to perform custom actions before rendering the frame.
        void preRender() override {
            // Implement with logics, physics, etc.
            // Not mandatory.
        }

        // Allows the user to perform custom actions after rendering the frame.
        void postRender() override {
            // Implement with logics, physics, etc.
            // Not mandatory.
        }
} ;
```

### Accessing the scene
The `Window` class gives you access to the scene throught the `scene()` method. It is a public method so that you can get it from outside the `Window` class if it is better for your application architecture.

From the scene, you can then set up the *Framegraph* through the `Scene::setFrameGraphRoot(rootNode)` method.

You can create your scene graph as well by getting the scene root node with the `Scene::root()` method.

```cpp
MyWindow mainWindow ;
Hope::Scene* scene = mainWindow.scene() ;

// Stuff on viewport and framegraph...
Hope::ViewportNode* viewportNode = new Hope::ViewportNode() ;
// ...
scene -> setFrameGraphRoot(viewportNode) ;

// Stuff on scene graph...
Hope::Entity* cameraEntity = new Hope::Entity(scene -> root()) ;
Hope::CameraComponent* cameraComponent = new Hope::PerspectiveCameraComponent() ;
cameraEntity -> addComponent(cameraComponent) ;
// ...
```

## Run the application
To run the application, use the following minimal code:
```cpp
#include "MyWindow.hpp"
#include <cstdlib>

int main(int, char**) {
    MyWindow mainWindow ;
    mainWindow.run() ;

    return EXIT_SUCCESS ;
}
```
