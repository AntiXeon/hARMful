#include <scene/ogl/mesh/MeshPart.hpp>
#include <cstdint>

using namespace Hope::GL ;

MeshPart::~MeshPart() {
    if (m_vertexBuffer != INVALID_VALUE) {
        glDeleteBuffers(1, &m_vertexBuffer);
    }

    if (m_indexBuffer != INVALID_VALUE) {
        glDeleteBuffers(1, &m_indexBuffer);
    }
}

bool MeshPart::initialize
(
    const std::vector<Vertex>& /*vertices*/,
    const std::vector<uint32_t>& indices
) {
    m_amountIndices = indices.size();

    // glGenBuffers(1, &m_vertexBuffer);
  	// glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    //
    // glGenBuffers(1, &m_indexBuffer);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_amountIndices, &indices[0], GL_STATIC_DRAW);

    return true ;
}
