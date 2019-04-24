#include <scene/ogl/mesh/MeshPart.hpp>
#include <scene/ogl/mesh/Vertex.hpp>
#include <cstdint>

using namespace Hope::GL ;

MeshPart::MeshPart(
    const uint32_t materialID,
    const std::vector<uint32_t>& indices
) : m_materialID(materialID) {
    m_amountIndices = static_cast<uint32_t>(indices.size()) ;

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
    if (glIsBuffer(m_indexBuffer)) {
        glDeleteBuffers(1, &m_indexBuffer) ;
    }

    m_materialID = INVALID_MATERIAL ;
}
