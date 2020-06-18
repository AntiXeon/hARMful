#ifndef __HOPE__SCENE_TYPES__
#define __HOPE__SCENE_TYPES__

#include <cstdint>

namespace Hope {
    /**
     * ID for render passes.
     * An ID equal to 0 means the default render pass is to be used.
     */
    typedef unsigned int RenderPassID ;

    #define ForwardPassID           0       // Forward render pass ID.
    #define DeferredPassID          1       // Deferred render pass ID.
    #define DirectionalShadowPassID 2       // Shadow depth map pass ID (directional lights).

    typedef unsigned int EffectNodeType ;
    #define AmbientOcclusionEffectType  0
    #define ShadowsEffectType           1
    #define FogEffectType               2
    #define AmountEffectsTypes          (FogEffectType + 1)

    /**
     * ID for frames.
     */
    typedef unsigned int FrameID ;

    typedef unsigned int ComponentType ;

    #define MaterialComponentType           0
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
