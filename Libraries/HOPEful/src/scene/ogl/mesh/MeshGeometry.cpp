#include <scene/ogl/mesh/MeshGeometry.hpp>
#include <scene/ogl/mesh/Vertex.hpp>

using namespace Hope::GL ;

MeshGeometry::MeshGeometry(const std::vector<float>& vertices)
    : Geometry() {
    static const size_t VertexByteSize = Vertex::TotalLength * sizeof(float) ;

    glGenVertexArrays(1, &m_vertexArray) ;

    glGenBuffers(1, &m_vertexBuffer) ;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW) ;

    glBindVertexArray(m_vertexArray) ;
    unsigned char offset = 0 ;
    // Position attribute.
    glEnableVertexAttribArray(0) ;
    glVertexAttribPointer(0, Vertex::PositionLength, GL_FLOAT, GL_FALSE, VertexByteSize, reinterpret_cast<void*>(offset)) ;
    offset += (Vertex::PositionLength * sizeof(float)) ;

    // Texture coordinates attribute.
    glEnableVertexAttribArray(1) ;
    glVertexAttribPointer(1, Vertex::TexCoordLength, GL_FLOAT, GL_FALSE, VertexByteSize, reinterpret_cast<void*>(offset)) ;
    offset += (Vertex::TexCoordLength * sizeof(float)) ;

    // Normal attribute.
    glEnableVertexAttribArray(2) ;
    glVertexAttribPointer(2, Vertex::NormalLength, GL_FLOAT, GL_FALSE, VertexByteSize, reinterpret_cast<void*>(offset)) ;
    offset += (Vertex::NormalLength * sizeof(float)) ;

    // Tangent vector attribute.
    glEnableVertexAttribArray(3) ;
    glVertexAttribPointer(3, Vertex::TangentLength, GL_FLOAT, GL_FALSE, VertexByteSize, reinterpret_cast<void*>(offset)) ;
    offset += (Vertex::TangentLength * sizeof(float)) ;

    // Bitangent vector attribute.
    glEnableVertexAttribArray(4) ;
    glVertexAttribPointer(4, Vertex::BitangentLength, GL_FLOAT, GL_FALSE, VertexByteSize, reinterpret_cast<void*>(offset)) ;

    glGenBuffers(1, &m_indexBuffer) ;
    glBindVertexArray(0) ;
}

void MeshGeometry::addPart(
    const uint32_t materialID,
    const std::vector<uint32_t>& indices
) {
    uint32_t offset = static_cast<uint32_t>(m_indices.size()) ;
    m_parts.push_back(
        GeometryPart(
            materialID,
            offset,
            static_cast<uint32_t>(indices.size())
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
