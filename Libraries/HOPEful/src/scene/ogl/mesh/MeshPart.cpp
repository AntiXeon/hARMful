#include <scene/ogl/mesh/MeshPart.hpp>
#include <scene/ogl/mesh/Vertex.hpp>
#include <cstdint>

using namespace Hope::GL ;

MeshPart::MeshPart(
    const std::vector<float>& vertices,
    const std::vector<uint16_t>& indices
) {
    m_amountIndices = static_cast<uint32_t>(indices.size()) ;

    glGenBuffers(1, &m_vertexBuffer) ;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW) ;

    // Position attribute.
    glEnableVertexAttribArray(0) ;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr) ;


    glGenBuffers(1, &m_indexBuffer) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * m_amountIndices, indices.data(), GL_STATIC_DRAW) ;
}

void MeshPart::deleteBuffers() {
    if (glIsBuffer(m_vertexBuffer)) {
        glDeleteBuffers(1, &m_vertexBuffer);
    }

    if (glIsBuffer(m_indexBuffer)) {
        glDeleteBuffers(1, &m_indexBuffer);
    }

    std::cout << "Destroying mesh part" << std::endl ;
}
