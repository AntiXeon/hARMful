#include <scene/components/mesh/MeshGeometryComponent.hpp>

using namespace Hope ;

MeshGeometryComponent::MeshGeometryComponent(API::MeshGeometry* geometry)
    : Component(ClassType),
      m_geometry(geometry) {}

MeshGeometryComponent::~MeshGeometryComponent() {
    m_geometry -> clearBuffers() ;
    delete m_geometry ;
}
