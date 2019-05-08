#ifndef __HOPE__SCENE_TYPES__
#define __HOPE__SCENE_TYPES__

namespace Hope {
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
