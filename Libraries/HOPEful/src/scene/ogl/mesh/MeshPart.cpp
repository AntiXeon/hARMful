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
    std::cout << "VBO: " << m_vertexBuffer << std::endl ;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &(vertices[0]), GL_STATIC_DRAW) ;
    glBindBuffer(GL_ARRAY_BUFFER, 0) ;

    glGenBuffers(1, &m_indexBuffer) ;
    std::cout << "IBO: " << m_indexBuffer << std::endl ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * m_amountIndices, &(indices[0]), GL_STATIC_DRAW) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) ;
}

void MeshPart::deleteBuffers() {
    std::cout << "Destroyed" << std::endl ;
    if (glIsBuffer(m_vertexBuffer)) {
        glDeleteBuffers(1, &m_vertexBuffer);
    }

    if (glIsBuffer(m_indexBuffer)) {
        glDeleteBuffers(1, &m_indexBuffer);
    }
}
