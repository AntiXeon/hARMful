---
title: hARMful
layout: default
---

**hARMful** is a project aimed at making a whole experience for programming video games and interactive 2D/3D applications.

![hARMful screenshot](./assets/images/hARMful.jpg)
[Fullscreen](./assets/images/hARMful_big.jpg)

hARMful is a young project, leaded by a single developer. It evolves slowly but many features are expected.
Some of them are already implemented and a demonstration video is available. A "✗" symbol indicates that the feature is not yet implemented; a "✓" symbol is used to signal non-graphic features that are implemented.

## Features
### Features of HOPEful
- Architecture based on the [Entity-Component-System pattern](https://en.wikipedia.org/wiki/Entity_component_system)
- Rendering process based on a [framegraph](https://www.ea.com/frostbite/news/framegraph-extensible-rendering-architecture-in-frostbite) to handle render passes
    - Render to several viewports [[Demo](https://www.youtube.com/watch?v=ElPDwyt3TtE)]
- Blinn-Phong material [[Demo](https://www.youtube.com/watch?v=WdcBg3hA-xQ)]
- Diffuse, normal and specular maps material [[Demo](https://www.youtube.com/watch?v=KRRrB-G3OOY)]
- Alpha channel supporting materials (✗)
- Order-independent transparency (✗)
- Physics based rendering materials (✗)
- Cascade shadow mapping [[Demo](https://www.youtube.com/watch?v=8Q3Ci3c_1Pg)]
- Render passes management [[Demo](https://www.youtube.com/watch?v=_oQXAGGpcu8)]
- Support of deferred rendering (✓)
    - Compute scene objects position from depth (✓)
    - Compute normals in a spheremap transform (✓)
- Post-rendering effects:
    - Anti-aliasing (✗)
    - Screen-Space Ambient Occlusion [[Demo](https://www.youtube.com/watch?v=kyHOFL1iB9c)]
    - Ground-Truth Ambient Occlusion (✗)
    - Bloom (✗)
    - Depth of Field (✗)
    - Many others...
- Uniform Buffer Objects (✓)
- Mesh import using ASSIMP (✓)
- Mesh instancing (✗)
- Frustum culling (✗)
- Quadtree (✗)
- Animations (✗)
- Cube maps (✓)
- Input management (keyboard, mouse, joypad) (✗)
- Scripting (✗)
- [Bullet physics engine](https://github.com/bulletphysics/bullet3) integration (✗)

### Features of MINDful
- SIMD implementations:
    - SSE (Intel/AMD) (✓)
    - NEON (ARM) (✗)
- Vectors 2D, 3D and 4D with common operations (✓)
- Quaternions with common operations (✓)
- Matrices 3x3 and 4x4 with common operations for 3D graphics applications (✓)

### Features of SPITEful
- Load text files (✓)
- Load binary files (✓)
- Load images:
    - PNG (✓)
    - JPEG (✓)
    - TGA (✗)
    - DDS (✗)

### Features of HOPEful
- Log system (✓)
- Profiling tool (✓)
- Translation abstraction tool:
    - Linux (✓)
    - Windows (✗)
- Random numbers (integer, floats) generation (✓)

## Roadmap
A version development lasts around 18 months (except the Puppy version, for which low-level tools have been developped as well).

### Version 1.0 (Puppy)
The first version of hARMful is waited for mid-2020. It is not yet well evolved and it still is a "baby" engine.
* Support of GNU/Linux (only)
* Intel SSE support for mathematics
* Image loader (JPEG/PNG)
* Support of OpenGL 4.5 (only) with basic 3D features:
    - Mesh importer
    - Hard shadows
    - Transparent objects rendering
    - Cubemaps
    - Reflections / refractions of cubemap
    - Screen-space ambient occlusion

### Version 1.1 (Poodle)
This version brings user interactions and physics engine. That reminds the pompom of a poodle one can love to touch!
* Animated meshes
* Image saver (JPEG/PNG)
* Integration of Bullet physics engine
* User interactions (keyboard, mouse, controllers)
* Increase of performances (instancing, octrees, multithreading)

### Version 1.2 (Malteser)
Mainly oriented towards an improvements of the rendering, as a Maltese dog with hair styled.
* Physics-based rendering materials
* Ground-truth ambient occlusion
* Soft shadows
* Global illumination
* Support of sounds and musics (OGG)
* Support of Microsoft Windows

### Version 1.3 (Shiba-inu)
Support of modern ARM processors (CPU and GPU).
* Support of NEON
* Support of Vulkan API
* Scripting language
