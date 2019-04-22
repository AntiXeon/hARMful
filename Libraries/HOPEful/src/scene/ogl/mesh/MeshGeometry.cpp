#include <scene/ogl/mesh/MeshGeometry.hpp>
#include <scene/ogl/mesh/Vertex.hpp>

using namespace Hope::GL ;

MeshGeometry::MeshGeometry() {
    glGenVertexArrays(1, &m_vertexArray) ;
}

void MeshGeometry::clearBuffers() {
    for (MeshPart& part : m_parts) {
        part.deleteBuffers() ;
    }

    glDeleteVertexArrays(1, &m_vertexArray) ;
}
