#ifndef __HOPE__SCENE_TYPES__
#define __HOPE__SCENE_TYPES__

namespace Hope {
    typedef unsigned int FrameID ;

    typedef unsigned int ComponentType ;

    extern ComponentType MeshComponentType ;
    extern ComponentType CameraComponentType ;
    extern ComponentType RenderConfigurationType ;
    extern ComponentType LightComponentType ;
    extern ComponentType MaterialComponentType ;

    extern ComponentType TriangleTestType ;
    
    extern ComponentType LastComponentType ;

    extern unsigned int AmountComponentTypes ;
}

#endif
