#ifndef __HOPE__SCENE_MESH_DATA__
#define __HOPE__SCENE_MESH_DATA__

#include <scene/ogl/mesh/MeshPart.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <map>
#include <vector>

namespace Hope {
    class MaterialComponent ;
    class MeshGeometryComponent ;
}

namespace Hope::GL {
    class FrameRenderSharedData ;

    /**
     * Elements of a mesh to draw using the same material.
     */
    struct MeshData {
        MeshGeometryComponent* mesh ;
        std::map<MaterialComponent*, std::vector<MeshPart>> parts ;

        Mind::Matrix4x4f worldTransformation ;
        FrameRenderSharedData* sharedData ;
    } ;
}

#endif
