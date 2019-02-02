#include <scene/SceneTypes.hpp>

namespace Hope {
    ComponentType MeshComponentType =               1 ;
    ComponentType CameraComponentType =             MeshComponentType + 1 ;
    ComponentType RenderConfigurationType =         CameraComponentType + 1 ;
    ComponentType LightType =                       RenderConfigurationType + 1 ;
}
