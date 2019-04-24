#include <scene/components/mesh/MeshGeometryComponent.hpp>
#include <interfaces/visitors/scenegraph/ISceneGraphVisitor.hpp>

using namespace Hope ;

MeshGeometryComponent::MeshGeometryComponent(API::MeshGeometry* geometry)
    : Component(Hope::MeshGeometryComponentType),
      m_geometry(geometry) {}

void MeshGeometryComponent::accept(ISceneGraphVisitor* visitor) {
    visitor -> visit(this) ;
}

MeshGeometryComponent::~MeshGeometryComponent() {
    m_geometry -> clearBuffers() ;
    delete m_geometry ;
}
