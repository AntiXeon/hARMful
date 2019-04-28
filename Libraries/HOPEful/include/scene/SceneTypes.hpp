#ifndef __HOPE__SCENE_TYPES__
#define __HOPE__SCENE_TYPES__

namespace Hope {
    typedef unsigned int FrameID ;

    typedef unsigned int ComponentType ;

    #define MaterialComponentType       0
    #define MeshTreeComponentType       (MaterialComponentType + 1)
    #define MeshGeometryComponentType   (MeshTreeComponentType + 1)
    #define CameraComponentType         (MeshGeometryComponentType + 1)
    #define RenderConfigurationType     (CameraComponentType + 1)
    #define LightComponentType          (RenderConfigurationType + 1)

    #define TriangleTestType            (LightComponentType + 1)

    #define LastComponentType           (TriangleTestType)

    #define AmountComponentTypes        (LastComponentType + 1)

    // extern constexpr ComponentType MaterialComponentType ;
    // extern constexpr ComponentType MeshTreeComponentType ;
    // extern constexpr ComponentType MeshGeometryComponentType ;
    // extern constexpr ComponentType CameraComponentType ;
    // extern constexpr ComponentType RenderConfigurationType ;
    // extern constexpr ComponentType LightComponentType ;
    //
    // extern constexpr ComponentType TriangleTestType ;
    //
    // extern constexpr ComponentType LastComponentType ;
    //
    // extern constexpr unsigned int AmountComponentTypes ;
}

#endif
