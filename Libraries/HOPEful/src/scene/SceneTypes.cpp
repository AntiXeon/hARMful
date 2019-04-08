#include <scene/SceneTypes.hpp>

namespace Hope {
    ComponentType MaterialComponentType =           0 ;
    ComponentType MeshComponentType =               MaterialComponentType + 1 ;
    ComponentType CameraComponentType =             MeshComponentType + 1 ;
    ComponentType RenderConfigurationType =         CameraComponentType + 1 ;
    ComponentType LightComponentType =              RenderConfigurationType + 1 ;

    ComponentType TriangleTestType = LightComponentType + 1 ;
    
    ComponentType LastComponentType = TriangleTestType ;

    unsigned int AmountComponentTypes = LastComponentType + 1 ;
}
