#include <scene/ogl/mesh/MeshGeometry.hpp>
#include <scene/ogl/mesh/Vertex.hpp>

using namespace Hope::GL ;

MeshGeometry::MeshGeometry(const std::vector<float>& vertices) {
    glGenVertexArrays(1, &m_vertexArray) ;

    glGenBuffers(1, &m_vertexBuffer) ;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW) ;

    glBindVertexArray(m_vertexArray) ;
    unsigned char offset = 0 ;
    // Position attribute.
    glEnableVertexAttribArray(0) ;
    glVertexAttribPointer(0, Vertex::PositionLength, GL_FLOAT, GL_FALSE, Vertex::TotalLength * sizeof(float), reinterpret_cast<void*>(offset)) ;
    offset += (Vertex::PositionLength * sizeof(float)) ;

    // Normal attribute.
    glEnableVertexAttribArray(1) ;
    glVertexAttribPointer(1, Vertex::TexCoordLength, GL_FLOAT, GL_FALSE, Vertex::TotalLength * sizeof(float), reinterpret_cast<void*>(offset)) ;
    offset += (Vertex::TexCoordLength * sizeof(float)) ;

    // Texture coordinates attribute.
    glEnableVertexAttribArray(2) ;
    glVertexAttribPointer(2, Vertex::NormalLength, GL_FLOAT, GL_FALSE, Vertex::TotalLength * sizeof(float), reinterpret_cast<void*>(offset)) ;

    glGenBuffers(1, &m_indexBuffer) ;
    glBindVertexArray(0) ;
}

void MeshGeometry::addPart(
    const uint32_t materialID,
    const std::vector<uint32_t>& indices
) {
    uint32_t offset = m_indices.size() ;
    m_parts.push_back(
        MeshPart(
            materialID,
            offset,
            indices.size()
        )
    ) ;

    m_indices.reserve(m_indices.size() + indices.size()) ;
    m_indices.insert(m_indices.end(), indices.begin(), indices.end()) ;
}

void MeshGeometry::completed() {
    glBindVertexArray(m_vertexArray) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * amountIndices(), m_indices.data(), GL_STATIC_DRAW) ;
    glBindVertexArray(0) ;
}

void MeshGeometry::clearBuffers() {
    if (glIsBuffer(m_indexBuffer)) {
        glDeleteBuffers(1, &m_indexBuffer) ;
    }

    glDeleteBuffers(1, &m_vertexBuffer) ;
    glDeleteVertexArrays(1, &m_vertexArray) ;
}
