#include <scene/ogl/mesh/MeshPart.hpp>
#include <scene/ogl/mesh/Vertex.hpp>
#include <cstdint>

using namespace Hope::GL ;

MeshPart::MeshPart(
    const std::vector<float>& vertices,
    const std::vector<uint32_t>& indices
) {
    m_amountIndices = static_cast<uint32_t>(indices.size()) ;

    glGenBuffers(1, &m_vertexBuffer) ;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW) ;

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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_amountIndices, indices.data(), GL_STATIC_DRAW) ;
}

void MeshPart::deleteBuffers() {
    if (glIsBuffer(m_vertexBuffer)) {
        glDeleteBuffers(1, &m_vertexBuffer) ;
    }

    if (glIsBuffer(m_indexBuffer)) {
        glDeleteBuffers(1, &m_indexBuffer) ;
    }
}
