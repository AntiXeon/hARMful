#include <scene/SceneTypes.hpp>

namespace Hope {
    ComponentType MeshComponentType =               1 ;
    ComponentType CameraComponentType =             MeshComponentType + 1 ;
    ComponentType RenderConfigurationType =         CameraComponentType + 1 ;
    ComponentType LightComponentType =              RenderConfigurationType + 1 ;
    ComponentType MaterialComponentType =           LightComponentType + 1 ;
}
