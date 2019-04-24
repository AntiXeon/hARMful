#include <scene/ogl/mesh/MeshGeometry.hpp>
#include <scene/ogl/mesh/Vertex.hpp>

using namespace Hope::GL ;

MeshGeometry::MeshGeometry(const std::vector<float>& vertices) {
    glGenVertexArrays(1, &m_vertexArray) ;

    glGenBuffers(1, &m_vertexBuffer) ;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW) ;
}

void MeshGeometry::addPart(
    const uint32_t materialID,
    const std::vector<uint32_t>& indices
) {
    glBindVertexArray(m_vertexArray) ;
    m_parts.push_back(MeshPart(materialID, indices)) ;
    glBindVertexArray(0) ;
}

void MeshGeometry::clearBuffers() {
    for (MeshPart& part : m_parts) {
        part.deleteBuffers() ;
    }

    glDeleteBuffers(1, &m_vertexBuffer) ;
    glDeleteVertexArrays(1, &m_vertexArray) ;
}
