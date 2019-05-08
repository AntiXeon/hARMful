#ifndef __HOPE__SCENE_MESH_DATA__
#define __HOPE__SCENE_MESH_DATA__

#include <scene/ogl/mesh/GeometryPart.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <map>
#include <vector>

namespace Hope {
    class MaterialComponent ;
    class GeometryComponent ;
}

namespace Hope::GL {
    class FrameRenderSharedData ;

    /**
     * Elements of a mesh to draw using the same material.
     */
    struct GeometryData {
        GeometryComponent* mesh ;

        // Associate the material to the index of the part in the whole geometry.
        std::map<MaterialComponent*, std::vector<uint32_t>> parts ;

        Mind::Matrix4x4f worldTransformation ;
        FrameRenderSharedData* sharedData ;
    } ;
}

#endif
