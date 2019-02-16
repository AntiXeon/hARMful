#include <scene/ogl/mesh/MeshPart.hpp>
#include <scene/ogl/mesh/Vertex.hpp>
#include <cstdint>

using namespace Hope::GL ;

MeshPart::~MeshPart() {
    if (glIsBuffer(m_vertexBuffer)) {
        glDeleteBuffers(1, &m_vertexBuffer);
    }

    if (glIsBuffer(m_indexBuffer)) {
        glDeleteBuffers(1, &m_indexBuffer);
    }
}

bool MeshPart::initialize
(
    const std::vector<float>& vertices,
    const std::vector<uint32_t>& indices
) {
    m_indices = indices ;

    glGenVertexArrays(1, &m_vertexArray) ;
    glBindVertexArray(m_vertexArray) ;

    glGenBuffers(1, &m_vertexBuffer) ;
  	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer) ;
	glBufferData(GL_ARRAY_BUFFER, Vertex::DataByteSize * vertices.size(), &(vertices[0]), GL_STATIC_DRAW) ;
    glEnableVertexAttribArray(0) ;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::AmountValues, nullptr) ;
    glBindBuffer(GL_ARRAY_BUFFER, 0) ;

    glGenBuffers(1, &m_indexBuffer) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * amountIndices(), &(indices[0]), GL_STATIC_DRAW) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) ;

    return true ;
}
