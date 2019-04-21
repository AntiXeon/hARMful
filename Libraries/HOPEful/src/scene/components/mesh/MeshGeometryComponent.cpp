#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>

using namespace Hope ;

MeshGeometryComponent::MeshGeometryComponent(
    const std::vector<float>& vertices,
    const std::vector<uint32_t>& indices
) : Component(Hope::MeshGeometryComponentType) {
    m_geometry = API::MeshGeometry(vertices, indices) ;
}

MeshGeometryComponent::MeshGeometryComponent(const API::MeshGeometry& geometry)
    : Component(Hope::MeshGeometryComponentType),
      m_geometry(geometry) {}

void MeshGeometryComponent::accept(ISceneGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
