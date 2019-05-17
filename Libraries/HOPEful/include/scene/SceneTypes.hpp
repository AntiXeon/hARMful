#ifndef __HOPE__SCENE_TYPES__
#define __HOPE__SCENE_TYPES__

namespace Hope {
    /**
     * ID for render passes.
     * An ID equal to 0 means the default render pass is to be used.
     */
    typedef unsigned int RenderPassID ;

    #define ForwardPassID   0       // Default render pass ID.
    #define AlbedoPassID    1       // ID for a albedo (diffuse) render pass (deferred rendering).
    #define NormalPassID    2       // ID for a normal render pass (deferred rendering).
    #define SpecularPassID  3       // ID for a specular render pass (deferred rendering).
    #define PositionPassID  4       // ID for a position render pass (deferred rendering).
    #define TexCoordPassID  5       // ID for a texture coordinates render pass (deferred rendering).


    /**
     * ID for frames.
     */
    typedef unsigned int FrameID ;

    typedef unsigned int ComponentType ;

    #define MaterialComponentType       0
    #define MeshTreeComponentType           (MaterialComponentType + 1)
    #define GeometryComponentType           (MeshTreeComponentType + 1)
    #define CameraComponentType             (GeometryComponentType + 1)
    #define RenderConfigurationType         (CameraComponentType + 1)
    #define LightComponentType              (RenderConfigurationType + 1)

    #define TriangleTestType                (LightComponentType + 1)

    #define LastComponentType               (TriangleTestType)

    #define AmountComponentTypes            (LastComponentType + 1)
}

#endif
